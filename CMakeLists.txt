cmake_minimum_required(VERSION 3.12)
project(game CXX)

if(NOT WIN32)
  message(FATAL_ERROR "Only Windows builds are allowed. WinAPI used")
endif()

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE) # unicode (*_W) WinAPI functions are used

file(GLOB HEADERS include/*.h)
file(GLOB SOURCES source/*.cpp) #bad practice! use full file-list

set(SOURCES ${SOURCES} main.cpp)

add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
