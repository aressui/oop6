cmake_minimum_required(VERSION 3.10)

project(lab06_npc
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

# Основная программа
set(MAIN_SOURCES
    main.cpp
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/squirrel.cpp
    ${SRC_DIR}/werewolf.cpp
    ${SRC_DIR}/druid.cpp
    ${SRC_DIR}/visitor.cpp
    ${SRC_DIR}/factory.cpp
)

add_executable(lab06_main ${MAIN_SOURCES})

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тесты
set(TEST_SOURCES
    ${TEST_DIR}/test.cpp
    ${SRC_DIR}/npc.cpp
    ${SRC_DIR}/squirrel.cpp
    ${SRC_DIR}/werewolf.cpp
    ${SRC_DIR}/druid.cpp
    ${SRC_DIR}/visitor.cpp
    ${SRC_DIR}/factory.cpp
)

add_executable(lab06_tests ${TEST_SOURCES})
target_link_libraries(lab06_tests PRIVATE gtest_main)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab06_main PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab06_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(lab06_tests)