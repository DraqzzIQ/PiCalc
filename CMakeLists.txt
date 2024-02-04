cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
option(RPI_PICO "use rpi pico" ON)

set(PICO_BOARD pico_w)
set(PROJECT_NAME "CasioOS")

# Set compiler flags for profiling
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

set(CMAKE_CXX_FLAGS_RELEASE "-Os")


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
    set(PICO_CXX_ENABLE_RTTI 1)
    include(pico_sdk_import.cmake) # must be included before project()
endif()

project(${PROJECT_NAME} CXX C )


add_executable(${PROJECT_NAME})
# source files
add_subdirectory(src)
add_subdirectory(lib)
# Linux, (Windows)


# SECRETS
#check if file exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/secrets")
    # Read from file
    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/secrets" SECRETS_LIST)

    # Set during configuration
    list(GET SECRETS_LIST 0 WOLFRAMALPHA_APPID)
    list(GET SECRETS_LIST 1 OPENAI_API_KEY)

    list(GET SECRETS_LIST 2 PICO_WIFI_SSID)
    list(GET SECRETS_LIST 3 PICO_WIFI_PASSWORD)

    # Extract values after the equal sign
    string(REGEX REPLACE "WOLFRAMALPHA_APPID=(.*)" "\\1" WOLFRAMALPHA_APPID "${WOLFRAMALPHA_APPID}")
    string(REGEX REPLACE "OPENAI_API_KEY=(.*)" "\\1" OPENAI_API_KEY "${OPENAI_API_KEY}")

    string(REGEX REPLACE "PICO_WIFI_SSID=(.*)" "\\1" PICO_WIFI_SSID "${PICO_WIFI_SSID}")
    string(REGEX REPLACE "PICO_WIFI_PASSWORD=(.*)" "\\1" PICO_WIFI_PASSWORD "${PICO_WIFI_PASSWORD}")
    # Replace new line and other unwanted chars
    string(STRIP "${WOLFRAMALPHA_APPID}" WOLFRAMALPHA_APPID)
    string(STRIP "${OPENAI_API_KEY}" OPENAI_API_KEY)

    string(STRIP "${PICO_WIFI_SSID}" PICO_WIFI_SSID)
    string(STRIP "${PICO_WIFI_PASSWORD}" PICO_WIFI_PASSWORD)

    message(STATUS "Secrets have been loaded from file.")
else()
    # Use default values if the file is not found
    message(WARNING "Secrets file not found, using default values.")
    set(WOLFRAMALPHA_APPID "DEMO")
    set(OPENAI_API_KEY "DEMO")

    set(PICO_WIFI_SSID "DEMO")
    set(PICO_WIFI_PASSWORD "DEMO")
endif()
# Define secrets compile time
add_compile_definitions(WOLFRAMALPHA_APPID="${WOLFRAMALPHA_APPID}")
add_compile_definitions(OPENAI_API_KEY="${OPENAI_API_KEY}")

add_compile_definitions(PICO_WIFI_SSID="${PICO_WIFI_SSID}")
add_compile_definitions(PICO_WIFI_PASSWORD="${PICO_WIFI_PASSWORD}")

# Pico
# cmake -DRPI_PICO=ON to compile
if(RPI_PICO)
    # initialize the Raspberry Pi Pico SDK
    pico_sdk_init()

    # Add pico_stdlib library which aggregates commonly used features
    # pico_cyw43_arch_none is nessessary for accessing the CYW4343W WiFi chip and it's LED
    target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c pico_multicore hardware_adc pico_lwip pico_lwip_nosys pico_mbedtls pico_cyw43_arch_lwip_threadsafe_background pico_lwip_mbedtls)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(${PROJECT_NAME})

    # redirect standart output to UART
    pico_enable_stdio_usb(${PROJECT_NAME} 0)
    pico_enable_stdio_uart(${PROJECT_NAME} 1)

    # preprocessor macro
    target_compile_definitions(${PROJECT_NAME} PRIVATE PICO)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-unused-result)
endif()
