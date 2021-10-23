/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             16.10.2021
 * Last updated:        23.10.2021
 *
 */

#ifndef APP_CUSTOM_ANALYSIS_H_
#define APP_CUSTOM_ANALYSIS_H_

// App and RTOS system
#include "app.h"			// Application framework
#include "ch.h" 			// ChibiOS
#include "hal.h" 			// ChibiOS HAL

// Microcontroller spesific
//#include "stm32f4xx_conf.h" // For STM32F4xx, HW: VESC 6 MkV

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
#include "app_custom_plotter.h"
#include "app_custom_commands.h"
#include "app_custom_hall_sensor.h"
#include "app_custom_indicator.h"

// Variables


// Functions
void app_custom_set_thread_priority(int priority);
int app_custom_get_thread_priority(void);



#endif /* APP_CUSTOM_ANALYSIS_H_ */



