cmake_minimum_required(VERSION 3.26)

project(CasioOS CXX C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

file(GLOB SOURCES "*.c" "*.cpp" "*.h")

add_executable(CasioOS ${SOURCES})

target_link_libraries(CasioOS Threads::Threads)