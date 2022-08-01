cmake_minimum_required(VERSION 3.1)
project(dune)

add_definitions(-std=c++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(src_editor)

#### Editor #####
set(EDITOR_SOURCE_FILES editor_main.cpp)
add_executable(editor ${EDITOR_SOURCE_FILES})
target_link_libraries(editor edit)
target_include_directories(editor PUBLIC src_editor)
#################

#### Client #####
set(CLIENT_SOURCE_FILES client_main.cpp)
add_executable(dune_client ${CLIENT_SOURCE_FILES})
target_link_libraries(dune_client client pthread)
target_include_directories(dune_client PUBLIC client)
#################


#### Server #####
set(SERVER_SOURCE_FILES server_main.cpp)
add_executable(dune_server ${SERVER_SOURCE_FILES})
target_link_libraries(dune_server server pthread)
target_include_directories(dune_server PUBLIC server)
#################


#### Tests ######
add_subdirectory(tests)
enable_testing()
add_test(model_test tests/server/model/runModelTests)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage runModelTests coverage)

    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()
#################
