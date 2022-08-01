cmake_minimum_required(VERSION 3.10)
project(edit)

set(HEADER_FILES    editor.h
                    crearMenu.h
                    piecesMap.h
                    mapWidget.h
                    editarMenu.h
                    createFileMap.h
                    )

set(SOURCE_FILES    editor.cpp
                    crearMenu.cpp
                    piecesMap.cpp
                    mapWidget.cpp
                    editarMenu.cpp
                    createFileMap.cpp
                    )

find_package(Qt5 REQUIRED COMPONENTS Widgets)

find_package(yaml-cpp)

add_library(edit STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(edit Qt5::Widgets yaml-cpp)

target_include_directories(edit PUBLIC ..)