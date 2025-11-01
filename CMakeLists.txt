cmake_minimum_required(VERSION 3.10)
project(M3z0idClient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(M3z0idClient src/main.cpp
        src/ArgParser.h
        src/ModifiersForwards.h)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math")

add_subdirectory(clip)
set(CLIP_ENABLE_IMAGE OFF CACHE BOOL "Compile with support to copy/paste images")
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
if(UNIX AND NOT APPLE)
    set(CLIP_X11_WITH_PNG OFF CACHE BOOL "Compile with libpng to support copy/paste image in png format")
endif()

target_link_libraries(M3z0idClient clip)

if(WIN32)
    set(CMAKE_VS_SDK_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
    target_sources(M3z0idClient PRIVATE M3z0idClient.rc)
endif(WIN32)