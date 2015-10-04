PROJECT( faceHack_project )
cmake_minimum_required(VERSION 2.8)
#set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

set(WITH_FFMPEG ON)
FIND_PACKAGE( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

set(USE_SSE4_INSTRUCTIONS ON)
include(./dlib/cmake)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
