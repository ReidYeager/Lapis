
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
  uint8_t shouldClose;

  LapisInputState currentInputState;
  LapisInputState previousInputState;

  WindowPlatformData platform;
} LapisWindow_T;

typedef struct PlatformInputData
{
  uint32_t flags;
  union {
    float valueFloat;
    int32_t valueInt;
    uint32_t valueUint;
  };
} PlatformInputData;

#ifdef LAPIS_PLATFORM_WIN32
static const uint8_t LapisPlatformKeycodeMap[256] = {
  Lapis_Input_Button_Unkown, // 0x00
  Lapis_Input_Mouse_Button_Left,
  Lapis_Input_Mouse_Button_Right,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Mouse_Button_Middle,
  Lapis_Input_Mouse_Button_4,
  Lapis_Input_Mouse_Button_5,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Backspace, // 0x08
  Lapis_Input_Key_Tab,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Numpad_Enter,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Lshift, // 0x10 -- Does not differentiate between L/R
  Lapis_Input_Key_Lctrl, // Does not differentiate between L/R
  Lapis_Input_Key_Lalt, // Does not differentiate between L/R
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_CapsLock,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0x18
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Escape,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Space, // 0x20
  Lapis_Input_Key_PageUp,
  Lapis_Input_Key_PageDown,
  Lapis_Input_Key_End,
  Lapis_Input_Key_Home,
  Lapis_Input_Key_Arrow_Left,
  Lapis_Input_Key_Arrow_Up,
  Lapis_Input_Key_Arrow_Right,
  Lapis_Input_Key_Arrow_Down, // 0x28
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Insert,
  Lapis_Input_Key_Delete,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_0, // 0x30
  Lapis_Input_Key_1,
  Lapis_Input_Key_2,
  Lapis_Input_Key_3,
  Lapis_Input_Key_4,
  Lapis_Input_Key_5,
  Lapis_Input_Key_6,
  Lapis_Input_Key_7,
  Lapis_Input_Key_8, // 0x38
  Lapis_Input_Key_9,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0x40
  Lapis_Input_Key_A,
  Lapis_Input_Key_B,
  Lapis_Input_Key_C,
  Lapis_Input_Key_D,
  Lapis_Input_Key_E,
  Lapis_Input_Key_F,
  Lapis_Input_Key_G,
  Lapis_Input_Key_H, // 0x48
  Lapis_Input_Key_I,
  Lapis_Input_Key_J,
  Lapis_Input_Key_K,
  Lapis_Input_Key_L,
  Lapis_Input_Key_M,
  Lapis_Input_Key_N,
  Lapis_Input_Key_O,
  Lapis_Input_Key_P, // 0x50
  Lapis_Input_Key_Q,
  Lapis_Input_Key_R,
  Lapis_Input_Key_S,
  Lapis_Input_Key_T,
  Lapis_Input_Key_U,
  Lapis_Input_Key_V,
  Lapis_Input_Key_W,
  Lapis_Input_Key_X, // 0x58
  Lapis_Input_Key_Y,
  Lapis_Input_Key_Z,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Menu,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Numpad0, // 0x60
  Lapis_Input_Key_Numpad1,
  Lapis_Input_Key_Numpad2,
  Lapis_Input_Key_Numpad3,
  Lapis_Input_Key_Numpad4,
  Lapis_Input_Key_Numpad5,
  Lapis_Input_Key_Numpad6,
  Lapis_Input_Key_Numpad7,
  Lapis_Input_Key_Numpad8, // 0x68
  Lapis_Input_Key_Numpad9,
  Lapis_Input_Key_Numpad_Muliply,
  Lapis_Input_Key_Numpad_Add,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Numpad_Subtract,
  Lapis_Input_Key_Numpad_Decimal,
  Lapis_Input_Key_Numpad_Divide,
  Lapis_Input_Key_F1, // 0x70
  Lapis_Input_Key_F2,
  Lapis_Input_Key_F3,
  Lapis_Input_Key_F4,
  Lapis_Input_Key_F5,
  Lapis_Input_Key_F6,
  Lapis_Input_Key_F7,
  Lapis_Input_Key_F8,
  Lapis_Input_Key_F9, // 0x78
  Lapis_Input_Key_F10,
  Lapis_Input_Key_F11,
  Lapis_Input_Key_F12,
  Lapis_Input_Key_F13,
  Lapis_Input_Key_F14,
  Lapis_Input_Key_F15,
  Lapis_Input_Key_F16,
  Lapis_Input_Key_F17, // 0x80
  Lapis_Input_Key_F18,
  Lapis_Input_Key_F19,
  Lapis_Input_Key_F20,
  Lapis_Input_Key_F21,
  Lapis_Input_Key_F22,
  Lapis_Input_Key_F23,
  Lapis_Input_Key_F24,
  Lapis_Input_Button_Unkown, // 0x88
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_NumLock, // 0x90
  Lapis_Input_Key_ScrollLock,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0x98
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Lshift, // 0xa0
  Lapis_Input_Key_Rshift,
  Lapis_Input_Key_Lctrl,
  Lapis_Input_Key_Rctrl,
  Lapis_Input_Key_Lalt,
  Lapis_Input_Key_Ralt,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xa8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xb0
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xb8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_SemiColon,
  Lapis_Input_Key_Equals,
  Lapis_Input_Key_Comma,
  Lapis_Input_Key_Hyphen,
  Lapis_Input_Key_Period,
  Lapis_Input_Key_ForwardSlash,
  Lapis_Input_Key_Grave, // 0xc0
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xc8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xd0
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xd8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Key_Lbracket,
  Lapis_Input_Key_Backslash,
  Lapis_Input_Key_Rbracket,
  Lapis_Input_Key_Apostrophe,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xe0
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xe8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xf0
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown, // 0xf8
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown,
  Lapis_Input_Button_Unkown
};
#else
static const uint8_t LapisPlatformKeycodeMap[256] = { 0 };
#endif

