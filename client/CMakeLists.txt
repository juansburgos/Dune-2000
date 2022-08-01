cmake_minimum_required(VERSION 3.10)
project(client)

add_subdirectory(setupscreen)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_MIXER YES)
add_subdirectory(SDL2pp)
add_subdirectory(SDL)

# add compilation flags
# add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/assets")
include_directories(${SDL2PP_INCLUDE_DIRS})

set(HEADER_FILES
        clases/YAMLbuilding.h
        clases/YAMLunit.h
        clientqueue.h
        clientprotocol.h
        cmsg.h
        cmsgmover.h
        cmsgdestruir.h
        partida.h
        threceiver.h
        thsender.h
        thdrawer.h
        cmsgconstruir.h
        cmsgcrearunidad.h
        cmsgatacar.h
        cmsgforcedend.h
        )

set(SOURCE_FILES
        clases/YAMLbuilding.cpp
        clases/YAMLunit.cpp
        clientqueue.cpp
        clientprotocol.cpp
        cmsg.cpp
        cmsgmover.cpp
        partida.cpp
        threceiver.cpp
        thsender.cpp
        thdrawer.cpp
        cmsgconstruir.cpp
        cmsgcrearunidad.cpp
        cmsgatacar.cpp
        cmsgdestruir.cpp
        cmsgforcedend.cpp
        )

add_library(client STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(yaml-cpp)

target_link_libraries(client common ${SDL2PP_LIBRARIES} setupscreen SDL yaml-cpp)

target_include_directories(client PUBLIC ../common setupscreen SDL)
