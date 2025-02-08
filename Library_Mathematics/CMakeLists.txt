cmake_minimum_required(VERSION 3.14)
project(Library_Mathematics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main  
)
# Configure par défaut
option(BUILD_GMOCK OFF)
option(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS
    "${PROJECT_SOURCE_DIR}/Header_Files/*.h"
)

include_directories(${PROJECT_SOURCE_DIR}/Header_Files)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})


target_link_libraries(${PROJECT_NAME} PRIVATE gtest)