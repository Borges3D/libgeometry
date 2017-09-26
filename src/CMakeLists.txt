set(CLIPPER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/clipper)
set(SISL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/SISL/include)
set(TRIANGLE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/triangle)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

SET(GEOMETRY_SOURCES
    circle.cpp
    clip_options.cpp
    clipper_utilities.cpp
    closed_curve_2.cpp
    closed_curve_3.cpp
    curve.cpp
    curve_2.cpp
    curve_3.cpp
    edge.cpp
    face.cpp
    mesh_2.cpp
    offset_options.cpp
    open_curve_2.cpp
    open_curve_3.cpp
    point_2.cpp
    point_3.cpp
    polygon_2.cpp
    polygon_3.cpp
    polyline_2.cpp
    polyline_3.cpp
    rectangle.cpp
    scalar.cpp
    simple_polygon.cpp
    sisl_utilities.cpp
    unique_malloc_ptr.cpp
    unique_sisl_curve_ptr.cpp
    vector_2.cpp
    vector_3.cpp
)
SET(GEOMETRY_INCLUDE_DIRS
    ${CLIPPER_INCLUDE_DIR}
    ${SISL_INCLUDE_DIR}
    ${TRIANGLE_INCLUDE_DIR}
)
SET(GEOMETRY_LIBRARIES
    polyclipping
    sisl
    triangle
)

SET(VIEWER_SOURCES
    viewer.cpp
)
SET(VIEWER_COMPILE_OPTIONS
    -Wno-deprecated-declarations)
SET(VIEWER_INCLUDE_DIRS
    ${CLIPPER_INCLUDE_DIR}
    ${SISL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)
SET(VIEWER_LIBRARIES
    geometry
    ${GLUT_LIBRARY}
    ${OPENGL_LIBRARY}
)

set(CMAKE_CXX_STANDARD 11)

add_library(geometry STATIC ${GEOMETRY_SOURCES})
target_include_directories(geometry PRIVATE ${GEOMETRY_INCLUDE_DIRS})
target_link_libraries(geometry ${GEOMETRY_LIBRARIES})

add_executable(viewer ${VIEWER_SOURCES})
target_compile_options(viewer PRIVATE ${VIEWER_COMPILE_OPTIONS})
target_include_directories(viewer PRIVATE ${VIEWER_INCLUDE_DIRS})
target_link_libraries(viewer ${VIEWER_LIBRARIES})
