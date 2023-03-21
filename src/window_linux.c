
#include "src/defines.h"

#include <stdio.h>

LapisResult LapisCreateWindow(LapisCreateWindowInfo _info, LapisWindow* _outWindow)
{
  printf("Lapis create window LINUX : %d\n", _info.x);

  return Lapis_Success;
}
