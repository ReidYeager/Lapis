
#include "src/defines.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>

char windowClassNameBuffer[32];
LapisWindow activeWindow = NULL;

LRESULT CALLBACK ProcessInputMessage(HWND _hwnd, uint32_t _message, WPARAM _wparam, LPARAM _lparam)
{
  LRESULT result = 0;

  switch (_message)
  {
  case WM_CLOSE:
  case WM_QUIT:
  {
    activeWindow->shouldClose = 1;
    break;
  }
  default:
  {
    result = DefWindowProcA(_hwnd, _message, _wparam, _lparam);
  }
  }

  return result;
}

const char* ConstructWindowClassName(LapisWindow_T* _window)
{
  sprintf(windowClassNameBuffer, "LapisWindowClass_%p", _window);
  return windowClassNameBuffer;
}

LapisResult RegisterWindow(LapisWindow_T* _window)
{
  _window->platform.hinstance = GetModuleHandleA(0);

  WNDCLASSA wc;
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = ProcessInputMessage;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = _window->platform.hinstance;
  wc.hIcon = LoadIcon(_window->platform.hinstance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszClassName = ConstructWindowClassName(_window);
  wc.lpszMenuName = NULL;

  int x = RegisterClassA(&wc);

  if (x == 0)
  {
    LAPIS_LOG(Lapis_Console_Error, "Failed to register window\n");
    return Lapis_Window_Creation_Failed;
  }

  return Lapis_Success;
}

LapisResult CreateAndShowWindow(LapisCreateWindowInfo _info, LapisWindow_T* _window)
{
  uint32_t windowStyle = WS_OVERLAPPEDWINDOW; //WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION
  uint32_t windowExStyle = WS_EX_APPWINDOW;

  _window->platform.hwnd = CreateWindowExA(
    windowExStyle,
    ConstructWindowClassName(_window),
    _info.title,
    windowStyle,
    _info.xPos, // X screen position
    _info.yPos, // Y screen position
    _info.width, // Extent X
    _info.height, // Extent Y
    0,
    0,
    _window->platform.hinstance,
    0);

  if (_window->platform.hwnd == 0)
  {
    LAPIS_LOG(Lapis_Console_Error, "Failed to create window\n");
    return Lapis_Window_Creation_Failed;
  }

  ShowWindow(_window->platform.hwnd, SW_SHOW);

  return Lapis_Success;
}

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow)
{
  LapisWindow_T* newWindow = (LapisWindow_T*)LapisMemAllocZero(sizeof(LapisWindow_T));

  LAPIS_ATTEMPT(RegisterWindow(newWindow), return Lapis_Window_Creation_Failed);
  LAPIS_ATTEMPT(CreateAndShowWindow(_info, newWindow), return Lapis_Window_Creation_Failed);

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

LapisResult LapisWindowProcessOsEvents(LapisWindow _window)
{
  activeWindow = _window;

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

  activeWindow = NULL;
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

uint8_t LapisWindowGetShouldClose(LapisWindow _window)
{
  return _window->shouldClose;
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
    *_extensionCount = 1;
  }

  if (_extensionNames != NULL)
  {
    _extensionNames[0] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
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
    LapisConsolePrintMessage(
      Lapis_Console_Error,
      "Lapis :: Failed to create vulkan window surface\n");
    return Lapis_Window_Component_Failed;
  }

  return Lapis_Success;
}

#endif // LAPIS_VULKAN
