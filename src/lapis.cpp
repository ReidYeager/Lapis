
#include "src/common.h"
#include <stdarg.h>
#include <stdio.h>

namespace Lapis
{
void(*MessageOutput)(MessageType type, const char* message) = nullptr;

void OutputMessage(MessageType type, const char* message, ...)
{
  if (MessageOutput != nullptr)
  {
    char messageBuffer[1024];

    va_list args;
    va_start(args, message);
    vsnprintf(messageBuffer, 1024, message, args);
    va_end(args);

    MessageOutput(type, messageBuffer);
  }
}

} // namespace Lapis
