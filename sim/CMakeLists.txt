project(sim)

set(SRC
    bus.cpp
    cpu.cpp
    debug.cpp
    hdd.cpp
    main.cpp
    ram.cpp
)

add_executable(sim ${SRC})

