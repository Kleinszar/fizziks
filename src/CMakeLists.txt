set (PROGRAM_NAME
    Main
)

set(src_files
    main.cpp
)

add_executable(${PROGRAM_NAME} ${src_files})
target_include_directories(${PROGRAM_NAME}
#   PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glew/include
#   PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glfw/include
#   PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glm
   PUBLIC ${PROJECT_SOURCE_DIR}/include
)
# target_compile_options(${PROGRAM_NAME} PRIVATE -Wall)

# target_link_libraries(${PROGRAM_NAME} 
#     PUBLIC glew
#     PUBLIC glfw
#     PUBLIC OpenGL::GL
#     PUBLIC graphics_lib
#     PUBLIC midi_lib
# )
