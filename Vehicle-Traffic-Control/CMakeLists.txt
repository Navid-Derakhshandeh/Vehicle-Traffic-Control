cmake_minimum_required(VERSION 3.16)
project(Vehicle-Traffic-Control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets WebEngineWidgets Sql)
find_package(OpenCV REQUIRED)

add_executable(MapView
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    mainwindow.h
    jsbridge.h
    jsbridge.cpp
)

target_include_directories(MapView PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

qt5_add_resources(RESOURCES resources.qrc)
target_sources(MapView PRIVATE ${RESOURCES})

target_link_libraries(MapView
    PRIVATE Qt5::Widgets Qt5::WebEngineWidgets Qt5::Sql ${OpenCV_LIBS}
)
