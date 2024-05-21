
#if !defined(LAPIS_DEFINES_H)
#define LAPIS_DEFINES_H 1

#include "./gem_base.h"
#include "./lapis_buttons.h"

#include <stdbool.h>

// NOTE : Win32 uses 16-bits for extents and positions of the window and mouse.
// May need to change this when working with Linux/Mac

#if GEM_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#undef CreateWindow
#undef max
#undef min
typedef struct LapisWindowPlatformInfo
{
  HWND hwnd;
  HINSTANCE hinstance;
  const char* windowClassName;
} LapisWindowPlatformInfo;

typedef void(*LapisWindowPollEventCallbackFn)(HWND, u32, WPARAM, LPARAM);
#else
typedef struct LapisWindowPlatformInfo
{
  i32 unused;
} LapisWindowPlatformInfo;

typedef void(*LapisWindowPollEventCallbackFn)();
#endif // GEM_OS_*

typedef enum LapisResult
{
  Lapis_Success = 0,
  Lapis_Failure_Unknown,
  Lapis_Failure_Invalid,
  Lapis_Failure_Sys_Call,
} LapisResult;

typedef enum LapisEventType
{
  Lapis_Event_Window               = 0x000000ff,
  Lapis_Event_Window_Move          = 0x00000001,
  Lapis_Event_Window_Resize        = 0x00000002,
  Lapis_Event_Window_Minimize      = 0x00000004,
  Lapis_Event_Window_Close         = 0x00000008,
  Lapis_Event_Window_Focus_Mouse   = 0x00000010,
  Lapis_Event_Window_Focus_Key     = 0x00000020,

  Lapis_Event_Input                = 0x0000ff00,
  Lapis_Event_Input_Button         = 0x00000f00,
  Lapis_Event_Input_Button_Press   = 0x00000100,
  Lapis_Event_Input_Button_Release = 0x00000200,
  Lapis_Event_Input_Button_Repeat  = 0x00000400,
  Lapis_Event_Input_Mouse          = 0x0000f000,
  Lapis_Event_Input_Mouse_Move     = 0x00001000,
  Lapis_Event_Input_Mouse_Press    = 0x00002000,
  Lapis_Event_Input_Mouse_Release  = 0x00004000,
  Lapis_Event_Input_Mouse_Scroll   = 0x00008000,
} LapisEventType;

typedef void(*LapisEventCallbackFn)(LapisEventType, void*);

typedef struct LapisEventWindowMove
{
  i16 newX;
  i16 newY;
} LapisEventWindowMove;

typedef struct LapisEventWindowResize
{
  u16 newWidth;
  u16 newHeight;
} LapisEventWindowResize;

typedef struct LapisEventWindowMinimize
{
  bool isNowMinimized;
} LapisEventWindowMinimize;

typedef struct LapisEventWindowClose
{
  bool isNowClosed;
} LapisEventWindowClose;

typedef struct LapisEventWindowFocusMouse
{
  bool isNowFocused;
} LapisEventWindowFocusMouse;

typedef struct LapisEventWindowFocusKey
{
  bool isNowFocused;
} LapisEventWindowFocusKey;

typedef struct LapisEventInputButtonPress
{
  LapisButtonCode button;
} LapisEventInputButtonPress;

typedef struct LapisEventInputButtonRelease
{
  LapisButtonCode button;
} LapisEventInputButtonRelease;

typedef struct LapisEventInputButtonRepeat
{
  LapisButtonCode button;
} LapisEventInputButtonRepeat;

typedef struct LapisEventInputMouseMove
{
  i16 newX;
  i16 newY;
} LapisEventInputMouseMove;

typedef struct LapisEventInputMousePress
{
  LapisButtonCode button;
} LapisEventInputMousePress;

typedef struct LapisEventInputMouseRelease
{
  LapisButtonCode button;
} LapisEventInputMouseRelease;

typedef struct LapisEventInputMouseScroll
{
  i16 distanceX;
  i16 distanceY;
} LapisEventInputMouseScroll;


typedef struct LapisInputStateFrame
{
  u64 buttons[2];     // 128 bit flags (Current ButtonCode max == 118)
  i16 mousePos[2];    // { X, Y }
  i16 mouseScroll[2]; // { X, Y }
} LapisInputStateFrame;

typedef enum LapisWindowType
{
  Lapis_Window_Type_Windowed,
  Lapis_Window_Type_Borderless,
  Lapis_Window_Type_Fullscreen,
} LapisWindowType;

typedef struct LapisWindowInitInfo
{
  u32 width, height;
  i32 posX, posY;
  const char* title;

  // Currently does nothing.
  LapisWindowType type;

  LapisWindowPollEventCallbackFn pPollEventCallbackFn;
  LapisEventCallbackFn pEventCallbackFn;
} LapisWindowInitInfo;

typedef struct LapisWindow
{
  u16 width, height;
  i16 posX, posY;
  char* title;

  bool shouldClose;
  bool minimized;

  LapisWindowPlatformInfo platformInfo;
  LapisWindowPollEventCallbackFn pPollEventCallbackFunction;
  LapisEventCallbackFn pEventCallbackFn;

  struct
  {
    LapisInputStateFrame prevState;
    LapisInputStateFrame curState;
  } input;
} LapisWindow;

#endif // LAPIS_DEFINES_H
