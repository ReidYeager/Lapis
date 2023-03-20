
#ifndef GEM_LAPIS_DEFINES_H
#define GEM_LAPIS_DEFINES_H

#include <stdint.h>

// =====
// Lapis generic
// =====

typedef enum LapisResult
{
  Lapis_Success,
  Lapis_Window_Creation_Failed,
  Lapis_Unknown
} LapisResult;

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

#endif // !GEM_LAPIS_DEFINES_H
