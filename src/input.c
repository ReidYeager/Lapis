
#include "common.h"

void EventCallbackNull_Lapis(LapisEventType type, void* data) { }

bool LapisInputButtonGetState(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  return (pWindow->input.curState.buttons[index] & bit) != 0;
}

bool LapisInputButtonPressed(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  return (pWindow->input.curState.buttons[index] & bit) && !(pWindow->input.prevState.buttons[index] & bit);
}

bool LapisInputButtonReleased(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  return !(pWindow->input.curState.buttons[index] & bit) && (pWindow->input.prevState.buttons[index] & bit);
}

void LapisInputMouseGetPosition(LapisWindow* pWindow, i16* outX, i16* outY)
{
  *outX = pWindow->input.curState.mousePos[0];
  *outY = pWindow->input.curState.mousePos[1];
}

void LapisInputMouseGetDelta(LapisWindow* pWindow, i16* outX, i16* outY)
{
  *outX = pWindow->input.curState.mousePos[0] - pWindow->input.prevState.mousePos[0];
  *outY = pWindow->input.curState.mousePos[1] - pWindow->input.prevState.mousePos[1];
}

void LapisInputMouseGetWheel(LapisWindow* pWindow, i16* outX, i16* outY)
{
  *outX = pWindow->input.curState.mouseScroll[0];
  *outY = pWindow->input.curState.mouseScroll[1];
}

void InputUpdateState_Lapis(LapisWindow* pWindow)
{
  pWindow->input.prevState = pWindow->input.curState;

  pWindow->input.curState.mouseScroll[0] = 0;
  pWindow->input.curState.mouseScroll[1] = 0;
}

void InputHandleButtonPress_Lapis(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  pWindow->input.curState.buttons[index] |= bit;

  LapisEventInputButtonPress e = { button };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Button_Press, &e);
}

void InputHandleButtonRepeat_Lapis(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  pWindow->input.curState.buttons[index] |= bit;

  LapisEventInputButtonRepeat e = { button };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Button_Repeat, &e);
}

void InputHandleButtonRelease_Lapis(LapisWindow* pWindow, LapisButtonCode button)
{
  u8 index = button >> 6; // button/64
  u64 bit = 1ll << (button & 63); // 1 << (button % 64)
  pWindow->input.curState.buttons[index] &= ~bit;

  LapisEventInputButtonRelease e = { button };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Button_Release, &e);
}

void InputHandleMouseMove_Lapis(LapisWindow* pWindow, i16 posX, i16 posY)
{
  pWindow->input.curState.mousePos[0] = posX;
  pWindow->input.curState.mousePos[1] = posY;

  LapisEventInputMouseMove e = { posX, posY };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Mouse_Move, &e);
}

void InputHandleMouseScrollX_Lapis(LapisWindow* pWindow, i16 amount)
{
  pWindow->input.curState.mouseScroll[0] += amount;

  LapisEventInputMouseScroll e = { amount, 0 };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Mouse_Scroll, &e);
}

void InputHandleMouseScrollY_Lapis(LapisWindow* pWindow, i16 amount)
{
  pWindow->input.curState.mouseScroll[1] += amount;

  LapisEventInputMouseScroll e = { 0, amount };
  pWindow->pEventCallbackFn(Lapis_Event_Input_Mouse_Scroll, &e);
}

void InputHandleMousePress_Lapis(LapisWindow* pWindow, u8 mouseButtonIndex)
{
  InputHandleButtonPress_Lapis(pWindow, Lapis_Mouse_0 + mouseButtonIndex);
}

void InputHandleMouseRelease_Lapis(LapisWindow* pWindow, u8 mouseButtonIndex)
{
  InputHandleButtonRelease_Lapis(pWindow, Lapis_Mouse_0 + mouseButtonIndex);
}
