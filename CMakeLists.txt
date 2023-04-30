cmake_minimum_required(VERSION 3.24)
project(YukonProjekt C)

set(CMAKE_C_STANDARD 11)

add_executable(YukonProjekt Classes/main.c Classes/reader.c Classes/deck.c Classes/deck.h Classes/reader.h Classes/moves.c Classes/moves.h Classes/FileHandler.c Classes/FileHandler.h)
