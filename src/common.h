
#if !defined(LAPIS_COMMON_H)
#define LAPIS_COMMON_H 1

#include "lapis.h"

bool WindowPlatformInit_Lapis(LapisWindow* pWindow, LapisWindowInitInfo* const initInfo);
void WindowPlatformShutdown_Lapis(LapisWindow* pWindow);

void EventCallbackNull_Lapis(LapisEventType type, void* data);

void InputUpdateState_Lapis(LapisWindow* pWindow);
void InputHandleButtonPress_Lapis(LapisWindow* pWindow, LapisButtonCode button);
void InputHandleButtonRelease_Lapis(LapisWindow* pWindow, LapisButtonCode button);
void InputHandleMouseMove_Lapis(LapisWindow* pWindow, i16 posX, i16 posY);
void InputHandleMouseScrollX_Lapis(LapisWindow* pWindow, i16 amount);
void InputHandleMouseScrollY_Lapis(LapisWindow* pWindow, i16 amount);
void InputHandleMousePress_Lapis(LapisWindow* pWindow, u8 mouseButtonIndex);
void InputHandleMouseRelease_Lapis(LapisWindow* pWindow, u8 mouseButtonIndex);

#endif // !LAPIS_COMMON_H
