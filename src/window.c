
#include "common.h"
#include <stdlib.h>

LapisResult LapisWindowInit(LapisWindow* pWindow, LapisWindowInitInfo* const initInfo)
{
  LapisWindow window = { 0 };
  LapisResult result = Lapis_Success;

  window.pPollEventCallbackFunction = initInfo->pPollEventCallbackFn;

  window.pEventCallbackFn = (initInfo->pEventCallbackFn != NULL) ? initInfo->pEventCallbackFn : EventCallbackNull_Lapis;

  if (WindowPlatformInit_Lapis(&window, initInfo))
  {
    return Lapis_Failure_Sys_Call;
  }

  window.width = initInfo->width;
  window.height = initInfo->height;
  window.posX = initInfo->posX;
  window.posY = initInfo->posY;

  u16 titleLength = strlen(initInfo->title) + 1;
  window.title = (char*)malloc(titleLength);
  if (window.title)
  {
    strcpy_s(window.title, titleLength, initInfo->title);
  }

  window.minimized = false;
  window.shouldClose = false;

  *pWindow = window;
  return result;
}

void LapisWindowShutdown(LapisWindow* pWindow)
{
  WindowPlatformShutdown_Lapis(pWindow);

  free(pWindow->title);
}
