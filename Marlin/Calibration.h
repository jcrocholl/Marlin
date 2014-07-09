/**
 * This file contains the important calibration settings for your Delta printer
 * in one place.
 * 
 * During calibration of your printer, each one of these will be customized
 * to suit your printers geometry, and stepper motor setup.
 * 
 * See the file Configuration.h for the meaning of each of these confituration
 * options.
 * 
 * NOTE: This file contains values that would suit a Kossel Mini. If you have
 * a Kossel Air, or other printer, these will be quite different.
 **/

#ifndef __CALIBRATION_H
#define __CALIBRATION_H

// This is a RAMPS board
#define MOTHERBOARD 33

// Define this to set a custom name for your generic Mendel,
#define STRING_CONFIG_H_AUTHOR "(tmolteno, Mini Kossel)" // Who made the changes.

//===========================================================================
//============================== Delta Settings =============================
//===========================================================================

// First thing to calibrate is the manual home position
// For delta: Distance between nozzle and print surface after homing.
#define MANUAL_Z_HOME_POS 206.8  

// Center-to-center distance of the holes in the diagonal push rods.
#define DELTA_DIAGONAL_ROD 214.5 // mm

// Horizontal offset from middle of printer to smooth rod center.
#define DELTA_SMOOTH_ROD_OFFSET 139.0 // mm

// Horizontal offset of the universal joints on the end effector.
#define DELTA_EFFECTOR_OFFSET 20.0 // mm

// Horizontal offset of the universal joints on the carriages.
#define DELTA_CARRIAGE_OFFSET 12.0 // mm

// Print surface diameter/2 minus unreachable space (avoid collisions with vertical towers).
#define DELTA_PRINTABLE_RADIUS 80.0


// Stepper Motor And Gear Calibration

#define XYZ_FULL_STEPS_PER_ROTATION 200
#define XYZ_MICROSTEPS 16
#define XYZ_BELT_PITCH 2    // millimeters
#define XYZ_PULLEY_TEETH 16

// After printing a test cube, insert a factor here that will scale your object to 
// the correct dimensions
#define SCALING_FACTOR 0.97

// During extruder calibration, modify this value so that
// the extruder extrudes the correct length.
#define EXTRUDER_STEPS 520

#define DEFAULT_MAX_FEEDRATE          {200, 200, 200, 200}    // (mm/sec)
#define DEFAULT_MAX_ACCELERATION      {4500,4500,4500,4500}    // X, Y, Z, E maximum start speed for accelerated moves. E default values are good for skeinforge 40+, for older versions raise them a lot.

/* Reduce these for smoother printing */
#define DEFAULT_ACCELERATION          1500    // X, Y, Z and E max acceleration in mm/s^2 for printing moves
#define DEFAULT_RETRACT_ACCELERATION  3000   // X, Y, Z and E max acceleration in mm/s^2 for retracts

// The speed change that does not require acceleration (i.e. the software might assume it can be done instantaneously)
#define DEFAULT_XYJERK                2.0    // (mm/sec)
#define DEFAULT_ZJERK                 2.0    // (mm/sec)
#define DEFAULT_EJERK                 5.0    // (mm/sec)

// All remaining calibration options are in the file Configuration.h

#endif //____CALIBRATION_H
