cmake_minimum_required(VERSION 3.10)
project(M3z0idClient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(M3z0idClient main.cpp
        ArgParser.h)

add_subdirectory(clip)
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
target_link_libraries(M3z0idClient clip)
if(WIN32)
    set(CMAKE_VS_SDK_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
    target_sources(M3z0idClient PRIVATE M3z0idClient.rc)
endif(WIN32)