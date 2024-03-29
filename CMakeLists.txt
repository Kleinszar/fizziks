cmake_minimum_required(VERSION 3.16.2)

project(Fizziks VERSION 0.1.0)

# Testing #
include(CTest)
enable_testing()

# Output Directory #
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# MSVC Directories #
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/assets)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)


#include
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)


# Configure #
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

set(app_dependencies
    core_lib
)

# Main #
# set(MAIN App)
# add_executable(${MAIN} main.cpp)
# target_link_libraries(${MAIN} ${app_dependencies})
# target_include_directories(${MAIN} PRIVATE ${PROJECT_SOURCE_DIR})
# target_include_directories(${MAIN} PRIVATE ${PROJECT_SOURCE_DIR}/include)
# target_compile_options(${MAIN} PRIVATE -O3)


