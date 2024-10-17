#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "position.h"

///////////////////////////////////////////////////////////////////////
// (X, Y Θ)
// +X -> RIGHT
// +Y -> FORWARD
// 
// (X, Y, Θ) =(0, 0, 0) @ LEFT CORNER; ALLIANCE SIDE; FACING RIGHT
///////////////////////////////////////////////////////////////////////

class odometry {
private:
    position pos;

public:
    // Constructor to initialize the values
    odometry(double x = 0, double y = 0, double a = 0);

    /** 
     * Set position and angle 
     */
    void setPosition(double x, double y, double a);

    /** 
     * Update position and angle 
     */
    void updatePosition(double xDisp, double yDisp, double angDisp);

    // Getters for each value
    double getX() const;
    double getY() const;
    double getAngle() const;

    // Getter for position
    position getPosition() const;

    /** 
     * Reset all odometry values to 0's
     */
    void reset();
};

#endif // ODOMETRY_H
