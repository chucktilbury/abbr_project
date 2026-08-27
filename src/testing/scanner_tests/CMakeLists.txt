project(scanner_tests)

include(${CMAKE_SOURCE_DIR}/CMakeBuildOpts.txt)

add_custom_target(testing)

add_executable(stest1
    scanner_test.c
)
add_dependencies(testing stest1)

add_executable(stest2
    token_queue_test.c
)
add_dependencies(testing stest2)

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
