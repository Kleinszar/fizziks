# GUI

# Utils

set (all_tests
    testcore.cpp
    testmat.cpp
    testmatspeed.cpp
    testvec.cpp
)

set (test_dependencies
    core_lib
)

# All Tests #
foreach (TEST ${all_tests})
    string (REGEX REPLACE ".cpp$" "" TEST_NAME ${TEST})
    add_executable (${TEST_NAME} ${TEST})
    target_link_libraries (${TEST_NAME} ${test_dependencies})
    target_include_directories (${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
    target_include_directories (${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # Executables
    add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # target_compile_options(${TEST_NAME} PRIVATE -Wall)
endforeach (TEST)

# Files