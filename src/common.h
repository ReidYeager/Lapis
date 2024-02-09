#ifndef LAPIS_DEFINES_H_
#define LAPIS_DEFINES_H_

#include "include/lapis_common.h"

#include <stdint.h>

namespace Lapis
{
void OutputMessage(MessageType type, const char* message, ...);
} // namespace Lapis

#define LAPIS_INFO(...) OutputMessage(Message_Info, __VA_ARGS__)
#define LAPIS_DEBUG(...) OutputMessage(Message_Debug, __VA_ARGS__)
#define LAPIS_WARNING(...) OutputMessage(Message_Warning, __VA_ARGS__)
#define LAPIS_ERROR(...) OutputMessage(Message_Error, __VA_ARGS__)
#define LAPIS_FATAL(...) OutputMessage(Message_Fatal, __VA_ARGS__)


#endif // !LAPIS_DEFINES_H_
