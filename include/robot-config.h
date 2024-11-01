using namespace vex;

extern brain Brain;

extern digital_out ClampPneumatic;
extern digital_out PivotPneumatic;

extern motor LeftFrontMotor;
extern motor LeftMiddleMotor;
extern motor LeftBackMotor;

extern motor RightFrontMotor;
extern motor RightMiddleMotor;
extern motor RightBackMotor;

extern motor ElevatorMotor;

extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

extern drivetrain Drivetrain;

extern controller Controller;

extern inertial Inertial;

/**
 * Whether the clamp is on
 */
extern bool isClampedOn;

/** 
 * Extend the clamp's actuator
 */
void clampOn(void);

/** 
 * Retract the clamp's actuator
 */
void clampOff(void);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
