#ifndef GEOMETRY_OFFSET_OPTIONS_H
#define GEOMETRY_OFFSET_OPTIONS_H

enum class Cap_type {
    butt,
    round,
    square
};

enum class Join_type {
    miter,
    round,
    square
};

struct Offset_options {
    Offset_options(double distance);

    double distance;
    Cap_type cap_type = Cap_type::round;
    Join_type join_type = Join_type::round;
    double miter_limit = 2.0;
    double smoothness = 0.5;
    double tolerance = 1E-3;
};

#endif // GEOMETRY_OFFSET_OPTIONS_H
