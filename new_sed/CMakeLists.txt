cmake_minimum_required(VERSION 3.0)
project(sed)

set(CMAKE_CXX_STANDARD 17)
set(SED_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SED_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SED_MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB SED_SOURCE_FILES ${SED_SOURCE_DIR}/*.cpp)
file(GLOB SED_HEADER_FILES ${SED_INCLUDE_DIR}/*.hpp ${SED_INCLUDE_DIR}/*.h ${SED_INCLUDE_DIR}/*.hh)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-local-typedefs)

# Bison and Flex
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(parser src/parser.y ${CMAKE_BINARY_DIR}/parser.cpp COMPILE_FLAGS "-Wcounterexamples -Wother" DEFINES_FILE ${CMAKE_BINARY_DIR}/parser.hpp)
FLEX_TARGET(scanner src/scanner.l ${CMAKE_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${SED_INCLUDE_DIR})
add_executable(sed ${SED_MAIN_FILE} ${SED_SOURCE_FILES} ${SED_HEADER_FILES} ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS} )
target_link_libraries(sed "-lfl")

enable_testing()

file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/*)

foreach (TEST_DIR ${TEST_DIRS})
    set(TEST_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/in.sy)
    set (TEST_MD ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.md)
    set(TEST_ERROR ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.err)
    set(TEST_IR ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.ir)

    if (NOT EXISTS ${TEST_INPUT})
        file(WRITE ${TEST_INPUT} "")
    endif ()
    if (NOT EXISTS ${TEST_MD})
        file(WRITE ${TEST_MD} "")
    endif ()
    if (NOT EXISTS ${TEST_ERROR})
        file(WRITE ${TEST_ERROR} "")
    endif ()
    if (NOT EXISTS ${TEST_IR})
        file(WRITE ${TEST_IR} "")
    endif ()
    
    add_test(
            NAME ${TEST_DIR}
            COMMAND sed ${TEST_INPUT} ${TEST_MD} ${TEST_ERROR}  ${TEST_IR}
            )

    set_tests_properties(${TEST_DIR} PROPERTIES
            TIMEOUT 10
    )
endforeach ()
