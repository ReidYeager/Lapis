
#include "common.h"

#if GEM_OS_WINDOWS

#include "./buttons_win32.inl"

#define WIN32_WINDOW_CLASS_NAME "LapisWindowClasName"
static LRESULT CALLBACK Win32InputCallback(HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam);
static LRESULT CALLBACK Win32InputCallbackWithClientCallback(HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam);
static LRESULT CALLBACK Win32PollEvent(LapisWindow* pWindow, HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam);
static LapisWindow* g_pollingWindow = NULL;

static bool RegisterWindow(LapisWindow* pWindow, bool useClientCallback)
{
  pWindow->platformInfo.hinstance = GetModuleHandleA(0);

  WNDCLASSA wc;
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = (useClientCallback) ? Win32InputCallbackWithClientCallback : Win32InputCallback;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = pWindow->platformInfo.hinstance;
  wc.hIcon = LoadIcon(pWindow->platformInfo.hinstance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszClassName = WIN32_WINDOW_CLASS_NAME;
  wc.lpszMenuName = NULL;

  int result = RegisterClassA(&wc);

  if (!result)
  {
    // TODO : Log error
    return false;
  }

  return true;
}

static bool CreateWindow(LapisWindow* pWindow, LapisWindowInitInfo* const initInfo)
{
  u32 resizability = WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
  u32 windowStyle = resizability | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
  u32 windowExStyle = WS_EX_APPWINDOW;

  RECT borderRect = { 0, 0, 0, 0 };
  AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);
  u32 adjustedWidth = initInfo->width + borderRect.right - borderRect.left;
  u32 adjustedHeight = initInfo->height + borderRect.bottom - borderRect.top;

  pWindow->platformInfo.hwnd = CreateWindowExA(
    windowExStyle, WIN32_WINDOW_CLASS_NAME,
    initInfo->title, windowStyle,
    initInfo->posX, initInfo->posY,
    adjustedWidth, adjustedHeight,
    0, 0,
    pWindow->platformInfo.hinstance, 0);

  if (!pWindow->platformInfo.hwnd)
  {
    // TODO : Log error
    return false;
  }

  return true;
}

static bool RegisterInputs(LapisWindow* pWindow)
{
  RAWINPUTDEVICE inputDevice = { 0 };
  inputDevice.usUsagePage = 0x01; // HID generic usage page
  inputDevice.usUsage = 0x02; // HID generic usage mouse
  inputDevice.dwFlags = RIDEV_INPUTSINK;
  inputDevice.hwndTarget = pWindow->platformInfo.hwnd;

  if (!RegisterRawInputDevices(&inputDevice, 1, sizeof(inputDevice)))
  {
    // TODO : Log error
    return false;
  }

  return true;
}

bool WindowPlatformInit_Lapis(LapisWindow* pWindow, LapisWindowInitInfo* const initInfo)
{
  if (!RegisterWindow(pWindow, initInfo->pPollEventCallbackFn != NULL))
  {
    // TODO : Log error
    return false;
  }

  if (!CreateWindow(pWindow, initInfo))
  {
    // TODO : Log error
    return false;
  }

  if (!RegisterInputs(pWindow))
  {
    // TODO : Log error
    return false;
  }

  if (!ShowWindow(pWindow->platformInfo.hwnd, SW_SHOW))
  {
    // TODO : Log error
    return false;
  }

  return true;
}

void WindowPlatformShutdown_Lapis(LapisWindow* pWindow)
{
  DestroyWindow(pWindow->platformInfo.hwnd);
  UnregisterClassA(WIN32_WINDOW_CLASS_NAME, pWindow->platformInfo.hinstance);
}

