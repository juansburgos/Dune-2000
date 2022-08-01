cmake_minimum_required(VERSION 3.10)
project(setupscreen)

set(HEADER_FILES    setupscreen.h 
                    conectServer.h
                    menuMultiPlayer.h
                    salaCrear.h
                    salaUnirse.h
                    playerReproductor.h
                    )

set(SOURCE_FILES    setupscreen.cpp
                    conectServer.cpp
                    menuMultiPlayer.cpp
                    salaCrear.cpp
                    salaUnirse.cpp
                    playerReproductor.cpp
                    )

add_library(setupscreen STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)

target_link_libraries(setupscreen Qt5::Widgets Qt5::Multimedia client)

target_include_directories(setupscreen PUBLIC ..)