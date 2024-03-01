cmake_minimum_required(VERSION 3.14)

project(extractstrings LANGUAGES CXX)
enable_testing()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test)

add_executable(extractstrings
  main.cpp
  runoptions.h
  filehandler.h
  filehandler.cpp
  statistics.h
  statistics.cpp
  runoptions.cpp
)
target_link_libraries(extractstrings Qt${QT_VERSION_MAJOR}::Core)


add_executable(TestFileHandler
    runoptions.h
    filehandler.h
    filehandler.cpp
    statistics.h
    statistics.cpp
    runoptions.cpp
    tests/testfilehandler.cpp)

target_link_libraries(TestFileHandler Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test)

add_test(NAME TestFileHandler COMMAND TestFileHandler)

include(GNUInstallDirs)
install(TARGETS extractstrings
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
