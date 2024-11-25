cmake_minimum_required(VERSION 3.10)

# For cross-compiling from Linux; Requires: mingw64-gcc, mingw64-gcc-c++
if(UNIX)
if(NOT DEFINED PATH_TO_MINGW)
  set(PATH_TO_MINGW "/usr/x86_64-w64-mingw32" CACHE PATH "Path to MinGW installation")
endif()

  set(CMAKE_CROSSCOMPILING TRUE)

  set(CMAKE_SYSTEM_NAME Windows)
  set(CMAKE_SYSTEM_VERSION 10)

  set(CMAKE_SYSTEM_PROCESSOR "x86_64")

  set(CMAKE_C_COMPILER "x86_64-w64-mingw32-gcc")
  set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-g++")
  set(CMAKE_LINKER "${PATH_TO_MINGW}/bin/ld")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/windows/")
