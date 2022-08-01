project(common)

set(HEADER_FILES
        defines.h
        protocol.h
        resolver.h
        socket.h
        protocolerror.h
        )

set(SOURCE_FILES
        protocol.cpp
        resolver.cpp
        socket.cpp
        )

add_library(common STATIC ${SOURCE_FILES} ${HEADER_FILES})