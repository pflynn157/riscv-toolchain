cmake_minimum_required(VERSION 3.0.0)
project(riscv-toolchain)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

add_compile_options(-std=c++17 -g)

add_subdirectory(as)
add_subdirectory(sim)
add_subdirectory(udo)

