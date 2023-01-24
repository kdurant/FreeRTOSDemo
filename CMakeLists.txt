cmake_minimum_required(VERSION 3.10)
set(projectName FreeRTOS_linux)
project(${projectName})

# include(auto_version.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin) set(LIBRARY_OUTPUT_PATH
# ${CMAKE_SOURCE_DIR}/bin)

include_directories(
  ${CMAKE_SOURCE_DIR}/Source/include
  ${CMAKE_SOURCE_DIR}/Source/portable/MemMang
  ${CMAKE_SOURCE_DIR}/Source/portable/GCC/POSIX ${CMAKE_SOURCE_DIR}/Project)

# link_directories (${CMAKE_SOURCE_DIR}/build/archive)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
# set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m32")
# set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -m32")

add_compile_options(
  -W
  -Wall
  -Wextra
  -Wformat
  -Wmissing-braces
  -Wno-cast-align
  -Wparentheses
  -Wshadow
  -Wno-sign-compare
  -Wswitch
  -Wuninitialized
  -Wunknown-pragmas
  -Wunused-function
  -Wunused-label
  -Wunused-parameter
  -Wunused-value
  -Wunused-variable
  -Wmissing-prototypes
  -m32
  -DDEBUG=1
  -g
  -UUSE_STDIO
  -D__GCC_POSIX__=1
  -pthread
  -DMAX_NUMBER_OF_TASKS=300)

add_executable(
  ${projectName}
  ./Source/croutine.c
  ./Source/event_groups.c
  ./Source/list.c
  ./Source/queue.c
  ./Source/tasks.c
  ./Source/timers.c
  ./Source/portable/MemMang/heap_3.c
  ./Source/portable/GCC/POSIX/port.c
  ./Project/main.c)
