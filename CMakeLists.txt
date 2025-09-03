cmake_minimum_required(VERSION 3.16)
project(Hydra_Scheduler)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include_directories(header_files)

set(SOURCES
    src/main.cpp
    src/Process.cpp
    src/Scheduler.cpp
    src/GanttChart.cpp
    src/GUI_MainWindow.cpp
    src/GUI_GanttView.cpp
    src/GlobalThemes.cpp
)

set(HEADERS
    header_files/Process.hpp
    header_files/Scheduler.hpp
    header_files/GanttChart.hpp
    header_files/GUI_MainWindow.hpp
    header_files/GUI_GanttView.hpp
)

qt_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(Hydra_Scheduler
    ${SOURCES}
    ${MOC_SOURCES}
)

target_link_libraries(Hydra_Scheduler Qt6::Widgets)
