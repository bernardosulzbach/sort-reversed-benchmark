cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(benchmark)

add_executable(main main.cpp)
target_link_libraries(main pthread)
target_link_libraries(main benchmark)
