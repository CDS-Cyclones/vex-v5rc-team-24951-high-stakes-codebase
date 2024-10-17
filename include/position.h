#ifndef POSITION_H
#define POSITION_H

struct position {
    double x;  // X position
    double y;  // Y position
    double a;  // Angle

    // Constructor for Position
    position(double _x, double _y, double _a) : x(_x), y(_y), a(_a) {}
};

#endif // POSITION_H
