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

// A global instance of competition
competition Competition;

const int DEADZONE = 10; // Adjust this value as needed
const double TURN_MULTIPLER = 0.75; // Define turn multiplier as per your requirements
const double AUTON_DRIVE_TIME_SEC = 1.5;

































;

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

    clampOff();

    ElevatorMotor.setVelocity(100, percent);
    ElevatorMotor.spin(fwd);

    wait(2, seconds);

    ElevatorGroup.stop();

    Drivetrain.setDriveVelocity(60, percent);
    Drivetrain.drive(reverse);
  
    wait(AUTON_DRIVE_TIME_SEC, seconds);

    Drivetrain.setDriveVelocity(45, percent);
    Drivetrain.drive(forward);

    wait(0.19, seconds);

        Drivetrain.stop();

    clampOn();

    ElevatorMotor.setVelocity(100, percent);
    ElevatorMotor.spin(reverse);

    wait(2, seconds);

    Drivetrain.stop();

    wait(4, seconds);
    ElevatorGroup.stop();
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
  // User control code here, inside the loop
  int32_t forward, turn;
  
  while (1) {
    // // This is the main execution loop for the user control program.
    // // Each time through the loop your program should update motor + servo
    // // values based on feedback from the joysticks.

    // // ........................................................................
    // // Insert user code here. This is where you use the joystick values to
    // // update your motors, etc.
    // // ........................................................................

    // // Changes turn speed based on float value below

    // Read joystick positions
    forward = Controller.Axis3.position();
    turn = Controller.Axis1.position() * TURN_MULTIPLER;

    // Apply deadzones
    if (abs(forward) < DEADZONE) {
      forward = 0;
    }
    if (abs(turn) < DEADZONE) {
      turn = 0;
    }

    // // Drive the robot using arcade control
    Drivetrain.arcade(forward, turn);

    // Control the clamp mechanism
    if (Controller.ButtonA.PRESSED) {
      if (isClampedOn)
        clampOff();
      else 
        clampOn();
    }

    // Control the elevator motor
    if (Controller.ButtonX.pressing()) {
      ElevatorMotor.setVelocity(100, percent);
      ElevatorMotor.spin(fwd);
    } else if (Controller.ButtonB.pressing()) {
      ElevatorMotor.setVelocity(100, percent);
      ElevatorMotor.spin(reverse);
    } else if (! Controller.ButtonX.pressing() && !Controller.ButtonB.pressing()) {
      ElevatorMotor.stop();
    }

    // // Print clamp status to the controller
    // // if (isClampOn()) {
    // //   Controller.Screen.print("Clamp: On");
    // // } else {
    // //   Controller.Screen.print("Clamp: Off");
    // // }

    // // Print value from ultrasonic sensor
    // Controller.Screen.clearScreen();
    // Controller.Screen.setCursor(2, 0);
    // Controller.Screen.print(getDistanceFromObjectBehind());

    //  if (abs(getDistanceFromObjectBehind()-10) <= 4) {
    //    clampOn();
    //  }

    // ElevatorMotor.setVelocity(150, percent);
    // ElevatorMotor.spin(reverse);
    // ElevatorMotor2.setVelocity(150, percent);
    // ElevatorMotor2.spin(fwd);

    wait(20, msec); // Sleep the task for a short amount of time to
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
