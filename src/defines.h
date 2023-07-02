
#ifndef GEM_LAPIS_DEFINES_H_PRIVATE
#define GEM_LAPIS_DEFINES_H_PRIVATE

#include "include/lapis.h"

#include <stdint.h>

#define LAPIS_ATTEMPT(fn, failureAction) \
{                                        \
  LapisResult attemptResult = (fn);      \
  if (attemptResult != Lapis_Success)    \
  {                                      \
    failureAction;                       \
  }                                      \
}

#define LAPIS_LOG(type, msg, ...) LapisConsolePrintMessage(type, "Lapis :: " msg, __VA_ARGS__)

// =====
// Window
// =====

#ifdef LAPIS_PLATFORM_WIN32
#include <windows.h>
#include <windowsx.h>
typedef struct WindowPlatformData
{
  HWND hwnd;
  HINSTANCE hinstance;
} WindowPlatformData;
#else
typedef struct WindowPlatformData
{
  int x;
} WindowPlatformData;
#endif // LAPIS_PLATFORM_XXX

typedef struct LapisWindow_T
{
  uint32_t width;
  uint32_t height;
  bool shouldClose;

  LapisInputState currentInputState;
  LapisInputState previousInputState;

  WindowPlatformData platform;
} LapisWindow_T;

#ifdef LAPIS_PLATFORM_WIN32
static const uint16_t LapisPlatformKeycodeMap[256] = {
  Lapis_Input_Unknown, // 0x00
  Lapis_Input_Button_Mouse_Left,
  Lapis_Input_Button_Mouse_Right,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Mouse_Middle,
  Lapis_Input_Button_Mouse_4,
  Lapis_Input_Button_Mouse_5,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Backspace, // 0x08
  Lapis_Input_Button_Tab,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Numpad_Enter,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Lshift, // 0x10 -- Does not differentiate between L/R
  Lapis_Input_Button_Lctrl, // Does not differentiate between L/R
  Lapis_Input_Button_Lalt, // Does not differentiate between L/R
  Lapis_Input_Unknown,
  Lapis_Input_Button_CapsLock,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0x18
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Escape,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Space, // 0x20
  Lapis_Input_Button_PageUp,
  Lapis_Input_Button_PageDown,
  Lapis_Input_Button_End,
  Lapis_Input_Button_Home,
  Lapis_Input_Button_Arrow_Left,
  Lapis_Input_Button_Arrow_Up,
  Lapis_Input_Button_Arrow_Right,
  Lapis_Input_Button_Arrow_Down, // 0x28
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Insert,
  Lapis_Input_Button_Delete,
  Lapis_Input_Unknown,
  Lapis_Input_Button_0, // 0x30
  Lapis_Input_Button_1,
  Lapis_Input_Button_2,
  Lapis_Input_Button_3,
  Lapis_Input_Button_4,
  Lapis_Input_Button_5,
  Lapis_Input_Button_6,
  Lapis_Input_Button_7,
  Lapis_Input_Button_8, // 0x38
  Lapis_Input_Button_9,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0x40
  Lapis_Input_Button_A,
  Lapis_Input_Button_B,
  Lapis_Input_Button_C,
  Lapis_Input_Button_D,
  Lapis_Input_Button_E,
  Lapis_Input_Button_F,
  Lapis_Input_Button_G,
  Lapis_Input_Button_H, // 0x48
  Lapis_Input_Button_I,
  Lapis_Input_Button_J,
  Lapis_Input_Button_K,
  Lapis_Input_Button_L,
  Lapis_Input_Button_M,
  Lapis_Input_Button_N,
  Lapis_Input_Button_O,
  Lapis_Input_Button_P, // 0x50
  Lapis_Input_Button_Q,
  Lapis_Input_Button_R,
  Lapis_Input_Button_S,
  Lapis_Input_Button_T,
  Lapis_Input_Button_U,
  Lapis_Input_Button_V,
  Lapis_Input_Button_W,
  Lapis_Input_Button_X, // 0x58
  Lapis_Input_Button_Y,
  Lapis_Input_Button_Z,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Menu,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Numpad0, // 0x60
  Lapis_Input_Button_Numpad1,
  Lapis_Input_Button_Numpad2,
  Lapis_Input_Button_Numpad3,
  Lapis_Input_Button_Numpad4,
  Lapis_Input_Button_Numpad5,
  Lapis_Input_Button_Numpad6,
  Lapis_Input_Button_Numpad7,
  Lapis_Input_Button_Numpad8, // 0x68
  Lapis_Input_Button_Numpad9,
  Lapis_Input_Button_Numpad_Muliply,
  Lapis_Input_Button_Numpad_Add,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Numpad_Subtract,
  Lapis_Input_Button_Numpad_Decimal,
  Lapis_Input_Button_Numpad_Divide,
  Lapis_Input_Button_F1, // 0x70
  Lapis_Input_Button_F2,
  Lapis_Input_Button_F3,
  Lapis_Input_Button_F4,
  Lapis_Input_Button_F5,
  Lapis_Input_Button_F6,
  Lapis_Input_Button_F7,
  Lapis_Input_Button_F8,
  Lapis_Input_Button_F9, // 0x78
  Lapis_Input_Button_F10,
  Lapis_Input_Button_F11,
  Lapis_Input_Button_F12,
  Lapis_Input_Button_F13,
  Lapis_Input_Button_F14,
  Lapis_Input_Button_F15,
  Lapis_Input_Button_F16,
  Lapis_Input_Button_F17, // 0x80
  Lapis_Input_Button_F18,
  Lapis_Input_Button_F19,
  Lapis_Input_Button_F20,
  Lapis_Input_Button_F21,
  Lapis_Input_Button_F22,
  Lapis_Input_Button_F23,
  Lapis_Input_Button_F24,
  Lapis_Input_Unknown, // 0x88
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_NumLock, // 0x90
  Lapis_Input_Button_ScrollLock,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0x98
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Lshift, // 0xa0
  Lapis_Input_Button_Rshift,
  Lapis_Input_Button_Lctrl,
  Lapis_Input_Button_Rctrl,
  Lapis_Input_Button_Lalt,
  Lapis_Input_Button_Ralt,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xa8
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xb0
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xb8
  Lapis_Input_Unknown,
  Lapis_Input_Button_SemiColon,
  Lapis_Input_Button_Equals,
  Lapis_Input_Button_Comma,
  Lapis_Input_Button_Hyphen,
  Lapis_Input_Button_Period,
  Lapis_Input_Button_ForwardSlash,
  Lapis_Input_Button_Grave, // 0xc0
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xc8
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xd0
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xd8
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Button_Lbracket,
  Lapis_Input_Button_Backslash,
  Lapis_Input_Button_Rbracket,
  Lapis_Input_Button_Apostrophe,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xe0
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xe8
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xf0
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown, // 0xf8
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown,
  Lapis_Input_Unknown
};
#else
static const bool LapisPlatformKeycodeMap[256] = { 0 };
#endif

#endif // !GEM_LAPIS_DEFINES_H_PRIVATE
