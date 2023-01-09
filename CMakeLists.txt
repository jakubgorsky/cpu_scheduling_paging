cmake_minimum_required(VERSION 3.23)
project(cpu_scheduling)

set(SOURCE
        src/main.cpp
        src/fcfs.cpp src/sjf.cpp)

set(HEADERS
        headers/fcfs.h headers/PROCESS_GENERATOR.h headers/CPU_Process.h headers/split.h headers/sjf.h)

include_directories(${PROJECT_SOURCE_DIR}/src/ ${PROJECT_SOURCE_DIR}/headers/)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpu_scheduling ${SOURCE} ${HEADERS})
