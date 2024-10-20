/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  CDS Vex V5 High Stakes Code                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const int DEADZONE = 10; // Adjust this value as needed
const double TURN_MULTIPLER = 0.7; // Define turn multiplier as per your requirements

// ROBOT CONSTANTS
const double WHEEL_RADIUS = 3.25/2.0;

// CONVERSION FACTORS & PHYSICS CONSTANTS
const double RAD_TO_DEG_CONV_FAC = 0.01745329251; // rad/deg
const double GRAV_ACC_UNIT_EARTH = 9.81; // ms^-2

/**
 * Rest time b/w user control loop's cycles
 */
double T = 0.02;
const timeUnits T_UNITS = sec;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
    int32_t forward, turn;
    double heading, ang_vel_mag, acc_y, acc_x, vel_mag, vel_y, vel_x;

    // User control code here, inside the loop
    while (1) {
        // This is the main execution loop for the user control program.
        // Each time through the loop your program should update motor + servo
        // values based on feedback from the joysticks.

        // ........................................................................
        // Insert user code here. This is where you use the joystick values to
        // update your motors, etc.
        // ........................................................................

        forward = Controller.Axis3.position();
        turn = Controller.Axis1.position() * TURN_MULTIPLER;

        // Apply deadzones
        if (abs(forward) < DEADZONE) {
            forward = 0;
        }
        if (abs(turn) < DEADZONE) {
            turn = 0;
        }

        Drivetrain.arcade(forward, turn);

        // EMPIRICALLY: y axis - fwd | x-axis - right

        // Read values off the sensors
        heading = (360.0 - Inertial.heading(deg)) * RAD_TO_DEG_CONV_FAC; // in rad; invert direction by 360 - value
        ang_vel_mag = Drivetrain.velocity(dps) * RAD_TO_DEG_CONV_FAC;  // in rad/s
        acc_y = Inertial.acceleration(yaxis) * GRAV_ACC_UNIT_EARTH; // in m/s^2
        acc_x = Inertial.acceleration(xaxis) * GRAV_ACC_UNIT_EARTH; // in m/s^2

        // Convert angular speed to translational speed
        vel_mag = ang_vel_mag  * WHEEL_RADIUS;

        // Split translational velocity into components
        vel_y = vel_mag * sin(heading);
        vel_x = vel_mag * cos(heading);

        // Control clamp with ButtonA
        if (Controller.ButtonA.PRESSED) {
            if (isClampedOn)
                clampOff();
            else
                clampOn();
        }

        wait(T, T_UNITS); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }

}
