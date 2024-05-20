
cmake_minimum_required (VERSION 3.20)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.h")
file(GLOB_RECURSE CSourceFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.c")

add_library (lapis STATIC
  ${HeaderFiles}
  ${CSourceFiles}
)

target_include_directories (lapis PUBLIC
  ./src/
  ./include/Lapis/
)

set_target_properties(lapis PROPERTIES LINKER_LANGUAGE C)
