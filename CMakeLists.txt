cmake_minimum_required(VERSION 4.0)
project(N01Z VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/maps)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/items)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/map_templates)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/item_templates)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/logs)


include_directories(.)
find_package(glfw3 REQUIRED)
find_package(tomlplusplus REQUIRED)
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
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ".debug")
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE tomlplusplus::tomlplusplus)

# map template demo configuration build-time copy
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/n01z/map_templates/demo.toml"
        "${CMAKE_CURRENT_SOURCE_DIR}/../N01Z_BUILD/n01Z/map_templates/demo.toml"
)

