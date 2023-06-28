
#include "src/defines.h"

#include <stdio.h>
#include <stdarg.h>

#define MAX_CONSOLE_MESSAGE_LENGTH 0x1000 // 4096 character limit
char messageBuffer[MAX_CONSOLE_MESSAGE_LENGTH];

void LapisConsolePrintMessage(LapisConsolePrintType _type, const char* _message, ...)
{
  va_list pArguments;
  va_start(pArguments, _message);
  vsnprintf(messageBuffer, MAX_CONSOLE_MESSAGE_LENGTH, _message, pArguments);
  va_end(pArguments);

  //                    Debug, Info , Warning, Error , Fatal
  //                    Cyan , White, Yellow , Red   , White-on-Red
  uint32_t colors[] = { 0xb  , 0xf  , 0xe    , 0x4   , 0xcf };

  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(console, colors[_type]);
  OutputDebugStringA(messageBuffer);
  uint64_t length = strlen(messageBuffer);
  LPDWORD written = 0;
  WriteConsoleA(console, messageBuffer, (DWORD)length, written, 0);
  SetConsoleTextAttribute(console, 0xf);
}
