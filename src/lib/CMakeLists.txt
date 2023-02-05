set(core_lib_src_files
    particle.cpp
)

# set(fizx_lib_src_files
#     core.cpp
# )


add_library(core_lib ${core_lib_src_files})
#add_library(fizx_lib ${fizx_lib_src_files})


# target_link_libraries(graphics_lib
#     PUBLIC glew
#     PUBLIC glfw
#     PUBLIC OpenGL::GL
# )

target_include_directories(core_lib
#    PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glew/include
#    PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glfw/include
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# target_include_directories(fizx_lib
# #    PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glew/include
# #    PUBLIC ${PROJECT_SOURCE_DIR}/external_modules/glfw/include
#     PUBLIC ${PROJECT_SOURCE_DIR}/include
# )