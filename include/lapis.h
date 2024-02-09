#ifndef LAPIS_H
#define LAPIS_H

#include "include/lapis_common.h"
#include "include/window/window.h"

namespace Lapis
{

// Default nullptr
// Set to handle logging in the user application
extern void(*MessageOutput)(MessageType type, const char* message);

} // namespace Lapis

#endif // !LAPIS_H
