
#include "src/defines.h"
#include "src/internal.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>

char windowClassNameBuffer_Lapis[64];
LapisWindow activeWindow_Lapis = NULL;

void LapisGetSystemInfo(LapisSystemInfo* _pInfo)
{
  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics
  _pInfo->monitorCount = GetSystemMetrics(SM_CMONITORS);
  _pInfo->mouseButtonCount = GetSystemMetrics(SM_CMOUSEBUTTONS);

  _pInfo->primaryMonitorExtents.width = GetSystemMetrics(SM_CXSCREEN);
  _pInfo->primaryMonitorExtents.height = GetSystemMetrics(SM_CYSCREEN);

  _pInfo->windowMinExtents.width = GetSystemMetrics(SM_CXMIN);
  _pInfo->windowMinExtents.height = GetSystemMetrics(SM_CYMIN);
}

LRESULT CALLBACK ProcessInputMessageWin32_Lapis(HWND _hwnd, uint32_t _message, WPARAM _wparam, LPARAM _lparam)
{
  LRESULT result = 0;
  LapisPlatformInputData inputData = { 0 };

  switch (_message)
  {
  case WM_CLOSE:
  case WM_QUIT:
  {
    activeWindow_Lapis->shouldClose = 1;
  } break;
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  {
    inputData.value = 1.0f;
    InputProcessInput(activeWindow_Lapis, LapisPlatformKeycodeMap[_wparam], inputData);
  } break;
  case WM_KEYUP:
  case WM_SYSKEYUP:
  {
    inputData.value = 0.0f;
    InputProcessInput(activeWindow_Lapis, LapisPlatformKeycodeMap[_wparam], inputData);
  } break;
  case WM_MOUSEMOVE:
  {
    int32_t posX = GET_X_LPARAM(_lparam);
    activeWindow_Lapis->cursor.posX = posX;
    inputData.value = (float)posX;
    InputProcessInput(activeWindow_Lapis, Lapis_Input_Axis_Mouse_Position_X, inputData);

    int32_t posY = GET_Y_LPARAM(_lparam);
    activeWindow_Lapis->cursor.posY = posY;
    inputData.value = (float)posY;
    InputProcessInput(activeWindow_Lapis, Lapis_Input_Axis_Mouse_Position_Y, inputData);
  } break;
  case WM_SIZE:
  {
    if (!activeWindow_Lapis) break;

    activeWindow_Lapis->resized = true;

    uint32_t width = LOWORD(_lparam);
    uint32_t height = HIWORD(_lparam);

    if (width || height)
    {
      activeWindow_Lapis->minimized = false;
      activeWindow_Lapis->width = width;
      activeWindow_Lapis->height = height;
    }
    else
    {
      activeWindow_Lapis->minimized = true;
    }

    if (activeWindow_Lapis->fnResizeCallback)
    {
      activeWindow_Lapis->fnResizeCallback(activeWindow_Lapis, activeWindow_Lapis->width, activeWindow_Lapis->height);
    }
  } break;
  case WM_INPUT:
  {
    GET_RAWINPUT_CODE_WPARAM(_wparam);
    if (_wparam != RIM_INPUT)
      break;

    UINT size = sizeof(RAWINPUT);
    uint32_t data[sizeof(RAWINPUT)];
    GetRawInputData((HRAWINPUT)_lparam, RID_INPUT, data, &size, sizeof(RAWINPUTHEADER));

    RAWINPUT* raw = (RAWINPUT*)data;

    if (raw->header.dwType == RIM_TYPEMOUSE)
    {
      inputData.value = raw->data.mouse.lLastX;
      InputProcessInput(activeWindow_Lapis, Lapis_Input_Axis_Mouse_Delta_X, inputData);
      inputData.value = raw->data.mouse.lLastY;
      InputProcessInput(activeWindow_Lapis, Lapis_Input_Axis_Mouse_Delta_Y, inputData);

      LapisInputCode mouseButtonCode = Lapis_Input_Unknown;

      uint32_t buttons = (uint32_t)raw->data.mouse.ulButtons;
      uint32_t index = 0;
      while (buttons != 0)
      {
        if (buttons & 3)
        {
          switch (index)
          {
          case 0: mouseButtonCode = Lapis_Input_Button_Mouse_Left; break;
          case 1: mouseButtonCode = Lapis_Input_Button_Mouse_Right; break;
          case 2: mouseButtonCode = Lapis_Input_Button_Mouse_Middle; break;
          case 3: mouseButtonCode = Lapis_Input_Button_Mouse_4; break;
          case 4: mouseButtonCode = Lapis_Input_Button_Mouse_5; break;
          default: break;
          }

          inputData.value = (buttons & 1);
          InputProcessInput(activeWindow_Lapis, mouseButtonCode, inputData);
        }
        buttons = buttons >> 2;
        index++;
      }
    }

  } break;
  case WM_KILLFOCUS:
  {
    if (activeWindow_Lapis == NULL) break;

    activeWindow_Lapis->focused = false;
  } break;
  case WM_SETFOCUS:
  {
    if (activeWindow_Lapis == NULL) break;

    activeWindow_Lapis->focused = true;
  } break;
  default:
  {
    result = DefWindowProcA(_hwnd, _message, _wparam, _lparam);
  } break;
  }

  return result;
}

