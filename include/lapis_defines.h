#ifndef LAPIS_DEFINES_H
#define LAPIS_DEFINES_H

#include <stdint.h>
#include <stdbool.h>

// ============================================================
// Window
// ============================================================

#ifdef LAPIS_PLATFORM_WIN32
#include <windows.h>
#undef CreateWindow
typedef struct LapisWindowPlatformInfo
{
  HWND hwnd; // window handle
  HINSTANCE hinstance; // module handle
} LapisWindowPlatformInfo;
#else
typedef struct LapisWindowPlatformInfo
{
  int noInfo;
} LapisWindowPlatformInfo;
#endif // LAPIS_PLATFORM_*

typedef enum LapisButtonCode
{
  Lapis_Button_Unknown = 0,

  // Alphabetic keys
  Lapis_Key_A, Lapis_Key_B, Lapis_Key_C, Lapis_Key_D, Lapis_Key_E, Lapis_Key_F, Lapis_Key_G, Lapis_Key_H, Lapis_Key_I,
  Lapis_Key_J, Lapis_Key_K, Lapis_Key_L, Lapis_Key_M, Lapis_Key_N, Lapis_Key_O, Lapis_Key_P, Lapis_Key_Q, Lapis_Key_R,
  Lapis_Key_S, Lapis_Key_T, Lapis_Key_U, Lapis_Key_V, Lapis_Key_W, Lapis_Key_X, Lapis_Key_Y, Lapis_Key_Z,

  // Numeric keys
  Lapis_Key_0, Lapis_Key_1, Lapis_Key_2, Lapis_Key_3, Lapis_Key_4,
  Lapis_Key_5, Lapis_Key_6, Lapis_Key_7, Lapis_Key_8, Lapis_Key_9,

  // Nubmer pad keys
  Lapis_Key_Num_0,                Lapis_Key_Num_1,                Lapis_Key_Num_2,
  Lapis_Key_Num_3,                Lapis_Key_Num_4,                Lapis_Key_Num_5,
  Lapis_Key_Num_6,                Lapis_Key_Num_7,                Lapis_Key_Num_8,
  Lapis_Key_Num_9,                Lapis_Key_Num_Multiply /* * */, Lapis_Key_Num_Add    /* + */,
  Lapis_Key_Num_Subtract /* - */, Lapis_Key_Num_Decimal  /* . */, Lapis_Key_Num_Divide /* / */,
  // Lapis_Key_Num_Enter missing because it's the same as Lapis_Key_Enter on win32

  // Function keys
  Lapis_Key_F1,  Lapis_Key_F2 , Lapis_Key_F3,  Lapis_Key_F4,  Lapis_Key_F5,  Lapis_Key_F6,  Lapis_Key_F7,  Lapis_Key_F8,
  Lapis_Key_F9,  Lapis_Key_F10, Lapis_Key_F11, Lapis_Key_F12, Lapis_Key_F13, Lapis_Key_F14, Lapis_Key_F15, Lapis_Key_F16,
  Lapis_Key_F17, Lapis_Key_F18, Lapis_Key_F19, Lapis_Key_F20, Lapis_Key_F21, Lapis_Key_F22, Lapis_Key_F23, Lapis_Key_F24,

  // Arrow keys
  Lapis_Key_Arrow_Up, Lapis_Key_Arrow_Right, Lapis_Key_Arrow_Down, Lapis_Key_Arrow_Left,

  // Symbol keys
  Lapis_Key_Grave     /* ` */, Lapis_Key_Hyphen    /* - */, Lapis_Key_Equals       /* = */, Lapis_Key_Bracket_L  /* [ */,
  Lapis_Key_Bracket_R /* ] */, Lapis_Key_BackSlash /* \ */, Lapis_Key_Semicolon    /* ; */, Lapis_Key_Apostrophe /* ' */,
  Lapis_Key_Comma     /* , */, Lapis_Key_Period    /* . */, Lapis_Key_ForwardSlash /* / */,

  // Modifier keys
  Lapis_Key_Shift_L, Lapis_Key_Shift_R,
  Lapis_Key_Ctrl_L,  Lapis_Key_Ctrl_R,
  Lapis_Key_Alt_L,   Lapis_Key_Alt_R,

  // Other keys
  Lapis_Key_Escape,   Lapis_Key_Enter,   Lapis_Key_Space,      Lapis_Key_Backspace, Lapis_Key_Tab,
  Lapis_Key_CapsLock, Lapis_Key_NumLock, Lapis_Key_ScrollLock, Lapis_Key_Insert,    Lapis_Key_Delete,
  Lapis_Key_Home,     Lapis_Key_End,     Lapis_Key_PageUp,     Lapis_Key_PageDown,  Lapis_Key_Menu,

  // Mouse buttons
  Lapis_Mouse_0, Lapis_Mouse_Left    = Lapis_Mouse_0,
  Lapis_Mouse_1, Lapis_Mouse_Right   = Lapis_Mouse_1,
  Lapis_Mouse_2, Lapis_Mouse_Middle  = Lapis_Mouse_2,
  Lapis_Mouse_3, Lapis_Mouse_Back    = Lapis_Mouse_3,
  Lapis_Mouse_4, Lapis_Mouse_Forward = Lapis_Mouse_4,

  Lapis_Button_COUNT
} LapisButtonCode;

typedef struct LapisInputState
{
  uint64_t buttons[2]; // 128 bits (118 button codes)
  int32_t mousePosX, mousePosY;
  int8_t mouseScrollX, mouseScrollY;
} LapisInputState;

typedef struct LapisInputInfo
{
  LapisInputState currentState;
  LapisInputState previousState;
} LapisInputInfo;

typedef struct LapisMouseDelta
{
  int32_t x, y;
} LapisMouseDelta;

typedef struct LapisWindow
{
  bool shouldClose;
  bool focused;
  bool minimized;
  LapisWindowPlatformInfo platform;
  LapisInputInfo input;

  uint32_t width, height;
  int32_t screenPosX, screenPosY;

  // TODO : Store callbacks
} LapisWindow;

#endif // !LAPIS_DEFINES_H
