
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT LAPIS_TARGET_PLATFORM)
  if (WIN32)
    set(LAPIS_TARGET_PLATFORM "WIN32")
  else()
    message(FATAL_ERROR "Must compile on windows")
  endif()
endif()


add_library (Lapis STATIC
  "include/lapis.h"
  "include/lapis_defines.h"
  "src/defines.h"
)

## =====
# Win32
## =====
if (LAPIS_TARGET_PLATFORM STREQUAL "WIN32")
  target_sources (Lapis PRIVATE
    "src/window_win32.c"
  )

  target_compile_definitions(Lapis PUBLIC
    LAPIS_PLATFORM_WIN32
  )
endif()

## =====
# Linux desktop
## =====
if (LAPIS_TARGET_PLATFORM STREQUAL "LINUX_DESKTOP")
  target_sources (Lapis PRIVATE
    "src/window_linux.c"
  )

  target_compile_definitions(Lapis PUBLIC
    LAPIS_PLATFORM_LINUX_DT
  )
endif()

set_target_properties(Lapis PROPERTIES LINKER_LANGUAGE C)

target_include_directories (Lapis PUBLIC
  ./include/
  ./src/
)
