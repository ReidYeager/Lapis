
#ifndef GEM_LAPIS_DEFINES_H_PRIVATE
#define GEM_LAPIS_DEFINES_H_PRIVATE

#include "include/lapis.h"

#include <stdint.h>

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

  WindowPlatformData platform;
} LapisWindow_T;

#endif // !GEM_LAPIS_DEFINES_H_PRIVATE
