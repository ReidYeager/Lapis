
#include "src/defines.h"

#include <stdlib.h>
#include <stdio.h>

uint64_t LapisFileRead(const char* _file, char** _pData)
{
  FILE* f = NULL;
  uint32_t error = 0;

  error = fopen_s(&f, _file, "rb");
  if (error)
  {
    LapisLogError("Failed to open file : \"%s\"\n", _file);
    *_pData = NULL;
    return 0;
  }

  fseek(f, 0, SEEK_END);
  uint64_t fileSize = ftell(f);
  char* fileDataBuffer = (char*)LapisMemAlloc(fileSize);
  rewind(f);

  uint64_t readFileSize = fread(fileDataBuffer, 1, fileSize, f);
  if (readFileSize != fileSize)
  {
    LapisLogError("File :: Unexpected end of file in \"%s\"\n", _file);

    fileDataBuffer = (char*)LapisMemRealloc(fileDataBuffer, readFileSize);
    fileSize = readFileSize;
  }

  *_pData = fileDataBuffer;
  return fileSize;
}
