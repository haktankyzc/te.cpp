cmake_minimum_required(VERSION 3.16)
project(TE_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
set(EXECUTABLE_OUTPUT_PATH ../bin/)
    
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(TE_CPP
  app/te.cpp
)

target_link_libraries(TE_CPP ${CURSES_LIBRARIES})