const char* ConstructWindowClassName_Lapis(LapisWindow_T* _window)
{
  sprintf_s(windowClassNameBuffer_Lapis, 64, "LapisWindowClass_%p", _window);
  return windowClassNameBuffer_Lapis;
}

LapisResult RegisterWindow_Lapis(LapisWindow_T* _window)
{
  _window->platform.hinstance = GetModuleHandleA(0);

  WNDCLASSA wc;
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = ProcessInputMessageWin32_Lapis;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = _window->platform.hinstance;
  wc.hIcon = LoadIcon(_window->platform.hinstance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszClassName = ConstructWindowClassName_Lapis(_window);
  wc.lpszMenuName = NULL;

  int x = RegisterClassA(&wc);

  if (x == 0)
  {
    LapisLogError("Failed to register window\n");
    return Lapis_Window_Creation_Failed;
  }

  return Lapis_Success;
}

LapisResult RegisterInputs_Lapis(LapisWindow_T* _window)
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
  inputDevice.hwndTarget = _window->platform.hwnd;
  if (!RegisterRawInputDevices(&inputDevice, 1, sizeof(inputDevice)))
  {
    return Lapis_Window_Component_Failed;
  }

  return Lapis_Success;
}

LapisResult CreateAndShowWindow_Lapis(LapisCreateWindowInfo _info, LapisWindow_T* _window)
{
  uint32_t resizability = (WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX) * _info.resizable;

  uint32_t windowStyle = resizability | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
  uint32_t windowExStyle = WS_EX_APPWINDOW;

  // Adjust extents so the canvas matches the input extents
  RECT borderRect = { 0, 0, 0, 0 };
  AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);
  uint32_t adjustedWidth = _info.extents.width + borderRect.right - borderRect.left;
  uint32_t adjustedHeight = _info.extents.height + borderRect.bottom - borderRect.top;

  _window->platform.hwnd = CreateWindowExA(
    windowExStyle,
    ConstructWindowClassName_Lapis(_window),
    _info.title,
    windowStyle,
    _info.position.x, // X screen position
    _info.position.y, // Y screen position
    adjustedWidth,
    adjustedHeight,
    0,
    0,
    _window->platform.hinstance,
    0);

  if (_window->platform.hwnd == 0)
  {
    LapisLogError("Failed to create window\n");
    return Lapis_Window_Creation_Failed;
  }

  LAPIS_ATTEMPT(RegisterInputs_Lapis(_window), return Lapis_Window_Creation_Failed);

  ShowWindow(_window->platform.hwnd, SW_SHOW);
  _window->width = _info.extents.width;
  _window->height = _info.extents.height;
  _window->platform.windowStyle = windowStyle;
  _window->platform.windowExStyle = windowExStyle;

  return Lapis_Success;
}

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow)
{
  LapisWindow_T* newWindow = (LapisWindow_T*)LapisMemAllocZero(sizeof(LapisWindow_T));

  if (activeWindow_Lapis == NULL)
  {
    activeWindow_Lapis = newWindow;
  }

  LAPIS_ATTEMPT(RegisterWindow_Lapis(newWindow), return Lapis_Window_Creation_Failed);
  LAPIS_ATTEMPT(CreateAndShowWindow_Lapis(_info, newWindow), return Lapis_Window_Creation_Failed);

  newWindow->fnResizeCallback = _info.fnResizeCallback;

  *_outWindow = newWindow;
  return Lapis_Success;
}

void LapisDestroyWindow(LapisWindow* _window)
{
  LapisWindow_T* window = *_window;
  DestroyWindow(window->platform.hwnd);
  LapisMemFree(window);
  *_window = NULL;
}

void LapisWindowMarkForClosure(LapisWindow _window)
{
  _window->shouldClose = 1;
}