LapisResult LapisWindowPollEvents(LapisWindow* pWindow)
{
  InputUpdateState_Lapis(pWindow);

  MSG message;
  g_pollingWindow = pWindow;

  while (PeekMessageA(&message, g_pollingWindow->platformInfo.hwnd, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  g_pollingWindow = NULL;
  return Lapis_Success;
}

static LRESULT CALLBACK Win32InputCallbackWithClientCallback(HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam)
{
  if (g_pollingWindow == NULL)
  {
    return DefWindowProcA(hwnd, message, wparam, lparam);
  }

  g_pollingWindow->pPollEventCallbackFunction(hwnd, message, wparam, lparam);

  return Win32PollEvent(g_pollingWindow, hwnd, message, wparam, lparam);
}

static LRESULT CALLBACK Win32InputCallback(HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam)
{
  if (g_pollingWindow == NULL)
  {
    return DefWindowProcA(hwnd, message, wparam, lparam);
  }

  return Win32PollEvent(g_pollingWindow, hwnd, message, wparam, lparam);
}

static LRESULT CALLBACK Win32PollEvent(LapisWindow* pWindow, HWND hwnd, u32 message, WPARAM wparam, LPARAM lparam)
{
  switch (message)
  {
  // ==============================
  // Window
  // ==============================

  case WM_CLOSE:
  {
    g_pollingWindow->shouldClose = true;
  } return 0;

  case WM_SIZE:
  {
    bool previouslyMinimized = pWindow->minimized;

    pWindow->minimized = wparam == SIZE_MINIMIZED;
    if (pWindow->minimized)
    {
      LapisEventWindowMinimize e = { true };
      pWindow->pEventCallbackFn(Lapis_Event_Window_Minimize, &e);
      return 0;
    }

    if (previouslyMinimized)
    {
      LapisEventWindowMinimize e = { false };
      pWindow->pEventCallbackFn(Lapis_Event_Window_Minimize, &e);
    }

    pWindow->width = LOWORD(lparam);
    pWindow->height = HIWORD(lparam);

    LapisEventWindowResize e = { pWindow->width, pWindow->height };
    pWindow->pEventCallbackFn(Lapis_Event_Window_Resize, &e);
  } return 0;

  case WM_KILLFOCUS:
  case WM_SETFOCUS:
  {
    LapisEventWindowFocusChange e = { message == WM_SETFOCUS };
    pWindow->pEventCallbackFn(Lapis_Event_Window_Focus_Change, &e);
  } return 0;

  case WM_MOVE:
  {
    pWindow->posX = LOWORD(lparam);
    pWindow->posY = HIWORD(lparam);

    LapisEventWindowMove e = { pWindow->posX, pWindow->posY };
    pWindow->pEventCallbackFn(Lapis_Event_Window_Move, &e);
  } return 0;

  // ==============================
  // Keyboard
  // ==============================

  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  {
    WPARAM keycode = wparam;
    UINT scancode = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    // Differentiate between left/right [shift/ctrl/alt]
    switch (keycode)
    {
    case VK_SHIFT:   keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL;      break;
    case VK_MENU:    keycode = isExtented ? VK_RMENU : VK_LMENU;            break;
    default: break;
    }

    InputHandleButtonPress_Lapis(pWindow, PlatformKeyToInputCode[keycode]);
  } return 0;

  case WM_KEYUP:
  case WM_SYSKEYUP:
  {
    WPARAM keycode = wparam;
    UINT scancode = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    // Differentiate between left/right [shift/ctrl/alt]
    switch (keycode)
    {
    case VK_SHIFT:   keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL;      break;
    case VK_MENU:    keycode = isExtented ? VK_RMENU : VK_LMENU;            break;
    default: break;
    }

    InputHandleButtonRelease_Lapis(pWindow, PlatformKeyToInputCode[keycode]);
  } return 0;

  // ==============================
  // Mouse
  // ==============================

  case WM_MOUSEMOVE:
  {
    i16 x = GET_X_LPARAM(lparam);
    i16 y = GET_Y_LPARAM(lparam);

    InputHandleMouseMove_Lapis(pWindow, x, y);
  } return 0;

  case WM_MOUSEWHEEL: // Mouse wheel Y (Vertical)
  {
    i16 amount = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
    InputHandleMouseScrollY_Lapis(pWindow, amount);
  } return 0;

  case WM_MOUSEHWHEEL: // Mouse wheel X (Horizontal)
  {
    i16 amount = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
    InputHandleMouseScrollX_Lapis(pWindow, amount);
  } return 0;

  case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
  case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
  case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
  case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
  {
    u8 button = 0;
    switch (message)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: button = 0; break;
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK: button = 1; break;
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: button = 2; break;
    case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK: button = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }

    InputHandleMousePress_Lapis(pWindow, button);
  } return 0;

  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MBUTTONUP:
  case WM_XBUTTONUP:
  {
    u8 button = 0;
    switch (message)
    {
    case WM_LBUTTONUP: button = 0; break;
    case WM_RBUTTONUP: button = 1; break;
    case WM_MBUTTONUP: button = 2; break;
    case WM_XBUTTONUP: button = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }
    InputHandleMouseRelease_Lapis(pWindow, button);
  } return 0;

  default:
  {
    return DefWindowProcA(hwnd, message, wparam, lparam);
  }
  }

  return 0;
}


#endif // GEM_OS_WINDOWS
