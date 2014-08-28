/**
  * MyConfiguration.h.example
  *
  * The intention of this file is to contain things particular to your configuration.
  * Configuration.h is a mixture of logic and settings, and the separation into MyConfiguration.h for
  * user specifics and Configuration.h for knock-on settings should help make merging easier on people.
  *
  * This is an example file, as used by Eddie Parker to drive his board.  More settings may be possible,
  * peruse the Configuration.h to see what can be overriden in here.  For now, you can copy this file
  * to MyConfiguration.h, and edit the values as makes sense for you.
  *
  * This example is for a deltabot style kossel pro reprap.
  */
#ifndef MY_CONFIGURATION_H
#define MY_CONFIGURATION_H

#define MOTHERBOARD 33  // RAMPS
#define BAUDRATE 115200 // Seems to cause issues if I go above with the mega.

// Positive values move the extruder lower
#define EXTRUDER_Z_OFFSET 0 // Reset to zero so we keep our dimensions.  FSR's should fix the levelling issue.

#define DELTA_SMOOTH_ROD_OFFSET    (209.55+EXTRUDER_Z_OFFSET)
#define DELTA_DIAGONAL_ROD        298.45
#define DELTA_EFFECTOR_OFFSET    25.4
#define DELTA_CARRIAGE_OFFSET    25.4
#define DELTA_PRINTABLE_RADIUS 100

#define X_MIN_ENDSTOP_NO true
#define Y_MIN_ENDSTOP_NO true
#define Z_MIN_ENDSTOP_NO true
#define X_MAX_ENDSTOP_NO true
#define Y_MAX_ENDSTOP_NO true
#define Z_MAX_ENDSTOP_NO true

#define X_HOME_DIR 1
#define Y_HOME_DIR 1
#define Z_HOME_DIR 1

#define XYZ_FULL_STEPS_PER_ROTATION 200
#define XYZ_MICROSTEPS 16
#define XYZ_BELT_PITCH 2
#define XYZ_PULLEY_TEETH 20

#define  MANUAL_Z_HOME_POS 298.7 // Distance between nozzle and printer

#define HOMING_FEEDRATE {150*60, 150*60, 150*60, 0}  // set the homing speeds (mm/min)

#define INVERT_E0_DIR true
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define E_STEPS 500

//#define LEDS
//#define NEOPIXEL_PIN 3

#endif
