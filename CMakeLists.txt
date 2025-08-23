cmake_minimum_required(VERSION 3.10)
project(OzneInjector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/pornomon)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/pornomon)

include_directories(include)

file(GLOB_RECURSE LIB_SOURCES "src/core/*.cpp" "src/functions/**/*.cpp" "src/utils/*.cpp")
add_library(pornozne SHARED ${LIB_SOURCES})
set_target_properties(pornozne PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_executable(ozne-inject main.cpp)

target_link_libraries(pornozne PRIVATE dl)
target_link_libraries(ozne-inject PRIVATE dl)
