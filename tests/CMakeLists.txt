set(SRC_DIR ../target/src)
set(MOCKS_DIR ./mocks)
# set(AVR_EXTENDS_DIR ../target/libs/avr-extends)

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(projectTests LANGUAGES C)

enable_testing()
add_subdirectory(unity)

add_unity_test(test_example test_example.c ${SRC_DIR}/unit_under_test.c)
target_include_directories(test_example PRIVATE ${UNITY_DIR} ${SRC_DIR})
