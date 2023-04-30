
#include "src/defines.h"

// =====
// Buttons
// =====

void InputProcessButtonInput(
  LapisWindow _window,
  LapisInputButtonCode _code,
  PlatformInputData _data)
{
  _window->currentInputState.buttons[_code] = _data.valueUint;
}

uint8_t LapisInputGetButton(LapisWindow _window, LapisInputButtonCode _code)
{
  return ( _window->currentInputState.buttons[_code] != 0 );
}

uint8_t LapisInputGetButtonWasPressed(LapisWindow _window, LapisInputButtonCode _code)
{
  return
    ( _window->currentInputState.buttons[_code] == 1 )
    && ( _window->previousInputState.buttons[_code] == 0 );
}

uint8_t LapisInputGetButtonWasReleased(LapisWindow _window, LapisInputButtonCode _code)
{
  return
    ( _window->currentInputState.buttons[_code] == 0 )
    && ( _window->previousInputState.buttons[_code] == 1 );
}

// =====
// Axises
// =====

void InputProcessAxisInput(LapisWindow _window, LapisInputAxisCode _code, PlatformInputData _data)
{
  _window->currentInputState.axises[_code] = _data.valueFloat;
}

float LapisInputGetAxis(LapisWindow _window, LapisInputAxisCode _code)
{
  return _window->currentInputState.axises[_code];
}

float LapisInputGetAxisDelta(LapisWindow _window, LapisInputAxisCode _code)
{
  return _window->currentInputState.axises[_code] - _window->previousInputState.axises[_code];
}

