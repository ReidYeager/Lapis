
#ifndef GEM_LAPIS_DEFINES_H
#define GEM_LAPIS_DEFINES_H

#include <stdint.h>
#include <stdbool.h>

// =====
// Lapis generic
// =====

typedef enum LapisResult
{
  Lapis_Success,
  Lapis_Window_Creation_Failed,
  Lapis_Window_Component_Failed,
  Lapis_Unknown
} LapisResult;

// =====
// Console
// =====

typedef enum LapisConsolePrintType
{
  Lapis_Console_Debug,
  Lapis_Console_Info,
  Lapis_Console_Warning,
  Lapis_Console_Error,
  Lapis_Console_Fatal
} LapisConsolePrintType;

// =====
// Window
// =====

typedef struct LapisWindow_T* LapisWindow;

typedef struct LapisCreateWindowInfo
{
  int32_t xPos;
  int32_t yPos;
  uint32_t width;
  uint32_t height;
  const char* title;
} LapisCreateWindowInfo;

// =====
// Input
// =====

typedef enum LapisInputCode
{
  Lapis_Input_Unknown,

  // Buttons =====

  Lapis_Input_Button_Mouse_Left,
  Lapis_Input_Button_Mouse_Right,
  Lapis_Input_Button_Mouse_Middle,
  Lapis_Input_Button_Mouse_4,
  Lapis_Input_Button_Mouse_5,

  Lapis_Input_Button_A,
  Lapis_Input_Button_B,
  Lapis_Input_Button_C,
  Lapis_Input_Button_D,
  Lapis_Input_Button_E,
  Lapis_Input_Button_F,
  Lapis_Input_Button_G,
  Lapis_Input_Button_H,
  Lapis_Input_Button_I,
  Lapis_Input_Button_J,
  Lapis_Input_Button_K,
  Lapis_Input_Button_L,
  Lapis_Input_Button_M,
  Lapis_Input_Button_N,
  Lapis_Input_Button_O,
  Lapis_Input_Button_P,
  Lapis_Input_Button_Q,
  Lapis_Input_Button_R,
  Lapis_Input_Button_S,
  Lapis_Input_Button_T,
  Lapis_Input_Button_U,
  Lapis_Input_Button_V,
  Lapis_Input_Button_W,
  Lapis_Input_Button_X,
  Lapis_Input_Button_Y,
  Lapis_Input_Button_Z,

  Lapis_Input_Button_0,
  Lapis_Input_Button_1,
  Lapis_Input_Button_2,
  Lapis_Input_Button_3,
  Lapis_Input_Button_4,
  Lapis_Input_Button_5,
  Lapis_Input_Button_6,
  Lapis_Input_Button_7,
  Lapis_Input_Button_8,
  Lapis_Input_Button_9,

  Lapis_Input_Button_Numpad0,
  Lapis_Input_Button_Numpad1,
  Lapis_Input_Button_Numpad2,
  Lapis_Input_Button_Numpad3,
  Lapis_Input_Button_Numpad4,
  Lapis_Input_Button_Numpad5,
  Lapis_Input_Button_Numpad6,
  Lapis_Input_Button_Numpad7,
  Lapis_Input_Button_Numpad8,
  Lapis_Input_Button_Numpad9,
  Lapis_Input_Button_Numpad_Muliply,
  Lapis_Input_Button_Numpad_Add,
  Lapis_Input_Button_Numpad_Subtract,
  Lapis_Input_Button_Numpad_Decimal,
  Lapis_Input_Button_Numpad_Divide,
  Lapis_Input_Button_Numpad_Enter,

  Lapis_Input_Button_F1,
  Lapis_Input_Button_F2,
  Lapis_Input_Button_F3,
  Lapis_Input_Button_F4,
  Lapis_Input_Button_F5,
  Lapis_Input_Button_F6,
  Lapis_Input_Button_F7,
  Lapis_Input_Button_F8,
  Lapis_Input_Button_F9,
  Lapis_Input_Button_F10,
  Lapis_Input_Button_F11,
  Lapis_Input_Button_F12,
  Lapis_Input_Button_F13,
  Lapis_Input_Button_F14,
  Lapis_Input_Button_F15,
  Lapis_Input_Button_F16,
  Lapis_Input_Button_F17,
  Lapis_Input_Button_F18,
  Lapis_Input_Button_F19,
  Lapis_Input_Button_F20,
  Lapis_Input_Button_F21,
  Lapis_Input_Button_F22,
  Lapis_Input_Button_F23,
  Lapis_Input_Button_F24,

  Lapis_Input_Button_Arrow_Up,
  Lapis_Input_Button_Arrow_Down,
  Lapis_Input_Button_Arrow_Right,
  Lapis_Input_Button_Arrow_Left,

  Lapis_Input_Button_Grave,        /* ` */
  Lapis_Input_Button_Hyphen,       /* - */
  Lapis_Input_Button_Equals,       /* = */
  Lapis_Input_Button_Lbracket,     /* [ */
  Lapis_Input_Button_Rbracket,     /* ] */
  Lapis_Input_Button_Backslash,    /* \ */
  Lapis_Input_Button_SemiColon,    /* ; */
  Lapis_Input_Button_Apostrophe,   /* ' */
  Lapis_Input_Button_Comma,        /* , */
  Lapis_Input_Button_Period,       /* . */
  Lapis_Input_Button_ForwardSlash, /* / */

  Lapis_Input_Button_Escape,
  Lapis_Input_Button_Enter,
  Lapis_Input_Button_Space,
  Lapis_Input_Button_Backspace,
  Lapis_Input_Button_Tab,
  Lapis_Input_Button_CapsLock,
  Lapis_Input_Button_NumLock,
  Lapis_Input_Button_ScrollLock,
  Lapis_Input_Button_Insert,
  Lapis_Input_Button_Delete,
  Lapis_Input_Button_Home,
  Lapis_Input_Button_End,
  Lapis_Input_Button_PageUp,
  Lapis_Input_Button_PageDown,
  Lapis_Input_Button_Lshift,
  Lapis_Input_Button_Rshift,
  Lapis_Input_Button_Lctrl,
  Lapis_Input_Button_Rctrl,
  Lapis_Input_Button_Lalt,
  Lapis_Input_Button_Ralt,
  Lapis_Input_Button_Menu,

  Lapis_Input_Button_Count,
  Lapis_Input_Button_Any = Lapis_Input_Button_Count,

  // Axises =====

  Lapis_Input_Axis_Mouse_Position_X,
  Lapis_Input_Axis_Mouse_Position_Y,
  Lapis_Input_Axis_Mouse_Delta_X,
  Lapis_Input_Axis_Mouse_Delta_Y,

  Lapis_Input_Count
} LapisInputCode;

typedef struct LapisInputState
{
  float values[Lapis_Input_Count];
  bool anyPressed;
} LapisInputState;

#endif // !GEM_LAPIS_DEFINES_H
