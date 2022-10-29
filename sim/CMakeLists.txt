project(sim)

set(SRC
    cpu.cpp
    debug.cpp
    main.cpp
    ram.cpp
)

add_executable(sim ${SRC})

