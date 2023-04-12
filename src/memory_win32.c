
#include "src/defines.h"

#include <stdlib.h>

void* LapisMemAlloc(uint64_t _size)
{
  return malloc(_size);
}

void* LapisMemAllocZero(uint64_t _size)
{
  void* data = LapisMemAlloc(_size);
  LapisMemSet(data, 0, _size);
  return data;
}

void* LapisMemRealloc(void* _data, uint64_t _size)
{
  return realloc(_data, _size);
}

void LapisMemSet(void* _data, uint32_t _value, uint64_t _size)
{
  memset(_data, _value, _size);
}

void LapisMemCopy(void* _src, void* _dst, uint64_t _size)
{
  memcpy(_dst, _src, _size);
}

void LapisMemFree(void* _data)
{
  free(_data);
}

