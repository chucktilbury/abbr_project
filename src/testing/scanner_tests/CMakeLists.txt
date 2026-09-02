project(scanner_tests)

include(${CMAKE_SOURCE_DIR}/CMakeBuildOpts.txt)

add_custom_target(scanner_test)

add_executable(stest1
    scanner_test.c
)
add_dependencies(scanner_test stest1)

add_executable(stest2
    token_queue_test.c
)
add_dependencies(scanner_test stest2)

set(TESTING_LIBS
    gc
    cord
    scanner
    common
)

target_link_libraries(stest1
    ${TESTING_LIBS}
)

target_link_libraries(stest2
    ${TESTING_LIBS}
)
