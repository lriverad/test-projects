cmake_minimum_required(VERSION 3.10)

# For cross-compiling from Windows with MSYS2; Requires: mingw-w64-x86_64-linux-gnu-gcc
if(WIN32)
if(NOT DEFINED PATH_TO_MSYS)
  set(PATH_TO_MSYS "C:/msys64" CACHE PATH "Path to MSYS2 installation")
endif()

  set(CMAKE_CROSSCOMPILING TRUE)

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_VERSION 1)

  set(CMAKE_SYSTEM_PROCESSOR "x86_64")

  set(CMAKE_C_COMPILER "${PATH_TO_MSYS}/mingw64/bin/x86_64-w64-mingw32-gcc.exe")
  set(CMAKE_CXX_COMPILER "${PATH_TO_MSYS}/mingw64/bin/x86_64-w64-mingw32-g++.exe")
  set(CMAKE_LINKER "${PATH_TO_MSYS}/mingw64/bin/x86_64-w64-mingw32-ld.exe")
endif()

set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_RPATH "$ORIGIN")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/linux/")
