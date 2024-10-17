#include "odometry.h"

// Constructor to initialize the values
odometry::odometry(double x, double y, double a) : pos(x, y, a) {}

/** 
 * Set position and angle 
 */
void odometry::setPosition(double x, double y, double a) {
    pos.x = x;
    pos.y = y;
    pos.a = a;
}

/** 
 * Update position and angle
 */
void odometry::updatePosition(double xDisp, double yDisp, double angDisp) {
    pos.x += xDisp;
    pos.y += yDisp;
    pos.a += angDisp;
}

/**
 * Get X position in meters
 */
double odometry::getX() const {
    return pos.x;
}

/**
 * Get Y position in meters
 */
double odometry::getY() const {
    return pos.y;
}

/**
 * Get angle in degrees
 */
double odometry::getAngle() const {
    return pos.a;
}

/**
 * Get full position
 */
position odometry::getPosition() const {
    return position(pos.y, pos.x, pos.a);
}

/** 
 * Reset all odometry values to 0's
 */
void odometry::reset() {
    pos.x = 0;
    pos.y = 0;
    pos.a = 0;
}
