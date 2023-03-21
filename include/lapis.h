
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


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GEM_LAPIS_H
