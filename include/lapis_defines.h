
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

#endif // !GEM_LAPIS_DEFINES_H
