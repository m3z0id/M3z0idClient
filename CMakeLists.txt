cmake_minimum_required(VERSION 3.0.0)
project(M3z0idClient VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(M3z0idClient main.cpp)

add_subdirectory(clip)
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
target_link_libraries(M3z0idClient clip)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
