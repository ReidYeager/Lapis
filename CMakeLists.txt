
cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/**.h")
file(GLOB_RECURSE CSourceFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

add_library (lapis STATIC
  ${HeaderFiles}
  ${CSourceFiles}
)

target_include_directories (lapis PUBLIC
  ./
)

#set_target_properties(lapis PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(lapis PUBLIC GEM_LAPIS=1)

if (WIN32)
  target_compile_definitions(lapis PUBLIC "LAPIS_PLATFORM_WIN32")
else()
  message(FATAL_ERROR "Lapis currently only supports Windows")
endif()
