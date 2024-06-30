cmake_minimum_required(VERSION 3.2)

project(parser)

if (WIN32)
    message("Well, you're shit out of luck mate")
    # Assume using MSVC
    add_compile_options(

    )
else()
    add_compile_options(
        -std=c++17
        -Wall
        -Wextra
        -Wpedantic
    )
endif()


add_library(parser
    parser.cpp
    command.cpp
    option.cpp
    argument.cpp
)

add_executable(test main.cpp)
target_link_libraries(test PUBLIC parser)