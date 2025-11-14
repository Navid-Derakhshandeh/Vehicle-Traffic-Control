cmake_minimum_required(VERSION 3.16)

project(Vehicle-Traffic-Map VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt build helpers
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt (Qt6 recommended; switch to Qt5 if needed)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
# If you’re on Qt5, comment the line above and uncomment:
# find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Find Marble (ensure libmarble-dev or equivalent is installed)
find_package(Marble REQUIRED)
find_package(OpenCV REQUIRED)
# Sources
add_executable(Vehicle-Traffic-Map
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
)

# Link Qt and Marble
target_link_libraries(Vehicle-Traffic-Map
    Qt6::Core Qt6::Gui Qt6::Widgets
    Marble ${OpenCV_LIBS}
)
# For Qt5:
# target_link_libraries(Vehicle-Traffic-Map Qt5::Core Qt5::Gui Qt5::Widgets Marble)
