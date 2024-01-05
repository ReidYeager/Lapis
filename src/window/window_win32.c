
#include "common.h"

#include <stdio.h>
//#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <windowsx.h>
#undef CreateWindow

global_var const char* globalWindowClassName = "LapisWindowClass";
global_var LapisWindow* globalPollingWindow;
global_var bool globalWin32Registered;

global_var const LapisButtonCode globalWin32KeyToLapisButtonCode[256] =
{
  // TODO : Add better support for OEM keys
  /*0x00*/ Lapis_Button_Unknown, /*0x01*/ Lapis_Mouse_Left,       /*0x02*/ Lapis_Mouse_Right,      /*0x03*/ Lapis_Button_Unknown,
  /*0x04*/ Lapis_Mouse_Middle,   /*0x05*/ Lapis_Mouse_3,          /*0x06*/ Lapis_Mouse_4,          /*0x07*/ Lapis_Button_Unknown,
  /*0x08*/ Lapis_Key_Backspace,  /*0x09*/ Lapis_Key_Tab,          /*0x0a*/ Lapis_Button_Unknown,   /*0x0b*/ Lapis_Button_Unknown,
  /*0x0c*/ Lapis_Button_Unknown, /*0x0d*/ Lapis_Key_Enter,        /*0x0e*/ Lapis_Button_Unknown,   /*0x0f*/ Lapis_Button_Unknown,

  /*0x10*/ Lapis_Button_Unknown, /*0x11*/ Lapis_Button_Unknown,   /*0x12*/ Lapis_Button_Unknown,   /*0x13*/ Lapis_Button_Unknown,
  /*0x14*/ Lapis_Key_CapsLock,   /*0x15*/ Lapis_Button_Unknown,   /*0x16*/ Lapis_Button_Unknown,   /*0x17*/ Lapis_Button_Unknown,
  /*0x18*/ Lapis_Button_Unknown, /*0x19*/ Lapis_Button_Unknown,   /*0x1a*/ Lapis_Button_Unknown,   /*0x1b*/ Lapis_Key_Escape,
  /*0x1c*/ Lapis_Button_Unknown, /*0x1d*/ Lapis_Button_Unknown,   /*0x1e*/ Lapis_Button_Unknown,   /*0x1f*/ Lapis_Button_Unknown,

  /*0x20*/ Lapis_Key_Space,      /*0x21*/ Lapis_Key_PageUp,       /*0x22*/ Lapis_Key_PageDown,     /*0x23*/ Lapis_Key_End,
  /*0x24*/ Lapis_Key_Home,       /*0x25*/ Lapis_Key_Arrow_Left,   /*0x26*/ Lapis_Key_Arrow_Up,     /*0x27*/ Lapis_Key_Arrow_Right,
  /*0x28*/ Lapis_Key_Arrow_Down, /*0x29*/ Lapis_Button_Unknown,   /*0x2a*/ Lapis_Button_Unknown,   /*0x2b*/ Lapis_Button_Unknown,
  /*0x2c*/ Lapis_Button_Unknown, /*0x2d*/ Lapis_Key_Insert,       /*0x2e*/ Lapis_Key_Delete,       /*0x2f*/ Lapis_Button_Unknown,

  /*0x30*/ Lapis_Key_0,          /*0x31*/ Lapis_Key_1,            /*0x32*/ Lapis_Key_2,            /*0x33*/ Lapis_Key_3,
  /*0x34*/ Lapis_Key_4,          /*0x35*/ Lapis_Key_5,            /*0x36*/ Lapis_Key_6,            /*0x37*/ Lapis_Key_7,
  /*0x38*/ Lapis_Key_8,          /*0x39*/ Lapis_Key_9,            /*0x3a*/ Lapis_Button_Unknown,   /*0x3b*/ Lapis_Button_Unknown,
  /*0x3c*/ Lapis_Button_Unknown, /*0x3d*/ Lapis_Button_Unknown,   /*0x3e*/ Lapis_Button_Unknown,   /*0x3f*/ Lapis_Button_Unknown,

  /*0x40*/ Lapis_Button_Unknown, /*0x41*/ Lapis_Key_A,            /*0x42*/ Lapis_Key_B,            /*0x43*/ Lapis_Key_C,
  /*0x44*/ Lapis_Key_D,          /*0x45*/ Lapis_Key_E,            /*0x46*/ Lapis_Key_F,            /*0x47*/ Lapis_Key_G,
  /*0x48*/ Lapis_Key_H,          /*0x49*/ Lapis_Key_I,            /*0x4a*/ Lapis_Key_J,            /*0x4b*/ Lapis_Key_K,
  /*0x4c*/ Lapis_Key_L,          /*0x4d*/ Lapis_Key_M,            /*0x4e*/ Lapis_Key_N,            /*0x4f*/ Lapis_Key_O,

  /*0x50*/ Lapis_Key_P,          /*0x51*/ Lapis_Key_Q,            /*0x52*/ Lapis_Key_R,            /*0x53*/ Lapis_Key_S,
  /*0x54*/ Lapis_Key_T,          /*0x55*/ Lapis_Key_U,            /*0x56*/ Lapis_Key_V,            /*0x57*/ Lapis_Key_W,
  /*0x58*/ Lapis_Key_X,          /*0x59*/ Lapis_Key_Y,            /*0x5a*/ Lapis_Key_Z,            /*0x5b*/ Lapis_Button_Unknown,
  /*0x5c*/ Lapis_Button_Unknown, /*0x5d*/ Lapis_Key_Menu,         /*0x5e*/ Lapis_Button_Unknown,   /*0x5f*/ Lapis_Button_Unknown,

  /*0x60*/ Lapis_Key_Num_0,      /*0x61*/ Lapis_Key_Num_1,        /*0x62*/ Lapis_Key_Num_2,        /*0x63*/ Lapis_Key_Num_3,
  /*0x64*/ Lapis_Key_Num_4,      /*0x65*/ Lapis_Key_Num_5,        /*0x66*/ Lapis_Key_Num_6,        /*0x67*/ Lapis_Key_Num_7,
  /*0x68*/ Lapis_Key_Num_8,      /*0x69*/ Lapis_Key_Num_9,        /*0x6a*/ Lapis_Key_Num_Multiply, /*0x6b*/ Lapis_Key_Num_Add,
  /*0x6c*/ Lapis_Button_Unknown, /*0x6d*/ Lapis_Key_Num_Subtract, /*0x6e*/ Lapis_Key_Num_Decimal,  /*0x6f*/ Lapis_Key_Num_Divide,

  /*0x70*/ Lapis_Key_F1,         /*0x71*/ Lapis_Key_F2,           /*0x72*/ Lapis_Key_F3,           /*0x73*/ Lapis_Key_F4,
  /*0x74*/ Lapis_Key_F5,         /*0x75*/ Lapis_Key_F6,           /*0x76*/ Lapis_Key_F7,           /*0x77*/ Lapis_Key_F8,
  /*0x78*/ Lapis_Key_F9,         /*0x79*/ Lapis_Key_F10,          /*0x7a*/ Lapis_Key_F11,          /*0x7b*/ Lapis_Key_F12,
  /*0x7c*/ Lapis_Key_F13,        /*0x7d*/ Lapis_Key_F14,          /*0x7e*/ Lapis_Key_F15,          /*0x7f*/ Lapis_Key_F16,

  /*0x80*/ Lapis_Key_F17,        /*0x81*/ Lapis_Key_F18,          /*0x82*/ Lapis_Key_F19,          /*0x83*/ Lapis_Key_F20,
  /*0x84*/ Lapis_Key_F21,        /*0x85*/ Lapis_Key_F22,          /*0x86*/ Lapis_Key_F23,          /*0x87*/ Lapis_Key_F24,
  /*0x88*/ Lapis_Button_Unknown, /*0x89*/ Lapis_Button_Unknown,   /*0x8a*/ Lapis_Button_Unknown,   /*0x8b*/ Lapis_Button_Unknown,
  /*0x8c*/ Lapis_Button_Unknown, /*0x8d*/ Lapis_Button_Unknown,   /*0x8e*/ Lapis_Button_Unknown,   /*0x8f*/ Lapis_Button_Unknown,

  /*0x90*/ Lapis_Key_NumLock,    /*0x91*/ Lapis_Key_ScrollLock,   /*0x92*/ Lapis_Button_Unknown,   /*0x93*/ Lapis_Button_Unknown,
  /*0x94*/ Lapis_Button_Unknown, /*0x95*/ Lapis_Button_Unknown,   /*0x96*/ Lapis_Button_Unknown,   /*0x97*/ Lapis_Button_Unknown,
  /*0x98*/ Lapis_Button_Unknown, /*0x99*/ Lapis_Button_Unknown,   /*0x9a*/ Lapis_Button_Unknown,   /*0x9b*/ Lapis_Button_Unknown,
  /*0x9c*/ Lapis_Button_Unknown, /*0x9d*/ Lapis_Button_Unknown,   /*0x9e*/ Lapis_Button_Unknown,   /*0x9f*/ Lapis_Button_Unknown,

  /*0xa0*/ Lapis_Key_Shift_L,    /*0xa1*/ Lapis_Key_Shift_R,      /*0xa2*/ Lapis_Key_Ctrl_L,       /*0xa3*/ Lapis_Key_Ctrl_R,
  /*0xa4*/ Lapis_Key_Alt_L,      /*0xa5*/ Lapis_Key_Alt_R,        /*0xa6*/ Lapis_Button_Unknown,   /*0xa7*/ Lapis_Button_Unknown,
  /*0xa8*/ Lapis_Button_Unknown, /*0xa9*/ Lapis_Button_Unknown,   /*0xaa*/ Lapis_Button_Unknown,   /*0xab*/ Lapis_Button_Unknown,
  /*0xac*/ Lapis_Button_Unknown, /*0xad*/ Lapis_Button_Unknown,   /*0xae*/ Lapis_Button_Unknown,   /*0xaf*/ Lapis_Button_Unknown,

  /*0xb0*/ Lapis_Button_Unknown, /*0xb1*/ Lapis_Button_Unknown,   /*0xb2*/ Lapis_Button_Unknown,   /*0xb3*/ Lapis_Button_Unknown,
  /*0xb4*/ Lapis_Button_Unknown, /*0xb5*/ Lapis_Button_Unknown,   /*0xb6*/ Lapis_Button_Unknown,   /*0xb7*/ Lapis_Button_Unknown,
  /*0xb8*/ Lapis_Button_Unknown, /*0xb9*/ Lapis_Button_Unknown,   /*0xba*/ Lapis_Key_Semicolon,    /*0xbb*/ Lapis_Key_Equals,
  /*0xbc*/ Lapis_Key_Comma,      /*0xbd*/ Lapis_Key_Hyphen,       /*0xbe*/ Lapis_Key_Period,       /*0xbf*/ Lapis_Key_ForwardSlash,

  /*0xc0*/ Lapis_Key_Grave,      /*0xc1*/ Lapis_Button_Unknown,   /*0xc2*/ Lapis_Button_Unknown,   /*0xc3*/ Lapis_Button_Unknown,
  /*0xc4*/ Lapis_Button_Unknown, /*0xc5*/ Lapis_Button_Unknown,   /*0xc6*/ Lapis_Button_Unknown,   /*0xc7*/ Lapis_Button_Unknown,
  /*0xc8*/ Lapis_Button_Unknown, /*0xc9*/ Lapis_Button_Unknown,   /*0xca*/ Lapis_Button_Unknown,   /*0xcb*/ Lapis_Button_Unknown,
  /*0xcc*/ Lapis_Button_Unknown, /*0xcd*/ Lapis_Button_Unknown,   /*0xce*/ Lapis_Button_Unknown,   /*0xcf*/ Lapis_Button_Unknown,

  /*0xd0*/ Lapis_Button_Unknown, /*0xd1*/ Lapis_Button_Unknown,   /*0xd2*/ Lapis_Button_Unknown,   /*0xd3*/ Lapis_Button_Unknown,
  /*0xd4*/ Lapis_Button_Unknown, /*0xd5*/ Lapis_Button_Unknown,   /*0xd6*/ Lapis_Button_Unknown,   /*0xd7*/ Lapis_Button_Unknown,
  /*0xd8*/ Lapis_Button_Unknown, /*0xd9*/ Lapis_Button_Unknown,   /*0xda*/ Lapis_Button_Unknown,   /*0xdb*/ Lapis_Key_Bracket_L,
  /*0xdc*/ Lapis_Key_BackSlash,  /*0xdd*/ Lapis_Key_Bracket_R,    /*0xde*/ Lapis_Key_Apostrophe,   /*0xdf*/ Lapis_Button_Unknown,

  /*0xe0*/ Lapis_Button_Unknown, /*0xe1*/ Lapis_Button_Unknown,   /*0xe2*/ Lapis_Button_Unknown,   /*0xe3*/ Lapis_Button_Unknown,
  /*0xe4*/ Lapis_Button_Unknown, /*0xe5*/ Lapis_Button_Unknown,   /*0xe6*/ Lapis_Button_Unknown,   /*0xe7*/ Lapis_Button_Unknown,
  /*0xe8*/ Lapis_Button_Unknown, /*0xe9*/ Lapis_Button_Unknown,   /*0xea*/ Lapis_Button_Unknown,   /*0xeb*/ Lapis_Button_Unknown,
  /*0xec*/ Lapis_Button_Unknown, /*0xed*/ Lapis_Button_Unknown,   /*0xee*/ Lapis_Button_Unknown,   /*0xef*/ Lapis_Button_Unknown,

  /*0xf0*/ Lapis_Button_Unknown, /*0xf1*/ Lapis_Button_Unknown,   /*0xf2*/ Lapis_Button_Unknown,   /*0xf3*/ Lapis_Button_Unknown,
  /*0xf4*/ Lapis_Button_Unknown, /*0xf5*/ Lapis_Button_Unknown,   /*0xf6*/ Lapis_Button_Unknown,   /*0xf7*/ Lapis_Button_Unknown,
  /*0xf8*/ Lapis_Button_Unknown, /*0xf9*/ Lapis_Button_Unknown,   /*0xfa*/ Lapis_Button_Unknown,   /*0xfb*/ Lapis_Button_Unknown,
  /*0xfc*/ Lapis_Button_Unknown, /*0xfd*/ Lapis_Button_Unknown,   /*0xfe*/ Lapis_Button_Unknown,   /*0xff*/ Lapis_Button_Unknown
};

