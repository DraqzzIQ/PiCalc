
if(NOT RPI_PICO)
    find_package(Threads REQUIRED)

    find_package(SDL2 REQUIRED) # sudo apt install libsdl2-dev to install

    include_directories(${SDL2_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME} Threads::Threads ${SDL2_LIBRARIES})

    include(httplib.h)
endif()
