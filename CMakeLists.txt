cmake_minimum_required(VERSION 4.0)
project(N01Z VERSION 1.0.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




include_directories(.)
find_package(glfw3 REQUIRED)
add_executable(${PROJECT_NAME} noeyz.cpp gl.c)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

