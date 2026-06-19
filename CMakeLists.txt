cmake_minimum_required(VERSION 4.2)
project(SelfWateringPlantSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SelfWateringPlantSystem
        src/config.h
        src/main.cpp
        src/moisture_sensor.cpp
        src/moisture_sensor.h
        src/pump_control.cpp
        src/pump_control.h)
