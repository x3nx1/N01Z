cmake_minimum_required(VERSION 4.0)
project(N01Z VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(.)
find_package(glfw3 REQUIRED)
add_executable(${PROJECT_NAME} noeyz.cpp gl.c
        system.cpp
        system.h
        afx.cpp
        afx.h
        input.cpp
        input.h
        net.cpp
        net.h
        netds.cpp
        netds.h
        gfx.cpp
        gfx.h
        negame.cpp
        negame.h
        nemenu.cpp
        nemenu.h
        nedata.cpp
        nedata.h
        player.cpp
        player.h
        arena.cpp
        arena.h
        menu.cpp
        menu.h
        item.cpp
        item.h
        ui.cpp
        ui.h
        debug.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

