/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        10.11.2021
 *
 */

#ifndef APP_CUSTOM_ANALYSIS_H_
#define APP_CUSTOM_ANALYSIS_H_

// App and RTOS system
#include "app.h"			// Application framework
#include "ch.h" 			// ChibiOS
#include "hal.h" 			// ChibiOS HAL

// Some useful includes
#include "mc_interface.h" 	// Motor Control functions
#include "mcpwm.h"			// Motor Control PWM functions
#include "mcpwm_foc.h"		// Motor Control FOC functions
#include "encoder.h" 		// Encoder functions
//#include "bms.h"			// Battery Management System (External BMS system)
#include "mempools.h"		// Memory Pool, for access to memory in VESC

#include "utils.h" 			// Utility functions
#include "hw.h"				// Pin mapping for hardware

#include "terminal.h" 		// Terminal functions (Commands through the terminal)
#include "commands.h"		// Commands functions
#include "comm_can.h"		// CANbus functions

#include "datatypes.h"		// Datatypes for the VESC
#include "timer.h"			// Timer functions
#include "timeout.h"		// Time out functions (To reset timeout) (NEEDED?)

// C built-in functionalities
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <limits.h> // To define limits of integers for terminal inputs


// Custom files
#include "app_custom_hw.h"
#include "app_custom_plotter.h"
#include "app_custom_commands.h"
#include "app_custom_hall_sensor.h"
#include "app_custom_indicator.h"

// Variables


// Functions
void app_custom_set_thread_priority(tprio_t priority);
tprio_t app_custom_get_thread_priority(void);

void app_custom_set_analysis_time_taker(bool x);
bool app_custom_get_tanalysis_time_taker(void);
void app_custom_reset_analysis_timer(void);



#endif /* APP_CUSTOM_ANALYSIS_H_ */



