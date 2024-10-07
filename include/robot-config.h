using namespace vex;

extern brain Brain;

extern motor LeftFrontMotor;
extern motor LeftMiddleMotor;
extern motor LeftBackMotor;

extern motor RightFrontMotor;
extern motor RightMiddleMotor;
extern motor RightBackMotor;

extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

extern drivetrain Drivetrain;

extern controller Controller;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
