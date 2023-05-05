
#include "src/defines.h"

// =====
// Buttons
// =====

void InputProcessInput(LapisWindow _window, LapisInputCode _code, PlatformInputData _data)
{
  _window->currentInputState.values[_code] = _data.value;
}

float LapisInputGetValue(LapisWindow _window, LapisInputCode _code)
{
  return _window->currentInputState.values[_code];
}

float LapisInputGetValueDelta(LapisWindow _window, LapisInputCode _code)
{
  return _window->currentInputState.values[_code] - _window->previousInputState.values[_code];
}

uint8_t LapisInputOnPressed(LapisWindow _window, LapisInputCode _code)
{
  return
    ( _window->currentInputState.values[_code] != 0.0f )
    && ( _window->previousInputState.values[_code] == 0.0f );
}

uint8_t LapisInputOnReleased(LapisWindow _window, LapisInputCode _code)
{
  return
    ( _window->currentInputState.values[_code] == 0.0f )
    && ( _window->previousInputState.values[_code] != 0.0f );
}
