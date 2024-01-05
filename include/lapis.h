#ifndef LAPIS_H
#define LAPIS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "lapis_defines.h"

// ============================================================
// Window
// ============================================================

LapisWindow LapisWindowInit(uint32_t width, uint32_t height, const char* title);
void LapisWindowShutdown(LapisWindow* window);
void LapisWindowUpdate(LapisWindow* window);

// ============================================================
// Input
// ============================================================

inline bool LapisButtonPressed(const LapisWindow window, const LapisButtonCode button)
{
  uint8_t index = (int8_t)(button >> 6);
  uint64_t bit = (1ll << (button % 64));
  return (window.input.currentState.buttons[index] & bit) && !(window.input.previousState.buttons[index] & bit);
}

inline bool LapisButtonReleased(const LapisWindow window, const LapisButtonCode button)
{
  uint8_t index = (int8_t)(button >> 6);
  uint64_t bit = (1ll << (button % 64));
  return !(window.input.currentState.buttons[index] & bit) && (window.input.previousState.buttons[index] & bit);
}

inline bool LapisButtonChanged(const LapisWindow window, const LapisButtonCode button)
{
  uint8_t index = (int8_t)(button >> 6);
  uint64_t bit = (1ll << (button % 64));
  return (window.input.currentState.buttons[index] & bit) != (window.input.previousState.buttons[index] & bit);
}

inline bool LapisButtonStatus(const LapisWindow window, const LapisButtonCode button)
{
  uint8_t index = (int8_t)(button >> 6);
  uint64_t bit = (1ll << (button % 64));
  return (window.input.currentState.buttons[index] & bit) != 0;
}

inline LapisMouseDelta LapisGetMouseDelta(const LapisWindow window)
{
  return (LapisMouseDelta) {
    window.input.currentState.mousePosX - window.input.previousState.mousePosX,
      window.input.currentState.mousePosY - window.input.previousState.mousePosY
  };
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // !LAPIS_H
