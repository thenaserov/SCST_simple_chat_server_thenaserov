cmake_minimum_required(VERSION 3.5)

project(SCST LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For developement under Qt 5 / 6 simply change the line below (ex) -> Qt6 => Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Network)

add_executable(SCST
  main.cpp
  server.h
  server.cpp
)
target_link_libraries(SCST PRIVATE Qt5::Core Qt5::Network)
