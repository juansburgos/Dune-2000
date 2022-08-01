add_executable(runModelTests test_map.cpp test_game.cpp)

option(BUILD_TESTS "Build all tests." OFF)
target_link_libraries(runModelTests gtest gtest_main)
target_link_libraries(runModelTests server)
target_include_directories(runModelTests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(runModelTests PUBLIC ${PROJECT_SOURCE_DIR}/server/model)