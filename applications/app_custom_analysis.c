/*
 * Custom Analysis Firmware (TTK8 Project)
 *
 * This custom app is used for analyzing the RTOS (ChibiOS) system in the VESC firmware.
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             12.10.2021
 * Last updated:        12.10.2021
 *
 */

#include "conf_general.h"

// Essential includes for application structure
#include "app.h"			// Application framework
#include "ch.h" 			// ChibiOS
#include "hal.h" 			// ChibiOS HAL

// Some useful includes
#include "mc_interface.h" 	// Motor Control functions
#include "mcpwm.h"			// Motor Control PWM functions
#include "mcpwm_foc.h"		// Motor Control FOC functions
#include "encoder.h" 		// Encoder functions
//#include "bms.h"			// Battery Management System (External BMS system)

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


// Threads
static THD_FUNCTION(custom_analysis_thread, arg);
static THD_WORKING_AREA(custom_analysis_thread_wa, 2048); // 2kb stack for this thread

// Function Headers
void app_custom_register_commands(void);
void app_custom_unregister_commands(void);
void terminal_custom_set_thread_prority(int argc, const char **argv);
void terminal_custom_get_thread_prority(int argc, const char **argv);
void terminal_custom_update_thread_settings(int argc, const char **argv);
static void app_custom_create_thread();

// Thread variables
static volatile bool stop_now = true;
static volatile bool is_running = false;

// Variables
static volatile int custom_thread_priority = NORMALPRIO;


// Register custom commands for callbacks
void app_custom_register_commands(void){

	// Thread Priority
	terminal_register_command_callback(
			"custom_debug_off",
			"Get the thread priority for the custom analysis thread.",
			0,
			terminal_custom_get_thread_prority);

	terminal_register_command_callback(
			"custom_set_thread_priority",
			"Set the thread priority for the custom analysis thread. Default: NORMALPRIO (128)",
			"[0-255]",
			terminal_custom_set_thread_prority);

	// Updates thread settings by restarting all apps
	terminal_register_command_callback(
				"custom_update_thread_settings",
				"Updates the thread settings by restarting all threads.",
				0,
				terminal_custom_update_thread_settings);
}


// Unregister custom commands for callbacks
void app_custom_unregister_commands(void){
	terminal_unregister_callback(terminal_custom_get_thread_prority);
	terminal_unregister_callback(terminal_custom_set_thread_prority);
	terminal_unregister_callback(terminal_custom_update_thread_settings);
}

void terminal_custom_set_thread_prority(int argc, const char **argv){
	if(argc == 2) {
		int d = -1;
		sscanf(argv[1], "%d", &d);
		commands_printf("You have entered %d", d);

		if(d < 0 || d > 255) {
			commands_printf("Invalid range. Range is [0, 255]");
			return;
		}

		custom_thread_priority = d;
		commands_printf("The thread priority is set to %d", d);

	}else{
		commands_printf("This command requires one argument.\n");
	}
}

// Gets the eRPM threshold value
void terminal_custom_get_thread_prority(int argc, const char **argv){
	(void)argc;
	(void)argv;
	commands_printf("The thread priority is: ", custom_thread_priority);
}

// Updates the thread settings to the thread, by calling app_set_configuration()
// app_set_configuration() stops all app threads, starts them and configures them.
void terminal_custom_update_thread_settings(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_configuration *appconf = mempools_alloc_appconf();
	conf_general_read_app_configuration(appconf);
	app_set_configuration(appconf);
}

static void app_custom_create_thread(){
	chThdCreateStatic(custom_analysis_thread_wa,
					sizeof(custom_analysis_thread_wa),
					custom_thread_priority, custom_analysis_thread, NULL);
}



// Thread functions

// Called when the custom application is started.
void app_custom_start(void){
	commands_printf("Custom propeller controller app started");

	// TO START UP STUFF HERE

	// Start Thread
	stop_now = false;
	app_custom_create_thread();
}

// Called when the custom application is stopped.
void app_custom_stop(void){
	commands_printf("Custom analysis app stopped");

	// TO STOP UP STUFF HERE
	app_custom_unregister_commands();

	stop_now = true;

	while (is_running) {
		chThdSleepMilliseconds(1);
	}
}

// Called when the custom application is being configured.
void app_custom_configure(app_configuration *conf) {
	(void)conf;
	commands_printf("Custom analysis app configured");

	// TO CONFIG STUFF HERE
}

// The thread function.
// This is where continuous logic happens
static THD_FUNCTION(custom_analysis_thread, arg){
	(void)arg;

	chRegSetThreadName("APP_CUSTOM_ANALYSIS");

	is_running = true;

	for(;;) {

		//if(custom_get_debug_custom()) commands_printf("CUSTOM start of loop");

		// Check if it is time to stop.
		if (stop_now) {
			is_running = false;
			return;
		}

		timeout_reset(); // Reset timeout if everything is OK.

		// Run the thread logic here //






		// Put the thread to sleep for 10 ms
		chThdSleepMilliseconds(10);
	}
}

