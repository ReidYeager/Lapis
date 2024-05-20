
#if !defined(LAPIS_H)
#define LAPIS_H 1

#if defined(__cplusplus)
extern "C" {
#endif

#include "./lapis_defines.h"

// ============================================================
// Window
// ============================================================

LapisResult LapisWindowInit(LapisWindow* pWindow, LapisWindowInitInfo* const initInfo);
void LapisWindowShutdown(LapisWindow* pWindow);
LapisResult LapisWindowPollEvents(LapisWindow* pWindow); // Defined per-platform directly

//void LapisWindowSetExtents(u32 newWidth, u32 newHeight);
//void LapisWindowSetPosition(i32 newX, i32 newY);
//void LapisWindowSetTitle(const char* newTitle);

// ============================================================
// Input
// ============================================================

bool LapisInputButtonGetState(LapisWindow* pWindow, LapisButtonCode button);
bool LapisInputButtonPressed(LapisWindow* pWindow, LapisButtonCode button);
bool LapisInputButtonReleased(LapisWindow* pWindow, LapisButtonCode button);

void LapisInputMouseGetPosition(LapisWindow* pWindow, i16* outX, i16* outY);
void LapisInputMouseGetDelta(LapisWindow* pWindow, i16* outX, i16* outY);
void LapisInputMouseGetWheel(LapisWindow* pWindow, i16* outX, i16* outY);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // !defined(LAPIS_H)
