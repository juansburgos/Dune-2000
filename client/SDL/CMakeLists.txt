cmake_minimum_required(VERSION 3.10)
project(SDL)
include_directories(${SDL2PP_INCLUDE_DIRS})

set(HEADER_FILES
    SDLgame.h
    SDLmap.h
    SDLcam.h
    SDLbuilding.h
    SDLbuildings.h
    SDLgui.h
    SDLmenu.h
    SDLmenuicon.h
    SDLunits.h
    SDLunit.h
    SDLsound.h
    buildings/SDLConstructionYard.h
    buildings/SDLHeavyFactory.h
    buildings/SDLSpiceSilo.h
    buildings/SDLBarracks.h
    buildings/SDLLightFactory.h
    buildings/SDLAirTrap.h
    buildings/SDLRefinery.h
    buildings/SDLPalace.h
)

set(SOURCE_FILES
    SDLgame.cpp
    SDLmap.cpp
    SDLcam.cpp
    SDLbuilding.cpp
    SDLbuildings.cpp
    SDLgui.cpp
    SDLunits.cpp
    SDLunit.cpp
    SDLmenuicon.cpp
    SDLmenu.cpp
    SDLsound.cpp
    buildings/SDLConstructionYard.cpp
    buildings/SDLHeavyFactory.cpp
    buildings/SDLSpiceSilo.cpp
    buildings/SDLBarracks.cpp
    buildings/SDLLightFactory.cpp
    buildings/SDLAirTrap.cpp
    buildings/SDLRefinery.cpp
    buildings/SDLPalace.cpp
)

add_library(SDL STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(SDL client ${SDL2PP_LIBRARIES})

target_include_directories(SDL PUBLIC ..)