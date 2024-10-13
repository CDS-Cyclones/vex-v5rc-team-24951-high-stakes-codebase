using namespace vex;

extern brain Brain;

extern digital_out ClampPneumatic;
extern digital_out PivotPneumatic;

extern controller Controller;

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
