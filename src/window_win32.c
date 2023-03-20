
#include "defines.h"

#include <stdio.h>

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

int RegisterWindow(LapisWindow_T* _window)
{
  _window->platform.hinstance = GetModuleHandleA(0);

  WNDCLASSA wc;
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = ProcessInputMessage;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = _window->platform.hinstance;
  wc.hIcon = LoadIcon(_window->platform.hinstance, IDI_APPLICATION);;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszClassName = windowClassName;
  wc.lpszMenuName = (void*)0;

  int x = RegisterClassA(&wc);

  if (x == 0)
  {
    printf("Failed to register window\n"); // TODO : Replace with custom fatal error/bail
    return -1;
  }

  return 0;
}

int CreateAndShowWindow(LapisCreateWindowInfo _info, LapisWindow_T* _window)
{
  uint32_t windowStyle = WS_OVERLAPPEDWINDOW; //WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION
  uint32_t windowExStyle = WS_EX_APPWINDOW;

  _window->platform.hwnd = CreateWindowExA(
    windowExStyle,
    windowClassName,
    _info.title,
    windowStyle,
    _info.xPos, // Xpos
    _info.yPos, // Ypos
    _info.width, // Extent X
    _info.height, // Extent Y
    0,
    0,
    _window->platform.hinstance,
    0);

  if (_window->platform.hwnd == 0)
  {
    printf("Failed to create window\n"); // TODO : Replace with custom fatal error/bail
    return -1;
  }

  ShowWindow(_window->platform.hwnd, SW_SHOW);

  return 0;
}

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow)
{
  *_outWindow = (LapisWindow_T*)malloc(sizeof(LapisWindow_T));
  *_outWindow = (LapisWindow_T*)memset(*_outWindow, 0, sizeof(LapisWindow_T));
  LapisWindow_T* window = *_outWindow;

  if (RegisterWindow(window))
  {
    return Lapis_Window_Creation_Failed; // TODO : Replace with custom fatal error/bail
  }

  if (CreateAndShowWindow(_info, window))
  {
    return Lapis_Window_Creation_Failed; // TODO : Replace with custom fatal error/bail
  }

  return Lapis_Success;
}
