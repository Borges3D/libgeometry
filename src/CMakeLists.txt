set(CLIPPER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/clipper)
set(SISL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/SISL/include)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

SET(GEOMETRY_SOURCES
    circle_2.cpp
    clipper_utilities.cpp
    closed_curve_2.cpp
    curve.cpp
    curve_2.cpp
    offset_options.cpp
    open_curve_2.cpp
    point_2.cpp
    polygon_2.cpp
    polyline_2.cpp
    rectangle_2.cpp
    sisl_utilities.cpp
    utilities.cpp
    vector_2.cpp
)
SET(GEOMETRY_INCLUDE_DIRS
    ${CLIPPER_INCLUDE_DIR}
    ${SISL_INCLUDE_DIR}
)
SET(GEOMETRY_LIBRARIES
    polyclipping
    sisl
)

SET(VIEWER_SOURCES
    viewer.cpp
)
SET(VIEWER_COMPILE_FLAGS
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
set_target_properties(viewer PROPERTIES COMPILE_FLAGS ${VIEWER_COMPILE_FLAGS})
target_include_directories(viewer PRIVATE ${VIEWER_INCLUDE_DIRS})
target_link_libraries(viewer ${VIEWER_LIBRARIES})
