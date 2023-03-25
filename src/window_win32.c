
#include "src/defines.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>

const char* windowClassName = "LapisWindowClass";

LRESULT CALLBACK ProcessInputMessage(HWND _hwnd, uint32_t _message, WPARAM _wparam, LPARAM _lparam)
{
  LRESULT result = 0;

  switch (_message)
  {
  case WM_CLOSE:
  case WM_QUIT:
  {
    break;
  }
  default:
  {
    result = DefWindowProcA(_hwnd, _message, _wparam, _lparam);
  }
  }

  return result;
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
  wc.lpszClassName = windowClassName;
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
    windowClassName,
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
  LapisMemFree(_window);
  *_window = NULL;
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
