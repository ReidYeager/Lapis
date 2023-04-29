
#include "src/defines.h"

void InputProcessKeyInput(LapisWindow _window, LapisInputCode _code, PlatformInputData _data)
{
  _window->currentInputState.keys[_code] = _data.isPressed;
}

uint8_t LapisInputGetInput(LapisWindow _window, LapisInputCode _code)
{
  return (_window->currentInputState.keys[_code] != 0);
}

uint8_t LapisInputGetInputWasPressed(LapisWindow _window, LapisInputCode _code)
{
  return
    (_window->currentInputState.keys[_code] == 1)
    && ( _window->previousInputState.keys[_code] == 0 );
}

uint8_t LapisInputGetInputWasReleased(LapisWindow _window, LapisInputCode _code)
{
  return
    ( _window->currentInputState.keys[_code] == 0 )
    && ( _window->previousInputState.keys[_code] == 1 );
}
