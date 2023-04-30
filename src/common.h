
#ifndef GEM_LAPIS_COMMON_H_PRIVATE
#define GEM_LAPIS_COMMON_H_PRIVATE

#include "src/defines.h"

// =====
// Input
// =====

void InputProcessButtonInput(
  LapisWindow _window,
  LapisInputButtonCode _code,
  PlatformInputData _data);
void InputProcessAxisInput(LapisWindow _window, LapisInputAxisCode _code, PlatformInputData _data);

#endif // !GEM_LAPIS_COMMON_H_PRIVATE
