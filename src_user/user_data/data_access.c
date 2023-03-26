#include "data_access.h"


/*
 * This is to store the valid incoming message from the user
 */
data_access user_conf_data[] = {

    {.message = "PWR_PITCH"    , .type = INTEGER,   .data_int   = &motor_pitch.power,      .data_int_min = 0,     .data_int_max = 100},
    {.message = "PP_PITCH"     , .type = INTEGER,   .data_int   = &motor_pitch.pole_pair,  .data_int_min = 0,     .data_int_max = 20},   
    {.message = "DIR_PITCH"    , .type = INTEGER,   .data_int   = &motor_pitch.direction,  .data_int_min = -1,    .data_int_max = 1},
    {.message = "P_ANG_PITCH"  , .type = FLOATING,  .data_float = &pid_pitch_angle.kp,     .data_float_min = 0,   .data_float_max = 1000},
    {.message = "P_ROT_PITCH"  , .type = FLOATING,  .data_float = &pid_pitch_rotation.kp,  .data_float_min = 0,   .data_float_max = 1000},
    {.message = "I_ROT_PITCH"  , .type = FLOATING,  .data_float = &pid_pitch_rotation.ki,  .data_float_min = 0,   .data_float_max = 1000},   
    {.message = "D_ROT_PITCH"  , .type = FLOATING,  .data_float = &pid_pitch_rotation.kd,  .data_float_min = 0,   .data_float_max = 1000},
    {.message = "ANGLE_PITCH"  , .type = FLOATING,  .data_float = &user_pitch_angle,       .data_float_min = -90, .data_float_max = 90},

    {.message = "PWR_ROLL"    , .type = INTEGER,    .data_int   = &motor_roll.power,       .data_int_min = 0,     .data_int_max = 100},
    {.message = "PP_ROLL"     , .type = INTEGER,    .data_int   = &motor_roll.pole_pair,   .data_int_min = 0,     .data_int_max = 20},   
    {.message = "DIR_ROLL"    , .type = INTEGER,    .data_int   = &motor_roll.direction,   .data_int_min = -1,    .data_int_max = 1},
    {.message = "P_ANG_ROLL"  , .type = FLOATING,   .data_float = &pid_roll_angle.kp,      .data_float_min = 0,   .data_float_max = 1000},
    {.message = "P_ROT_ROLL"  , .type = FLOATING,   .data_float = &pid_roll_rotation.kp,   .data_float_min = 0,   .data_float_max = 1000},
    {.message = "I_ROT_ROLL"  , .type = FLOATING,   .data_float = &pid_roll_rotation.ki,   .data_float_min = 0,   .data_float_max = 1000},   
    {.message = "D_ROT_ROLL"  , .type = FLOATING,   .data_float = &pid_roll_rotation.kd,   .data_float_min = -1,  .data_float_max = 1000},

    {.message = "PWR_YAW"     , .type = INTEGER,    .data_int   = &motor_yaw.power,        .data_int_min = 0,     .data_int_max = 100},
    {.message = "PP_YAW"      , .type = INTEGER,    .data_int   = &motor_yaw.pole_pair,    .data_int_min = 0,     .data_int_max = 20},   
    {.message = "DIR_YAW"     , .type = INTEGER,    .data_int   = &motor_yaw.direction,    .data_int_min = -1,    .data_int_max = 1},
    {.message = "P_ROT_YAW"   , .type = FLOATING,   .data_float = &pid_yaw_rotation.kp,    .data_float_min = 0,   .data_float_max = 1000},
    {.message = "I_ROT_YAW"   , .type = FLOATING,   .data_float = &pid_yaw_rotation.ki,    .data_float_min = 0,   .data_float_max = 1000},   
    {.message = "D_ROT_YAW"   , .type = FLOATING,   .data_float = &pid_yaw_rotation.kd,    .data_float_min = -1,  .data_float_max = 1000},

    {.message = "DEBUG"        , .type = INTEGER,   .data_int   = &debug,                  .data_int_min = 0,     .data_int_max = 1},

    {.message = "RESISTOR_UP"  , .type = FLOATING,  .data_float = &resistor_up,          .data_float_min = 0,   .data_float_max = 1000},
    {.message = "RESISTOR_DOWN", .type = FLOATING,  .data_float = &resistor_down,        .data_float_min = 0,   .data_float_max = 1000},
    {.message = "BATT_VOLT"    , .type = FLOATING,  .data_float = &battery_voltage,      .data_float_min = 0,   .data_float_max = 0},
    {.message = "BATT_APLHA"   , .type = FLOATING,  .data_float = &battery_voltage_alpha,.data_float_min = 0,   .data_float_max = 1},    

    {.message = "ENABLE_IMU2"      , .type = INTEGER,   .data_int = &imu_platform_enable,.data_int_min = 0,     .data_int_max = 1},
    {.message = "IMU1_ORIENTATION" , .type = INTEGER,   .data_int = &imu_cam.orientation,.data_int_min = 1,     .data_int_max = 24},
    {.message = "IMU2_ORIENTATION" , .type = INTEGER,   .data_int = &imu_platform.orientation,.data_int_min = 1,.data_int_max = 24},

    {.message = "MODE"           , .type = INTEGER, .data_int   = &user_gimbal_mode_data.gimbal_mode  , .data_int_min = 1  , .data_int_max = 3},
    {.message = "YAW_DEAD_ZONE"  , .type = FLOATING,.data_float = &user_gimbal_mode_data.yaw_dead_zone, .data_float_min = 4, .data_float_max = 15},
    {.message = "YAW_SPEED"      , .type = INTEGER, .data_int   = &user_gimbal_mode_data.yaw_speed    , .data_int_min = 1,   .data_int_max = 5},
    {.message = "PITCH_DEAD_ZONE", .type = FLOATING,.data_float = &user_gimbal_mode_data.yaw_dead_zone, .data_float_min = 4, .data_float_max = 15},
    {.message = "PITCH_SPEED"    , .type = INTEGER, .data_int   = &user_gimbal_mode_data.yaw_speed    , .data_int_min = 1,   .data_int_max = 5},

    {.message = "RC_PITCH_UPPER"    , .type = INTEGER, .data_int   = &pitch_rc_conf.upper_threshold      , .data_int_min = 0  , .data_int_max = 3000},
    {.message = "RC_PITCH_LOWER"    , .type = INTEGER, .data_int   = &pitch_rc_conf.lower_threshold      , .data_int_min = 0  , .data_int_max = 3000},
    {.message = "RC_PITCH_CENTER"   , .type = INTEGER, .data_int   = &pitch_rc_conf.center               , .data_int_min = 0,   .data_int_max = 3000},
    {.message = "RC_PITCH_DEAD_ZONE", .type = INTEGER, .data_int   = &pitch_rc_conf.dead_zone            , .data_int_min = 5,   .data_int_max = 200},
    {.message = "RC_PITCH_DIR"      , .type = INTEGER, .data_int   = &pitch_rc_conf.direction            , .data_int_min = -1,  .data_int_max = 1},

    {.message = "RC_YAW_UPPER"    , .type = INTEGER, .data_int   = &yaw_rc_conf.upper_threshold      , .data_int_min = 0  , .data_int_max = 3000},
    {.message = "RC_YAW_LOWER"    , .type = INTEGER, .data_int   = &yaw_rc_conf.lower_threshold      , .data_int_min = 0  , .data_int_max = 3000},
    {.message = "RC_YAW_CENTER"   , .type = INTEGER, .data_int   = &yaw_rc_conf.center               , .data_int_min = 0,   .data_int_max = 3000},
    {.message = "RC_YAW_DEAD_ZONE", .type = INTEGER, .data_int   = &yaw_rc_conf.dead_zone            , .data_int_min = 5,   .data_int_max = 200},
    {.message = "RC_YAW_DIR"      , .type = INTEGER, .data_int   = &yaw_rc_conf.direction            , .data_int_min = -1,  .data_int_max = 1},
};

const int length_user_conf_data = sizeof(user_conf_data) / sizeof(user_conf_data[0]);