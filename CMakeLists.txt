cmake_minimum_required(VERSION 3.7)
project(TRIANGLE)

SET(TRIANGLE_SOURCES
    triangle.c
)
SET(TRIANGLE_COMPILE_OPTIONS
    -DANSI_DECLARATORS
    -DTRILIBRARY
)

add_library(triangle STATIC ${TRIANGLE_SOURCES})
target_compile_options(triangle PRIVATE ${TRIANGLE_COMPILE_OPTIONS})
