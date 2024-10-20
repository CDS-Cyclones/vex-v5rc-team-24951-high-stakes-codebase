#include "vex.h"

#include "odometry.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// CONSTANTS
const distanceUnits DISTANCE_UNITS = mm;

const gearSetting DRIVETRAIN_MOTOR_GEAR_RATIO = ratio18_1;
const double WHEEL_CIRCUMFERENCE = 3.25 * atan(1) * 4;

/**
 * Track width - dist. b/w right wheels’ and left wheels’ center points.
 * Wheelbase - dist. b/w  drive shafts of the two drive wheels on the side.
 * @link https://kb.vex.com/hc/en-us/articles/360057008811-Finding-Your-Robot-s-Track-Width-and-Wheelbase
 */
const double TRACK_WIDTH = 284.48;
const double WHEELBASE = 127;

/**
 * If external gears used, GR = # of driven gear teeth / # of driving gear teeth
 * If no external gears used, GR = 1
 * Gear that provides the power, or input, is called a driving gear and the gear that is being turned, or responsible for the output, is called the driven gear
 * @link https://kb.vex.com/hc/en-us/articles/360035590932-Using-Gear-Ratios-with-the-V5-Motor
 */
const int EXTERNAL_GEAR_RATIO = 1;

// DRIVETRAIN MOTORS' PORTS ON BRAIN
const int32_t LEFT_FRONT_MOTOR_PORT = PORT1;
const int32_t LEFT_MIDDLE_MOTOR_PORT = PORT3;
const int32_t LEFT_BACK_MOTOR_PORT = PORT5;
const int32_t RIGHT_FRONT_MOTOR_PORT = PORT2;
const int32_t RIGHT_MIDDLE_MOTOR_PORT = PORT4;
const int32_t RIGHT_BACK_MOTOR_PORT = PORT6;

// WHETHER MOTORS NEED TO BE INVERTED
const bool LEFT_FRONT_MOTOR_INVERTED = false;
const bool LEFT_MIDDLE_MOTOR_INVERTED = false;
const bool LEFT_BACK_MOTOR_INVERTED = false;
const bool RIGHT_FRONT_MOTOR_INVERTED = true;
const bool RIGHT_MIDDLE_MOTOR_INVERTED = true;
const bool RIGHT_BACK_MOTOR_INVERTED = true;

// INERTIAL DEFINITION
inertial Inertial = inertial(PORT15);

triport::port CLAMP_PNEUMATIC_PORT = Brain.ThreeWirePort.E;

digital_out ClampPneumatic = digital_out(CLAMP_PNEUMATIC_PORT);

/**
 * Whether the clamp is on
 */
bool isClampedOn;

motor LeftFrontMotor = motor(LEFT_FRONT_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, LEFT_FRONT_MOTOR_INVERTED);
motor LeftMiddleMotor = motor(LEFT_MIDDLE_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, LEFT_MIDDLE_MOTOR_INVERTED);
motor LeftBackMotor = motor(LEFT_BACK_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, LEFT_BACK_MOTOR_INVERTED);
motor RightFrontMotor = motor(RIGHT_FRONT_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, RIGHT_FRONT_MOTOR_INVERTED);
motor RightMiddleMotor = motor(RIGHT_MIDDLE_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, RIGHT_MIDDLE_MOTOR_INVERTED);
motor RightBackMotor = motor(RIGHT_BACK_MOTOR_PORT, DRIVETRAIN_MOTOR_GEAR_RATIO, RIGHT_BACK_MOTOR_INVERTED);

motor_group LeftDriveSmart = motor_group(LeftFrontMotor, LeftMiddleMotor, LeftBackMotor);
motor_group RightDriveSmart = motor_group(RightFrontMotor, RightMiddleMotor, RightBackMotor);

drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, WHEEL_CIRCUMFERENCE, TRACK_WIDTH, WHEELBASE, DISTANCE_UNITS, EXTERNAL_GEAR_RATIO);

controller Controller = controller();

odometry Odometry = odometry();

/** 
 * Extend the clamp's actuator
 */
void clampOn(void) {
  ClampPneumatic.set(false);

  isClampedOn = true;
}

/**
 * Retract the clamp's actuator
 */
void clampOff(void) {
  ClampPneumatic.set(true);

  isClampedOn = false;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  //Calibrate inertial sensor **MUST BE STATIONARY**
  Inertial.calibrate(3);

  // Print that the Inertial Sensor is calibrating while waiting for it to finish calibrating.
  while(Inertial.isCalibrating()){
    Brain.Screen.clearScreen();

    // Sets coordinates of where to print on brain
    Brain.Screen.setCursor(10,10);
    Brain.Screen.print("Inertial Calibrating");
    wait(50, msec);
  }

  //Print that Inertial is calibrated
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(10,10);
  Brain.Screen.print("Inertial Calibrated");

  // Resets heading of inertial to zero
  Inertial.resetHeading();  
  
  // Retract clamp actuator at launch
  clampOff();

  // Initialize position relative to left corner of the filed facing right to (0, 0, 0)
  Odometry.reset();

  // Rumble controller to indicate that initialization complete
  Controller.rumble(".");
}