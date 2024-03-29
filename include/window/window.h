#ifndef LAPIS_WINDOW_H
#define LAPIS_WINDOW_H

#include "include/lapis_common.h"
#include "include/events/event.h"

#ifdef LAPIS_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#undef CreateWindow
#undef max
#undef min
#endif // LAPIS_PLATFORM_*

#include <functional>
#include <optional>

namespace Lapis
{

struct WindowInitInfo
{
  struct
  {
    uint32_t width, height;
  } extents;

  struct
  {
    int32_t x, y;
  } position;

  const char* title;
  std::function<void(Event&)> eventCallbackFunction;

#ifdef LAPIS_PLATFORM_WIN32
  // Optional callback for accessing raw platform event polling
  std::optional<std::function<void(HWND, uint32_t, WPARAM, LPARAM)>> platformPollInjection;
#else
  // Optional callback for accessing raw platform event polling
  std::optional<std::function<void()>> platformPollInjection;
#endif // LAPIS_PLATFORM_*
};

#ifdef LAPIS_PLATFORM_WIN32
struct WindowPlatformInfo
{
  HWND hwnd;
  HINSTANCE hinstance;
};
typedef void(*InputCallbackFunction_T)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#include "include/window/window_win32.inl"
#else
struct WindowPlatformInfo
{
  char none;
};
#include "include/window/window.inl"
#endif // LAPIS_PLATFORM_*

} // namespace Lapis

#endif // !LAPIS_WINDOW_H
