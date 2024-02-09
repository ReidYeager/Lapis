
#ifdef LAPIS_PLATFORM_WIN32

#include "src/common.h"
#include "include/window/window.h"

#include <string>
#include "stdlib.h"

namespace Lapis
{

#include "keycodes_win32.inl"

// Global variables
// ============================================================

static Window* g_pollingWindow = nullptr;
#define WIN32_WINDOW_CLASS_NAME "LapisWin32WindowClass"

// Declarations
// ============================================================

LRESULT CALLBACK Win32InputCallback(HWND hwnd, uint32_t message, WPARAM wparam, LPARAM lparam);

// Init
// ============================================================

LapisResult Window::Init(const WindowInitInfo* initInfo)
{
  if (m_isValid)
  {
    LAPIS_ERROR("Attempting to initialize a valid window");
    return Lapis_Success;
  }

  if (initInfo->eventCallbackFunction == NULL)
  {
    return Lapis_Failure_Invalid_Input;
  }

  if (Register())
  {
    return Lapis_Failure_Platform;
  }

  if (CreatePlatformWindow(initInfo))
  {
    return Lapis_Failure_Platform;
  }

  if (RegisterInput())
  {
    return Lapis_Failure_Platform;
  }

  // Set visibility
  ShowWindow(m_platformInfo.hwnd, SW_SHOW);

  // Set basic information
  m_width = initInfo->extents.width;
  m_height = initInfo->extents.height;
  m_title = nullptr;
  m_shouldClose = false;
  m_eventCallbackFunction = initInfo->eventCallbackFunction;
  m_platformPollInjection = initInfo->platformPollInjection;

  uint32_t titleLength = strlen(initInfo->title) + 1;
  while (m_title == nullptr)
  {
    m_title = (char*)malloc(titleLength);
  }
  memcpy(m_title, initInfo->title, titleLength);

  m_isValid = true;
  return Lapis_Success;
}

LapisResult Window::Register()
{
  m_platformInfo.hinstance = GetModuleHandleA(0);

  WNDCLASSA wc;
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = Win32InputCallback;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = m_platformInfo.hinstance;
  wc.hIcon = LoadIcon(m_platformInfo.hinstance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszClassName = WIN32_WINDOW_CLASS_NAME;
  wc.lpszMenuName = NULL;

  int result = RegisterClassA(&wc);

  if (result == 0)
  {
    LAPIS_ERROR("Failed to register the window");
    return Lapis_Failure_Platform;
  }
  return Lapis_Success;
}

LapisResult Window::CreatePlatformWindow(const WindowInitInfo* initInfo)
{
  uint32_t resizability = (WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

  uint32_t windowStyle = resizability | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
  uint32_t windowExStyle = WS_EX_APPWINDOW;

  // Adjust extents so the canvas matches the input extents
  RECT borderRect = { 0, 0, 0, 0 };
  AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);
  uint32_t adjustedWidth = initInfo->extents.width + borderRect.right - borderRect.left;
  uint32_t adjustedHeight = initInfo->extents.height + borderRect.bottom - borderRect.top;

  m_platformInfo.hwnd = CreateWindowExA(
    windowExStyle,
    WIN32_WINDOW_CLASS_NAME,
    initInfo->title,
    windowStyle,
    initInfo->position.x,
    initInfo->position.y,
    adjustedWidth,
    adjustedHeight,
    0,
    0,
    m_platformInfo.hinstance,
    0);

  if (m_platformInfo.hwnd == 0)
  {
    LAPIS_ERROR("Failed to create the window");
    return Lapis_Failure_Platform;
  }

  return Lapis_Success;
}

LapisResult Window::RegisterInput()
{
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif

  RAWINPUTDEVICE inputDevice;
  inputDevice.usUsagePage = HID_USAGE_PAGE_GENERIC;
  inputDevice.usUsage = HID_USAGE_GENERIC_MOUSE;
  inputDevice.dwFlags = RIDEV_INPUTSINK;
  inputDevice.hwndTarget = m_platformInfo.hwnd;
  if (!RegisterRawInputDevices(&inputDevice, 1, sizeof(inputDevice)))
  {
    LAPIS_ERROR("Failed to register raw input");
    return Lapis_Failure_Platform;
  }

  return Lapis_Success;
}

// Update
// ============================================================

LapisResult Window::PollEvents()
{
  if (!m_isValid)
  {
    LAPIS_ERROR("Attempting to poll an invalid window");
    return Lapis_Failure;
  }

  MSG message;
  uint32_t allowance = 100; // Limit number of messages allowed to process per call

  g_pollingWindow = this;

  while (allowance > 0 && PeekMessageA(&message, m_platformInfo.hwnd, 0, 0, PM_REMOVE))
  {
    allowance--;
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  g_pollingWindow = nullptr;

  return Lapis_Success;
}

LRESULT CALLBACK Win32InputCallback(HWND hwnd, uint32_t message, WPARAM wparam, LPARAM lparam)
{
  if (g_pollingWindow == nullptr)
    return DefWindowProcA(hwnd, message, wparam, lparam);

  if (g_pollingWindow->m_platformPollInjection.has_value())
  {
    g_pollingWindow->m_platformPollInjection.value()(hwnd, message, wparam, lparam);
  }

  switch (message)
  {
  case WM_CLOSE:
  {
    g_pollingWindow->m_shouldClose = true;
    EventWindowClose e;
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_SIZE:
  {
    bool wasMinimized = g_pollingWindow->m_minimized;
    g_pollingWindow->m_minimized = wparam == SIZE_MINIMIZED;
    if (wparam == SIZE_MINIMIZED)
    {
      EventWindowMinimize e(true);
      g_pollingWindow->m_eventCallbackFunction(e);
    }
    else
    {
      if (wasMinimized)
      {
        EventWindowMinimize e(false);
        g_pollingWindow->m_eventCallbackFunction(e);
      }

      uint32_t w = LOWORD(lparam);
      uint32_t h = HIWORD(lparam);
      g_pollingWindow->m_width = w;
      g_pollingWindow->m_height = h;
      EventWindowResize e(w, h);
      g_pollingWindow->m_eventCallbackFunction(e);
    }
  } return 0;
  case WM_KILLFOCUS:
  case WM_SETFOCUS:
  {
    EventWindowFocus e(message == WM_SETFOCUS);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_MOVE:
  {
    int32_t x = LOWORD(lparam);
    int32_t y = HIWORD(lparam);
    EventWindowMove e(x, y);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;

  // Keyboard
  // ===============
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  {
    WPARAM keycode = wparam;
    UINT scancode  = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    switch (keycode)
    {
    case VK_SHIFT:   keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL;      break;
    case VK_MENU:    keycode = isExtented ? VK_RMENU    : VK_LMENU;         break;
    default: break;
    }

    EventKeyPressed e(PlatformKeyToInputCode[keycode]);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_KEYUP:
  case WM_SYSKEYUP:
  {
    WPARAM keycode = wparam;
    UINT scancode  = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    switch (keycode)
    {
    case VK_SHIFT:   keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL;      break;
    case VK_MENU:    keycode = isExtented ? VK_RMENU    : VK_LMENU;         break;
    default: break;
    }

    EventKeyReleased e(PlatformKeyToInputCode[keycode]);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;

  // Mouse
  // ===============
  case WM_MOUSEMOVE:
  {
    int32_t x = GET_X_LPARAM(lparam);
    int32_t y = GET_Y_LPARAM(lparam);
    EventMouseMove e(x, y);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_MOUSEWHEEL:
  {
    int32_t y = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
    EventMouseScroll e(0, y);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_MOUSEHWHEEL:
  {
    int32_t x = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
    EventMouseScroll e(x, 0);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
  case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
  case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
  case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
  {
    uint32_t button = 0;
    switch (message)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: button = 0; break;
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK: button = 1; break;
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: button = 2; break;
    case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK: button = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }
    EventMouseButtonPress e(button);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MBUTTONUP:
  case WM_XBUTTONUP:
  {
    uint32_t button = 0;
    switch (message)
    {
    case WM_LBUTTONUP: button = 0; break;
    case WM_RBUTTONUP: button = 1; break;
    case WM_MBUTTONUP: button = 2; break;
    case WM_XBUTTONUP: button = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }
    EventMouseButtonRelease e(button);
    g_pollingWindow->m_eventCallbackFunction(e);
  } return 0;
  default: return DefWindowProcA(hwnd, message, wparam, lparam);
  }
}

// Shutdown
// ============================================================

void Window::Shutdown()
{
  std::string title(m_title);

  DestroyWindow(m_platformInfo.hwnd);
  UnregisterClassA(WIN32_WINDOW_CLASS_NAME, m_platformInfo.hinstance);
  free(m_title);
}

} // namespace Lapis

#endif // LAPIS_PLATFORM_WIN32
