cmake_minimum_required(VERSION 3.10)
project(server)

set(HEADER_FILES
        ctrlhilos.h
        gamecontainer.h
        games.h
        model/astar.h
        model/building.h
        model/config.h
        model/game.h
        model/guns.h
        model/map.h
        model/movable.h
        model/playerinfo.h
        model/positonable.h
        model/targetable.h
        model/unit.h
        model/worm.h
        model/harvester.h
        model/onhold.h
        serverprotocol.h
        thbroadcaster.h
        thclienthandler.h
        thgameloop.h
        thread.h
        thcmdexecutor.h
        thgamestatus.h
        serverqueue.h
        smsg.h
        smsgatacar.h
        smsgdestruir.h
        smsgconstruir.h
        smsgcrearunidad.h
        smsgmover.h
)

set(SOURCE_FILES
        ctrlhilos.cpp
        gamecontainer.cpp
        games.cpp
        model/astar.cpp
        model/building.cpp
        model/config.cpp
        model/game.cpp
        model/guns.cpp
        model/map.cpp
        model/movable.cpp
        model/playerinfo.cpp
        model/unit.cpp
        model/worm.cpp
        model/harvester.cpp
        model/onhold.cpp
        serverprotocol.cpp
        serverqueue.cpp
        smsgatacar.cpp
        smsgconstruir.cpp
        smsgdestruir.cpp
        smsgcrearunidad.cpp
        smsgmover.cpp
        thgameloop.cpp
        thbroadcaster.cpp
        thclienthandler.cpp
        thread.cpp
        thcmdexecutor.cpp
        thgamestatus.cpp
        smsgforcedend.cpp smsgforcedend.h)

add_library(server STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(yaml-cpp)

target_link_libraries(server common yaml-cpp)

target_include_directories(server PUBLIC ../common)
