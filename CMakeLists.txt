cmake_minimum_required(VERSION 3.0)
project(game LANGUAGES C)

add_executable(${PROJECT_NAME} "")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_include_directories(${PROJECT_NAME} PRIVATE -I/usr/include/SDL2/)
target_sources(${PROJECT_NAME} PRIVATE board.c board.h game.c)