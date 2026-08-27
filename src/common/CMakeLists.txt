project(common)

include(${CMAKE_SOURCE_DIR}/CMakeBuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    cmdline.c
    colors.c
    find_file.c
    hashtable.c
    hexdump.c
    int_list.c
    pointer_list.c
    string_buffer.c
    string_list.c
    trace.c
    alloc.c
)
