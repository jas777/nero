cmake_minimum_required(VERSION 3.20)
project(nero)

set(CMAKE_CXX_STANDARD 17)

add_executable(nero src/main.cpp src/ui/stripe.h src/cli/command.h include/argparse/argparse.hpp)

# Dependencies

include_directories(include/argparse)
add_subdirectory(include/ftxui)

target_link_libraries(nero
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        )