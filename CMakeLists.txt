cmake_minimum_required(VERSION 3.25)

project(CasioOS CXX C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
# sudo apt install libsdl2-dev
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "*.c" "*.cpp" "*.h")

add_executable(CasioOS ${SOURCES})

target_link_libraries(CasioOS Threads::Threads ${SDL2_LIBRARIES})