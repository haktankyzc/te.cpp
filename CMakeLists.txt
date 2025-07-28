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
  $(CMAKE_SOURCE_DIR)/../app/main.cpp
  
  $(CMAKE_SOURCE_DIR)/../core/editor.hpp

  $(CMAKE_SOURCE_DIR)/../core/input_handler/input_handler.cpp
  $(CMAKE_SOURCE_DIR)/../core/input_handler/input_handler.hpp

  $(CMAKE_SOURCE_DIR)/../core/status_bar/status_bar.cpp
  $(CMAKE_SOURCE_DIR)/../core/status_bar/status_bar.hpp
  
  $(CMAKE_SOURCE_DIR)/../core/pages/entry_win/entryWin.hpp
  $(CMAKE_SOURCE_DIR)/../core/pages/entry_win/entryWin.cpp
 
  $(CMAKE_SOURCE_DIR)/../core/pages/editor_win/editorWin.cpp 
  $(CMAKE_SOURCE_DIR)/../core/pages/editor_win/editorWin.hpp 

  $(CMAKE_SOURCE_DIR)/../common/styles/style.hpp
  $(CMAKE_SOURCE_DIR)/../common/types.hpp
  
  $(CMAKE_SOURCE_DIR)/../utils/timer/timer.cpp
  $(CMAKE_SOURCE_DIR)/../utils/timer/timer.hpp

)

target_link_libraries(TE_CPP ${CURSES_LIBRARIES})
