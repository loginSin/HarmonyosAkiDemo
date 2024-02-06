# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(MyOhosAkiDemo)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(aki)
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(entry SHARED CppEngine.cpp OhosAkiAdapter.cpp)
target_link_libraries(entry PUBLIC libace_napi.z.so aki_jsbind)