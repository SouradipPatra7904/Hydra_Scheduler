cmake_minimum_required(VERSION 3.16)
project(CPUScheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Your header folder
include_directories(header_files)

# Optionally enable GUI (SFML). If SFML isn't found, we silently fall back to ASCII.
option(USE_GUI "Enable SFML GUI visualization" ON)

if (USE_GUI)
  find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
  if (SFML_FOUND)
    message(STATUS "SFML found: enabling GUI visualization")
    add_definitions(-DUSE_GUI)
    set(GUI_LIBS sfml-graphics sfml-window sfml-system)
  else()
    message(WARNING "SFML not found, building without GUI. (You can set -DUSE_GUI=OFF)")
    set(USE_GUI OFF)
    set(GUI_LIBS "")
  endif()
endif()

add_executable(CPUScheduler
    src/main.cpp
    src/Process.cpp
    src/Scheduler.cpp
    src/GanttChart.cpp
    
    src/sch_algos/FCFS.cpp
    src/sch_algos/SJF.cpp
    src/sch_algos/Priority.cpp
    src/sch_algos/RoundRobin.cpp
)

if (USE_GUI AND SFML_FOUND)
  target_link_libraries(CPUScheduler PRIVATE ${GUI_LIBS})
endif()
