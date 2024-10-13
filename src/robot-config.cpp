#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

triport::port CLAMP_PNEUMATIC_PORT = Brain.ThreeWirePort.A;

digital_out ClampPneumatic = digital_out(CLAMP_PNEUMATIC_PORT);

controller Controller = controller();

/**
 * Whether the clamp is on
 */
bool isClampedOn;

/** 
 * Extend the clamp's actuator
 */
void clampOn(void) {
  ClampPneumatic.set(false);

  isClampedOn = false;
}

/** 
 * Retract the clamp's actuator
 */
void clampOff(void) {
  ClampPneumatic.set(true);

  isClampedOn = true;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Retract clamp actuator at launch
  clampOff();
}