static const char* LapisInputCodeStrings[] = {
  "Lapis_Input_Button_Unkown",
  "Lapis_Input_Key_A",
  "Lapis_Input_Key_B",
  "Lapis_Input_Key_C",
  "Lapis_Input_Key_D",
  "Lapis_Input_Key_E",
  "Lapis_Input_Key_F",
  "Lapis_Input_Key_G",
  "Lapis_Input_Key_H",
  "Lapis_Input_Key_I",
  "Lapis_Input_Key_J",
  "Lapis_Input_Key_K",
  "Lapis_Input_Key_L",
  "Lapis_Input_Key_M",
  "Lapis_Input_Key_N",
  "Lapis_Input_Key_O",
  "Lapis_Input_Key_P",
  "Lapis_Input_Key_Q",
  "Lapis_Input_Key_R",
  "Lapis_Input_Key_S",
  "Lapis_Input_Key_T",
  "Lapis_Input_Key_U",
  "Lapis_Input_Key_V",
  "Lapis_Input_Key_W",
  "Lapis_Input_Key_X",
  "Lapis_Input_Key_Y",
  "Lapis_Input_Key_Z",
  "Lapis_Input_Key_1",
  "Lapis_Input_Key_2",
  "Lapis_Input_Key_3",
  "Lapis_Input_Key_4",
  "Lapis_Input_Key_5",
  "Lapis_Input_Key_6",
  "Lapis_Input_Key_7",
  "Lapis_Input_Key_8",
  "Lapis_Input_Key_9",
  "Lapis_Input_Key_0",
  "Lapis_Input_Key_Numpad1",
  "Lapis_Input_Key_Numpad2",
  "Lapis_Input_Key_Numpad3",
  "Lapis_Input_Key_Numpad4",
  "Lapis_Input_Key_Numpad5",
  "Lapis_Input_Key_Numpad6",
  "Lapis_Input_Key_Numpad7",
  "Lapis_Input_Key_Numpad8",
  "Lapis_Input_Key_Numpad9",
  "Lapis_Input_Key_Numpad0",
  "Lapis_Input_Key_Numpad_Muliply",
  "Lapis_Input_Key_Numpad_Add",
  "Lapis_Input_Key_Numpad_Subtract",
  "Lapis_Input_Key_Numpad_Decimal",
  "Lapis_Input_Key_Numpad_Divide",
  "Lapis_Input_Key_Numpad_Enter",
  "Lapis_Input_Key_F1",
  "Lapis_Input_Key_F2",
  "Lapis_Input_Key_F3",
  "Lapis_Input_Key_F4",
  "Lapis_Input_Key_F5",
  "Lapis_Input_Key_F6",
  "Lapis_Input_Key_F7",
  "Lapis_Input_Key_F8",
  "Lapis_Input_Key_F9",
  "Lapis_Input_Key_F10",
  "Lapis_Input_Key_F11",
  "Lapis_Input_Key_F12",
  "Lapis_Input_Key_F13",
  "Lapis_Input_Key_F14",
  "Lapis_Input_Key_F15",
  "Lapis_Input_Key_F16",
  "Lapis_Input_Key_F17",
  "Lapis_Input_Key_F18",
  "Lapis_Input_Key_F19",
  "Lapis_Input_Key_F20",
  "Lapis_Input_Key_F21",
  "Lapis_Input_Key_F22",
  "Lapis_Input_Key_F23",
  "Lapis_Input_Key_F24",
  "Lapis_Input_Key_Arrow_Up",
  "Lapis_Input_Key_Arrow_Down",
  "Lapis_Input_Key_Arrow_Right",
  "Lapis_Input_Key_Arrow_Left",
  "Lapis_Input_Key_Grave",
  "Lapis_Input_Key_Hyphen",
  "Lapis_Input_Key_Equals",
  "Lapis_Input_Key_Lbracket",
  "Lapis_Input_Key_Rbracket",
  "Lapis_Input_Key_Backslash",
  "Lapis_Input_Key_SemiColon",
  "Lapis_Input_Key_Apostrophe",
  "Lapis_Input_Key_Comma",
  "Lapis_Input_Key_Period",
  "Lapis_Input_Key_ForwardSlash",
  "Lapis_Input_Key_Escape",
  "Lapis_Input_Key_Enter",
  "Lapis_Input_Key_Space",
  "Lapis_Input_Key_Backspace",
  "Lapis_Input_Key_Tab",
  "Lapis_Input_Key_CapsLock",
  "Lapis_Input_Key_NumLock",
  "Lapis_Input_Key_ScrollLock",
  "Lapis_Input_Key_Insert",
  "Lapis_Input_Key_Delete",
  "Lapis_Input_Key_Home",
  "Lapis_Input_Key_End",
  "Lapis_Input_Key_PageUp",
  "Lapis_Input_Key_PageDown",
  "Lapis_Input_Key_Lshift",
  "Lapis_Input_Key_Rshift",
  "Lapis_Input_Key_Lctrl",
  "Lapis_Input_Key_Rctrl",
  "Lapis_Input_Key_Lalt",
  "Lapis_Input_Key_Ralt",
  "Lapis_Input_Key_Menu",
  "Lapis_Input_Count"
};

#endif // !GEM_LAPIS_DEFINES_H_PRIVATE
