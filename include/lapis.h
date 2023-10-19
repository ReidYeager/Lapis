
#ifndef GEM_LAPIS_H
#define GEM_LAPIS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//#pragma warning(disable:4090)

#include "include/lapis_defines.h"

#include <stdbool.h>

// =====
// Console
// =====

void LapisConsolePrintMessage(LapisConsolePrintType _type, const char* _message, ...);
#define LapisLog(msg, ...) \
  LapisConsolePrintMessage(Lapis_Console_Info, "Lapis :: " msg, __VA_ARGS__)
#define LapisLogDebug(msg, ...) \
  LapisConsolePrintMessage(Lapis_Console_Debug, "Lapis :: " msg, __VA_ARGS__)
#define LapisLogWarning(msg, ...) \
  LapisConsolePrintMessage(Lapis_Console_Warning, "Lapis :: " msg, __VA_ARGS__)
#define LapisLogError(msg, ...) \
  LapisConsolePrintMessage(Lapis_Console_Error, "Lapis :: " msg, __VA_ARGS__)
#define LapisLogFatal(msg, ...) \
  LapisConsolePrintMessage(Lapis_Console_Fatal, "Lapis :: " msg, __VA_ARGS__)

// =====
// Memory
// =====

void* LapisMemAlloc(uint64_t _size);
void* LapisMemAllocZero(uint64_t _size);
void* LapisMemRealloc(void* _data, uint64_t _size);
void LapisMemSet(void* _data, uint32_t _value, uint64_t _size);
void LapisMemCopy(void* _src, void* _dst, uint64_t _size);
void LapisMemFree(void* _data);

#define LapisMemAllocSingle(type) (type*)LapisMemAlloc(sizeof(type))
#define LapisMemAllocZeroSingle(type) (type*)LapisMemAllocZero(sizeof(type))
#define LapisMemReallocSingle(source, type) (type*)LapisMemRealloc(source, sizeof(type))

#define LapisMemAllocArray(type, count) (type*)LapisMemAlloc(sizeof(type) * count)
#define LapisMemAllocZeroArray(type, count) (type*)LapisMemAllocZero(sizeof(type) * count)
#define LapisMemReallocArray(source, type, newCount) (type*)LapisMemRealloc(source, sizeof(type) * newCount)

// =====
// System
// =====

void LapisGetSystemInfo(LapisSystemInfo* _pInfo);

// =====
// File system
// =====

uint64_t LapisFileRead(const char* _file, char** _pData);

// =====
// Window
// =====

LapisResult LapisWindowInit(LapisWindowInitInfo _info, LapisWindow* _outWindow);
void LapisWindowShutdown(LapisWindow* _window);
void LapisWindowMarkForClosure(LapisWindow _window);
LapisResult LapisWindowProcessOsEvents(LapisWindow _window);
uint32_t LapisWindowGetWidth(LapisWindow _window);
uint32_t LapisWindowGetHeight(LapisWindow _window);
bool LapisWindowGetResized(LapisWindow _window);
bool LapisWindowGetMinimized(LapisWindow _window);
bool LapisWindowGetVisible(LapisWindow _window);
bool LapisWindowGetShouldClose(LapisWindow _window);

void LapisWindowGetPosition(LapisWindow _window, int32_t* _outX, int32_t* _outY);
void LapisWindowGetExtents(LapisWindow _window, uint32_t* _outX, uint32_t* _outY);
LapisResult LapisWindowSetPosition(LapisWindow _window, uint32_t _xPos, uint32_t _yPos);
LapisResult LapisWindowSetExtents(LapisWindow _window, uint32_t _width, uint32_t _height);

void LapisWindowCursorGetPosition(LapisWindow _window, int32_t* _outX, int32_t* _outY);
void LapisWindowCursorGetVisible(LapisWindow _window, bool* _outVisible);
LapisResult LapisWindowCursorSetPosition(LapisWindow _window, uint32_t _xPos, uint32_t _yPos);
LapisResult LapisWindowCursorSetVisible(LapisWindow _window, bool _visible);

// Vulkan =====
#if (LAPIS_VULKAN)
#include <vulkan/vulkan.h>
void LapisWindowVulkanGetRequiredExtensions(
  uint32_t* _extensionCount,
  const char** _extensionNames);
LapisResult LapisWindowVulkanCreateSurface(
  LapisWindow _window,
  VkInstance _instance,
  VkSurfaceKHR* _surface);
#else
  #pragma message ( "<G> : Vulkan not found and will not be supported in the compiled Lapis.\n" )
  void LapisWindowVulkanGetRequiredExtensions() {}
  void LapisWindowVulkanCreateSurface() {}
#endif // LAPIS_VULKAN

// =====
// Input
// =====
float LapisInputGetValue(LapisWindow _window, LapisInputCode _code);
float LapisInputGetValueDelta(LapisWindow _window, LapisInputCode _code);
bool LapisInputOnPressed(LapisWindow _window, LapisInputCode _code);
bool LapisInputOnReleased(LapisWindow _window, LapisInputCode _code);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GEM_LAPIS_H
