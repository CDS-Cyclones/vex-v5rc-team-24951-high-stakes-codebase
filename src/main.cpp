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
#include "vector"
#include "iostream"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;
//The indexes for colors goes from 1-7, best to use diff indexex for each color
int INDEX_BLUE = 1;
//colorRange and saturationRange is the max diff in total RGB value and Saturation Range such that it'll detect an object as Blue
//A ColorRange of 50 and saturation Range is quite high, these numbers need to be adjusted
double COLOR_RANGE = 50.00;
double SATURATION_RANGE = 0.80;
int RGB_BLUE_R = 55;
int RGB_BLUE_B = 87;
int RGB_BLUE_G = 102;
//this is the Blue that the vision will detect as Blue
aivision::colordesc Blue = aivision::colordesc(INDEX_BLUE,RGB_BLUE_R, RGB_BLUE_B,RGB_BLUE_G,COLOR_RANGE,SATURATION_RANGE);
//AI VISION OBJECT, in port 13
aivision AI = aivision(PORT13, Blue);


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
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
    //updates the AI vision
    AI.takeSnapshot(Blue);
    //size of the object array in the last AI Snapshot
    int size = sizeof(AI.objects)/sizeof(AI.objects[0]);
    //Clear Screen so each time it refreshes it draws anew
     Brain.Screen.clearScreen();

  
    //prints out objectCount
    cout<<AI.objectCount<<endl;
    //drawing a rectange at each object's X, Y coords with the respective width and height for each iteration on the brain screen
    for(int i = 0 ; i< size; i++){
      Brain.Screen.drawRectangle(AI.objects[i].originX, AI.objects[i].originY, AI.objects[i].width, AI.objects[i].height);
    }
  

    wait(100, msec);
  }
}
