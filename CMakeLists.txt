project(SimpleTinyServer)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)

aux_source_directory(. SRC_LIST)
include_directories(netlib)##include extern dir
aux_source_directory(netlib SRC_LIST)
include_directories(base)##include extern dir
aux_source_directory(base SRC_LIST)

find_package(Threads)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