LRESULT CALLBACK WindowInputCallback(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
  if (globalPollingWindow == NULL)
    return DefWindowProcA(window, message, wparam, lparam);

  // TODO : Rewrite keyboard/mouse using raw input
  // Sometimes a key state doesn't change properly
  switch (message)
  {
  // Window
  // ===============
  case WM_CLOSE:
  case WM_DESTROY:
  {
    globalPollingWindow->shouldClose = true;
  } return 0;

  case WM_SIZE:
  {
    globalPollingWindow->width = LOWORD(lparam);
    globalPollingWindow->height = HIWORD(lparam);
    globalPollingWindow->minimized = wparam == SIZE_MINIMIZED;
  } return 0;

  case WM_KILLFOCUS:
  case WM_SETFOCUS:
  {
    globalPollingWindow->focused = (message == WM_SETFOCUS);
  } return 0;

  case WM_MOVE:
  {
    globalPollingWindow->screenPosX = LOWORD(lparam);
    globalPollingWindow->screenPosY = HIWORD(lparam);
  } return 0;

  // Keyboard
  // ===============
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  {
    WPARAM keycode = wparam;
    UINT scancode = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    switch (keycode)
    {
    case VK_SHIFT: keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL; break;
    case VK_MENU: keycode = isExtented ? VK_RMENU : VK_LMENU; break;
    default: break;
    }

    LapisButtonCode button = globalWin32KeyToLapisButtonCode[keycode];
    uint8_t index = (int8_t)(button >> 6);
    uint64_t bit = (1ll << (button % 64));
    globalPollingWindow->input.currentState.buttons[index] |= bit;
  } return 0;

  case WM_KEYUP:
  case WM_SYSKEYUP:
  {
    WPARAM keycode = wparam;
    UINT scancode = (lparam & 0x00ff0000) >> 16;
    int isExtented = (lparam & 0x01000000) != 0;

    switch (keycode)
    {
    case VK_SHIFT: keycode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
    case VK_CONTROL: keycode = isExtented ? VK_RCONTROL : VK_LCONTROL; break;
    case VK_MENU: keycode = isExtented ? VK_RMENU : VK_LMENU; break;
    default: break;
    }

    LapisButtonCode button = globalWin32KeyToLapisButtonCode[keycode];
    uint8_t index = (int8_t)(button >> 6);
    uint64_t bit = (1ll << (button % 64));
    globalPollingWindow->input.currentState.buttons[index] &= ~bit;
  } return 0;

  // Mouse
  // ===============
  case WM_MOUSEMOVE:
  {
    globalPollingWindow->input.currentState.mousePosX = GET_X_LPARAM(lparam);
    globalPollingWindow->input.currentState.mousePosY = GET_Y_LPARAM(lparam);
  } return 0;

  case WM_MOUSEWHEEL:
  {
    globalPollingWindow->input.currentState.mouseScrollY = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
  } return 0;

  case WM_MOUSEHWHEEL:
  {
    globalPollingWindow->input.currentState.mouseScrollX = GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA;
  } return 0;

  case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
  case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
  case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
  case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
  {
    uint32_t mouseButton = 0;
    switch (message)
    {
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: mouseButton = 0; break;
    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK: mouseButton = 1; break;
    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK: mouseButton = 2; break;
    case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK: mouseButton = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }

    LapisButtonCode button = (LapisButtonCode)(Lapis_Mouse_0 + mouseButton);
    uint8_t index = (int8_t)(button >> 6);
    uint64_t bit = (1ll << (button % 64));
    globalPollingWindow->input.currentState.buttons[index] |= bit;
  } return 0;

  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MBUTTONUP:
  case WM_XBUTTONUP:
  {
    uint8_t mouseButton = 0;
    switch (message)
    {
    case WM_LBUTTONUP: mouseButton = 0; break;
    case WM_RBUTTONUP: mouseButton = 1; break;
    case WM_MBUTTONUP: mouseButton = 2; break;
    case WM_XBUTTONUP: mouseButton = GET_XBUTTON_WPARAM(wparam) + 2; break;
    default: break;
    }
    LapisButtonCode button = (LapisButtonCode)(Lapis_Mouse_0 + mouseButton);
    uint8_t index = (int8_t)(button >> 6);
    uint64_t bit = (1ll << (button % 64));
    globalPollingWindow->input.currentState.buttons[index] &= ~bit;
  } return 0;

  // Default
  // ===============
  default: return DefWindowProcA(window, message, wparam, lparam);
  }
}

