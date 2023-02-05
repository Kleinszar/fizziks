# GUI

# Utils

# Main Program

# TEST Core Components
set(TEST_NAME Test_Core)
add_executable(${TEST_NAME} test_core.cpp)
target_link_libraries(${TEST_NAME} core_lib)
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_options(${TEST_NAME} PRIVATE -Wall)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

#Files