
#ifndef GEM_LAPIS_H
#define GEM_LAPIS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//#pragma warning(disable:4090)

#include "include/lapis_defines.h"

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
void LapisMemSet(const void* _data, uint32_t _value, uint64_t _size);
void LapisMemCopy(const void* _src, void* _dst, uint64_t _size);
void LapisMemFree(const void* _data);

#define LapisMemAllocShort(type, count) (type*)LapisMemAlloc(sizeof(type) * count)
#define LapisMemAllocZeroShort(type, count) (type*)LapisMemAllocZero(sizeof(type) * count)

// =====
// File system
// =====

uint64_t LapisFileRead(const char* _file, char** _pData);

// =====
// Window
// =====

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow);
void LapisDestroyWindow(LapisWindow* _window);
void LapisWindowMarkForClosure(LapisWindow _window);
LapisResult LapisWindowProcessOsEvents(LapisWindow _window);
uint32_t LapisWindowGetWidth(LapisWindow _window);
uint32_t LapisWindowGetHeight(LapisWindow _window);
uint8_t LapisWindowGetShouldClose(LapisWindow _window);

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
uint8_t LapisInputOnPressed(LapisWindow _window, LapisInputCode _code);
uint8_t LapisInputOnReleased(LapisWindow _window, LapisInputCode _code);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GEM_LAPIS_H