internal void
RegisterWindowClass(HINSTANCE moduleHandle)
{
  if (globalWin32Registered)
  {
    // Only needs to be called once before the first window.
    return;
  }

  WNDCLASSEXA windowClass = {};
  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style = CS_OWNDC; // | CS_DBLCLKS;
  windowClass.lpfnWndProc = WindowInputCallback;
  windowClass.hInstance = moduleHandle;
  windowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);
  windowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
  windowClass.lpszClassName = globalWindowClassName;

  if (RegisterClassExA(&windowClass) == 0)
  {
    printf("Failed to register the class\n");
    return;
  }

  globalWin32Registered = true;

  return;
}

internal void
CreateWin32Window(LapisWindow* window, uint32_t width, uint32_t height, const char* title)
{
  window->platform.hwnd = CreateWindowExA(
    WS_EX_APPWINDOW,
    globalWindowClassName,
    title,
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    0, 0,
    width, height,
    0,
    0,
    window->platform.hinstance,
    0);

  window->screenPosX = 0;
  window->screenPosY = 0;
  window->width = width;
  window->height = height;
  window->focused = true;

  if (window->platform.hwnd == 0)
  {
    printf("Failed to create window\n");
  }
}

internal void
LapisWindowUpdate(LapisWindow* window)
{
  if (window->platform.hwnd == 0)
  {
    return;
  }

  if (window->shouldClose)
  {
    LapisWindowShutdown(window);
    return;
  }

  globalPollingWindow = window;

  window->input.previousState = window->input.currentState;
  window->input.currentState.mouseScrollX = 0;
  window->input.currentState.mouseScrollY = 0;

  MSG message;
  while (PeekMessageA(&message, window->platform.hwnd, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&message);
    DispatchMessageA(&message);
  }

  // TODO : add xinput for controllers

  globalPollingWindow = NULL;
}

LapisWindow LapisWindowInit(uint32_t width, uint32_t height, const char* title)
{
  LapisWindow window = {};
  window.platform.hinstance = GetModuleHandleA(0);

  RegisterWindowClass(window.platform.hinstance);
  CreateWin32Window(&window, width, height, title);

  if (window.platform.hwnd == 0)
  {
    window.shouldClose = true;
    window.platform.hinstance = 0;
  }

  return window;
}

void LapisWindowShutdown(LapisWindow* window)
{
  DestroyWindow(window->platform.hwnd);
  LapisWindow emptyWindow = {};
  emptyWindow.shouldClose = true;
  *window = emptyWindow;
}
