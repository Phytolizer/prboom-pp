cmake_minimum_required(VERSION 3.12..3.20)

project("blahh")

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
