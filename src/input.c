
#include "src/defines.h"

void InputProcessKeyInput(LapisWindow _window, LapisInputCode _code, PlatformInputData _data)
{
  _window->currentInputState.keys[_code] = _data.isPressed;

  LAPIS_LOG(Lapis_Console_Debug, "Key (%25s) : %s\n", LapisInputCodeStrings[_code], _data.isPressed ? "Pressed" : "Released");
}

