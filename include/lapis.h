
#ifndef GEM_LAPIS_H
#define GEM_LAPIS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#include "include/lapis_defines.h"

// =====
// Console
// =====

void LapisConsolePrintMessage(LapisConsolePrintType _type, const char* _message, ...);
#define LapisLog(msg, ...) LapisConsolePrintMessage(Lapis_Console_Info, msg, __VA_ARGS__)
#define LapisLogDebug(msg, ...) LapisConsolePrintMessage(Lapis_Console_Debug, msg, __VA_ARGS__)
#define LapisLogWarning(msg, ...) LapisConsolePrintMessage(Lapis_Console_Warning, msg, __VA_ARGS__)
#define LapisLogError(msg, ...) LapisConsolePrintMessage(Lapis_Console_Error, msg, __VA_ARGS__)
#define LapisLogFatal(msg, ...) LapisConsolePrintMessage(Lapis_Console_Fatal, msg, __VA_ARGS__)

// =====
// Memory
// =====

void* LapisMemAlloc(uint64_t _size);
void* LapisMemAllocZero(uint64_t _size);
void LapisMemSet(void* _data, uint32_t _value, uint64_t _size);
void LapisMemCopy(void* _src, void* _dst, uint64_t _size);
void LapisMemFree(void* _data);

// =====
// Window
// =====

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow);
void LapisDestroyWindow(LapisWindow* _window);

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


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GEM_LAPIS_H
