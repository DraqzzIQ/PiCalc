cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
option(RPI_PICO "use rpi pico" ON)

set(PICO_BOARD pico_w)
set(PROJECT_NAME "CasioOS")

# Set compiler flags for profiling
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

# # Set a default build type if it's not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add a compile-time macro based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(IS_DEBUG_BUILD)
endif()

# Pico
if(RPI_PICO)
    set(PICO_CXX_ENABLE_EXCEPTIONS 1)
    set(PICO_CXX_ENABLE_RTTI 1)
    include(pico_sdk_import.cmake) # must be included before project()
endif()

project(${PROJECT_NAME} CXX C )


add_executable(${PROJECT_NAME})
# source files
add_subdirectory(src)
add_subdirectory(lib)
# Linux, (Windows)

# Pico
# cmake -DRPI_PICO=ON to compile
if(RPI_PICO)
    # initialize the Raspberry Pi Pico SDK
    pico_sdk_init()

    # Add pico_stdlib library which aggregates commonly used features
    # pico_cyw43_arch_none is nessessary for accessing the CYW4343W WiFi chip and it's LED
    target_link_libraries(${PROJECT_NAME} pico_stdlib 
                #pico_cyw43_arch
                hardware_i2c 
                pico_mbedtls
                pico_cyw43_arch_lwip_threadsafe_background
                )

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(${PROJECT_NAME})

    # redirect standart output to UART
    pico_enable_stdio_usb(${PROJECT_NAME} 0)
    pico_enable_stdio_uart(${PROJECT_NAME} 1)

    # preprocessor macro
    target_compile_definitions(${PROJECT_NAME} PRIVATE PICO)
endif()
