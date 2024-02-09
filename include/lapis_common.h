#ifndef LAPIS_DEFINES_H
#define LAPIS_DEFINES_H

enum LapisResult
{
  Lapis_Success,
  Lapis_Failure,
  Lapis_Failure_Invalid_Input,
  Lapis_Failure_Platform
};

namespace Lapis
{

enum MessageType
{
  Message_Info,
  Message_Debug,
  Message_Warning,
  Message_Error,
  Message_Fatal
};

} // namespace Lapis

#endif // !LAPIS_DEFINES_H
