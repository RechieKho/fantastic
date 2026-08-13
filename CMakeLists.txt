cmake_minimum_required(VERSION 3.10)

find_package(Git QUIET)
if(GIT_FOUND)
    # Run git describe to get the latest tag
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
        OUTPUT_VARIABLE GIT_TAG_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endif()
if (NOT GIT_TAG_VERSION)
    set(GIT_TAG_VERSION "0.0.1")
endif()
message(STATUS "Detected Tag Version: ${GIT_TAG_VERSION}")

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/PROJECT_NAME" PROJECT_NAME)
message(STATUS "Detected Project Name: ${PROJECT_NAME}")

project(
    "${PROJECT_NAME}"
    VERSION "${GIT_TAG_VERSION}"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    VERSION 6.0
)

block(SCOPE_FOR VARIABLES)
    # Configuration variables for `raylib`.
    FetchContent_MakeAvailable(raylib)
endblock()

set(EXECUTABLE_NAME "${PROJECT_NAME}")
set(LIBRARY_NAME "lib${PROJECT_NAME}")
string(MAKE_C_IDENTIFIER "${LIBRARY_NAME}" C_IDENTIFIER_LIBRARY_NAME)
set(SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/inc")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIRECTORY}/*.cpp")

add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE ${INCLUDE_DIRECTORY})
target_compile_definitions(${LIBRARY_NAME} 
    INTERFACE
    LIBRARY_NAME=${C_IDENTIFIER_LIBRARY_NAME}
    VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    VERSION_MINOR=${PROJECT_VERSION_MINOR}
    VERSION_PATCH=${PROJECT_VERSION_PATCH}
    PROJECT_VERSION="${PROJECT_VERSION}"
)
target_link_libraries(${LIBRARY_NAME} INTERFACE raylib)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(
    ${EXECUTABLE_NAME}
    PRIVATE
    ${LIBRARY_NAME}
)