LapisResult LapisWindowProcessOsEvents(LapisWindow _window)
{
  activeWindow_Lapis = _window;
  activeWindow_Lapis->resized = false;

  activeWindow_Lapis->previousInputState = activeWindow_Lapis->currentInputState;
  LapisMemSet(
    &activeWindow_Lapis->currentInputState.values[Lapis_Input_Axis_Mouse_Delta_X],
    0,
    sizeof(float) * (Lapis_Input_Count - Lapis_Input_Axis_Mouse_Delta_X));

  MSG message;
  // TODO : Split window message processing into OS and input messages
  // Win32 has the option to only handle kbm messages
  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
  // Can handle input messages without needing to use "Translate/Dispatch Message"?
  // https://learn.microsoft.com/en-us/windows/win32/winmsg/using-messages-and-message-queues#examining-a-message-queue

  while (PeekMessageA(&message, _window->platform.hwnd, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  activeWindow_Lapis = NULL;
  return Lapis_Success;
}

uint32_t LapisWindowGetWidth(LapisWindow _window)
{
  return _window->width;
}

uint32_t LapisWindowGetHeight(LapisWindow _window)
{
  return _window->height;
}

bool LapisWindowGetResized(LapisWindow _window)
{
  return _window->resized;
}

bool LapisWindowGetMinimized(LapisWindow _window)
{
  return _window->minimized;
}

bool LapisWindowGetVisible(LapisWindow _window)
{
  return !LapisWindowGetMinimized(_window) && LapisWindowGetHeight(_window) > 0 && LapisWindowGetWidth(_window) > 0;
}

bool LapisWindowGetShouldClose(LapisWindow _window)
{
  return _window->shouldClose;
}

void LapisWindowGetPosition(LapisWindow _window, int32_t* _outX, int32_t* _outY)
{
  *_outX = _window->posX;
  *_outY = _window->posY;
}

void LapisWindowGetExtents(LapisWindow _window, uint32_t* _outWidth, uint32_t* _outHeight)
{
  *_outWidth = _window->width;
  *_outHeight = _window->height;
}

LapisResult LapisWindowSetPosition(LapisWindow _window, uint32_t _xPos, uint32_t _yPos)
{
  if (!SetWindowPos(_window->platform.hwnd, HWND_TOP, _xPos, _yPos, _window->width, _window->height, SWP_NOSIZE))
  {
    return Lapis_Failure;
  }

  _window->posX = _xPos;
  _window->posY = _yPos;

  return Lapis_Success;
}

LapisResult LapisWindowSetExtents(LapisWindow _window, uint32_t _width, uint32_t _height)
{
  LapisSystemInfo platformInfo = { 0 };
  LapisGetSystemInfo(&platformInfo);
  _width  = max(_width, platformInfo.windowMinExtents.width);
  _height = max(_height, platformInfo.windowMinExtents.height);

  // Adjust extents so the canvas matches the input extents
  RECT borderRect = { 0, 0, 0, 0};
  AdjustWindowRectEx(&borderRect, _window->platform.windowStyle, 0, _window->platform.windowExStyle);
  uint32_t adjustedWidth = _width + borderRect.right - borderRect.left;
  uint32_t adjustedHeight = _height + borderRect.bottom - borderRect.top;

  if (!SetWindowPos(
    _window->platform.hwnd,
    HWND_TOP,
    _window->posX,
    _window->posY,
    adjustedWidth,
    adjustedHeight,
    SWP_NOMOVE))
  {
    return Lapis_Failure;
  }

  _window->width = _width;
  _window->height = _height;
  _window->resized = true;

  return Lapis_Success;
}

void LapisWindowCursorGetPosition(LapisWindow _window, int32_t* _outX, int32_t* _outY)
{
  *_outX = _window->cursor.posX;
  *_outY = _window->cursor.posY;
}
void LapisWindowCursorGetVisible(LapisWindow _window, bool* _outVisible)
{
  *_outVisible = _window->cursor.visible;
}

LapisResult LapisWindowCursorSetPosition(LapisWindow _window, uint32_t _xPos, uint32_t _yPos)
{
  if (!_window->focused)
  {
    return Lapis_Failure;
  }

  POINT point;
  point.x = (LONG)_xPos;
  point.y = (LONG)_yPos;

  RECT canvasRect;
  GetClientRect(_window->platform.hwnd, &canvasRect);
  if (point.x >= canvasRect.right)
  {
    point.x = canvasRect.right - 1;
  }
  if (point.y >= canvasRect.bottom)
  {
    point.y = canvasRect.bottom - 1;
  }

  ClientToScreen(_window->platform.hwnd, &point);
  SetCursorPos(point.x, point.y);

  return Lapis_Success;
}

LapisResult LapisWindowCursorSetVisible(LapisWindow _window, bool _visible)
{
  if (!_window->focused)
  {
    return Lapis_Failure;
  }

  ShowCursor(_visible);
  _window->cursor.visible = _visible;

  return Lapis_Success;
}

// =====
// Graphics APIs
// =====

// Vulkan =====
#if (LAPIS_VULKAN)

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

void LapisWindowVulkanGetRequiredExtensions(uint32_t* _extensionCount, const char** _extensionNames)
{
  if (_extensionCount != NULL)
  {
    *_extensionCount = 2;
  }

  if (_extensionNames != NULL)
  {
    _extensionNames[0] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
    _extensionNames[1] = VK_KHR_SURFACE_EXTENSION_NAME;
  }
}

LapisResult LapisWindowVulkanCreateSurface(
  LapisWindow _window,
  VkInstance _instance,
  VkSurfaceKHR* _surface)
{
  VkWin32SurfaceCreateInfoKHR createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.pNext = NULL;
  createInfo.flags = 0;
  createInfo.hinstance = _window->platform.hinstance;
  createInfo.hwnd = _window->platform.hwnd;

  VkResult result = vkCreateWin32SurfaceKHR(
    _instance,
    &createInfo,
    NULL,
    _surface);

  if (result != VK_SUCCESS)
  {
    LapisLogError("Failed to create vulkan window surface\n");
    return Lapis_Window_Component_Failed;
  }

  return Lapis_Success;
}


#endif // LAPIS_VULKAN
