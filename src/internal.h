
#ifndef GEM_LAPIS_INTERNAL_H_PRIVATE
#define GEM_LAPIS_INTERNAL_H_PRIVATE

#include "include/lapis.h"
#include "src/defines.h"

// =====
// Input
// =====

typedef struct LapisPlatformInputData
{
  uint32_t flags;
  float value;
} LapisPlatformInputData;

void InputProcessInput(LapisWindow _window, LapisInputCode _code, LapisPlatformInputData _data);

#endif // !GEM_LAPIS_INTERNAL_H_PRIVATE
