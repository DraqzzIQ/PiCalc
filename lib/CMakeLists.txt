
if(NOT RPI_PICO)
    find_package(Threads REQUIRED)

    find_package(SDL2 REQUIRED) # sudo apt install libsdl2-dev to install

    include_directories(${SDL2_INCLUDE_DIRS})

    # httplib
    target_sources(${PROJECT_NAME}
        PRIVATE
            httplib/httplib.h
    )

    # httplib
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/httplib/
    )

    target_link_libraries(${PROJECT_NAME} Threads::Threads ${SDL2_LIBRARIES})
endif()