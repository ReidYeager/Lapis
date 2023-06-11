
#include "src/internal.h"

// =====
// Buttons
// =====

void InputProcessInput(LapisWindow _window, LapisInputCode _code, LapisPlatformInputData _data)
{
  _window->currentInputState.values[_code] = _data.value;
  _window->currentInputState.values[Lapis_Input_Button_Count] +=
    _code < Lapis_Input_Button_Count
    && ( _data.value == 1.0f && _window->previousInputState.values[_code] == 0.0f );
}

float LapisInputGetValue(LapisWindow _window, LapisInputCode _code)
{
  return _window->currentInputState.values[_code];
}

float LapisInputGetValueDelta(LapisWindow _window, LapisInputCode _code)
{
  return _window->currentInputState.values[_code] - _window->previousInputState.values[_code];
}

bool LapisInputOnPressed(LapisWindow _window, LapisInputCode _code)
{
  return
    ( _window->currentInputState.values[_code] != 0.0f )
    && ( _window->previousInputState.values[_code] == 0.0f );
}

bool LapisInputOnReleased(LapisWindow _window, LapisInputCode _code)
{
  return
    ( _window->currentInputState.values[_code] == 0.0f )
    && ( _window->previousInputState.values[_code] != 0.0f );
}
