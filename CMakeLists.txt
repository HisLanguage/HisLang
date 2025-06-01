cmake_minimum_required(VERSION 3.10)
project(HisLangCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC_DIR ${CMAKE_SOURCE_DIR}/HisLangCompiler)


include_directories(${SRC_DIR})


file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

add_executable(hcp ${SOURCES})


# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
