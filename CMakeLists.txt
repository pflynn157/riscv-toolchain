cmake_minimum_required(VERSION 3.0.0)
project(riscv-toolchain)

add_compile_options(-std=c++17 -g)

add_subdirectory(as)
add_subdirectory(sim)
add_subdirectory(udo)

