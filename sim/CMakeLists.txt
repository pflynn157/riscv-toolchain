project(sim)

set(SRC
    bus.cpp
    cpu.cpp
    debug.cpp
    display.cpp
    hdd.cpp
    main.cpp
    ram.cpp
    run.cpp
)

add_executable(sim ${SRC})

target_link_libraries(sim
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

