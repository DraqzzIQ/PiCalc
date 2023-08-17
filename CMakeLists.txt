cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(PICO_BOARD pico_w)
set(PROJECT_NAME "CasioOS")

# Pico
if(true)
    include(pico_sdk_import.cmake) # must be included before project()
endif()

project(${PROJECT_NAME} CXX C)

# import source files
file(GLOB SOURCES "*.c" "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

# Linux, (Windows)
if(NOT true)
    find_package(Threads REQUIRED)
    
    find_package(SDL2 REQUIRED) # sudo apt install libsdl2-dev to install

    include_directories(${SDL2_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME} Threads::Threads ${SDL2_LIBRARIES})
endif()

# Pico
# cmake -Dtrue=ON to compile
if(true)
    # initialize the Raspberry Pi Pico SDK
    pico_sdk_init()

    # Add pico_stdlib library which aggregates commonly used features 
    # pico_cyw43_arch_none is nessessary for accessing the CYW4343W WiFi chip and it's LED
    target_link_libraries(${PROJECT_NAME} pico_stdlib pico_cyw43_arch_none hardware_i2c)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(${PROJECT_NAME})

    # redirect standart output to UART
    pico_enable_stdio_usb(${PROJECT_NAME} 0)
    pico_enable_stdio_uart(${PROJECT_NAME} 1)

    # preprocessor macro
    target_compile_definitions(${PROJECT_NAME} PRIVATE PICO)
endif()