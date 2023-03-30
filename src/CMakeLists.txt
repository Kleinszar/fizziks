set (core_lib_src_files
    core.cpp
    particle.cpp
    pfgen.cpp
)

set (fizx_lib_src_files
    core.cpp
)

add_library (core_lib ${core_lib_src_files})

target_include_directories (core_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)