/*
  machine_defaults.h - machine specific default settings

  Force-included into every C file by CMakeLists.txt when present, so the core
  (grbl/settings.c) and plugins see the same values. These are the values that
  $RST=* restores.

  Machine: FYSETC R4 V1.0, X = GT2 belt (20T pulley), Z = two ganged motors with
  auto-squaring on 8 mm lead screws, RC servo on the laser connector (M280 P0).
  Settings tested on the machine on 2026-10-19.
*/

#ifndef MACHINE_DEFAULTS_H
#define MACHINE_DEFAULTS_H

// $1 - keep steppers enabled (Z holds against gravity)
#define DEFAULT_STEPPER_IDLE_LOCK_TIME          255
// $3 - invert X direction (X = 1, Y = 2, Z = 4)
#define DEFAULT_DIR_SIGNALS_INVERT_MASK         1
// $20 - soft limits on (requires homing after power on)
#define DEFAULT_SOFT_LIMIT_ENABLE               1
// $22 = 523: homing on (1) + single axis commands (2) + machine origin 0 (8) + per axis feedrates (512)
// Origin 0 = the axis reads MPos 0 after homing and travels in positive direction (0 .. travel - pull-off).
#define DEFAULT_HOMING_ENABLE                   1
#define DEFAULT_HOMING_SINGLE_AXIS_COMMANDS     1
#define DEFAULT_HOMING_FORCE_SET_ORIGIN         1
#define DEFAULT_HOMING_PER_AXIS_FEEDRATES       1
// $23 = 5 - X and Z home toward their minimum (negative) end
#define DEFAULT_HOMING_DIR_MASK                 5
// $26 - homing debounce delay, ms
#define DEFAULT_HOMING_DEBOUNCE_DELAY           50
// $44, $45, $46 - homing order: Z first, then X. Y has no switch.
#define DEFAULT_HOMING_CYCLE_0                  4
#define DEFAULT_HOMING_CYCLE_1                  1
#define DEFAULT_HOMING_CYCLE_2                  0
// $100, $102 - steps/mm: X = 200 * 16 / 40 mm, Z = 200 * 16 / 8 mm
#define DEFAULT_X_STEPS_PER_MM                  80.0f
#define DEFAULT_Z_STEPS_PER_MM                  400.0f
// $110, $112 - max rate, mm/min
#define DEFAULT_X_MAX_RATE                      18000.0f
#define DEFAULT_Z_MAX_RATE                      6000.0f
// $120, $122 - acceleration, mm/s^2
#define DEFAULT_X_ACCELERATION                  6000.0f
#define DEFAULT_Z_ACCELERATION                  600.0f
// $130, $132 - max travel, mm
#define DEFAULT_X_MAX_TRAVEL                    100.0f
#define DEFAULT_Z_MAX_TRAVEL                    90.0f
// $180 - $182 - homing locate feed rate per axis, mm/min
#define DEFAULT_X_HOMING_FEED_RATE              150.0f
#define DEFAULT_Y_HOMING_FEED_RATE              150.0f
#define DEFAULT_Z_HOMING_FEED_RATE              150.0f
// $190 - $192 - homing search seek rate per axis, mm/min
#define DEFAULT_X_HOMING_SEEK_RATE              3000.0f
#define DEFAULT_Y_HOMING_SEEK_RATE              3000.0f
#define DEFAULT_Z_HOMING_SEEK_RATE              600.0f
// $290, $292 - homing pull-off per axis, mm (homing pulloff plugin)
#define DEFAULT_X_HOMING_PULLOFF                2.0f
#define DEFAULT_Z_HOMING_PULLOFF                2.0f
// $481 - status autoreport interval, ms
#define DEFAULT_AUTOREPORT_INTERVAL             1000

#endif
