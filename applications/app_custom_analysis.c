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


#define SENSOR_VCC            5 // Define the voltage level (High level) of the output from sensor

// Threads
static THD_FUNCTION(custom_analysis_thread, arg);
static THD_WORKING_AREA(custom_analysis_thread_wa, 2048); // 2kb stack for this thread

// Function Headers
static void app_custom_register_commands(void);
static void app_custom_unregister_commands(void);
static void app_custom_create_analysis_thread();
static double app_custom_sensor_val_voltage_5V();
static double app_custom_sensor_val_voltage_3V3();

void terminal_custom_set_thread_prority(int argc, const char **argv);
void terminal_custom_get_thread_prority(int argc, const char **argv);
void terminal_custom_update_thread_settings(int argc, const char **argv);

// Thread variables
static volatile bool stop_now = true;
static volatile bool is_running = false;
static double custom_hall_sensor_val = 0.0;
static double custom_hall_sensor_val_voltage = 0.0;

// Variables
static volatile int custom_thread_priority = NORMALPRIO;



// Register custom commands for callbacks
static void app_custom_register_commands(void){

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
static void app_custom_unregister_commands(void){
	terminal_unregister_callback(terminal_custom_get_thread_prority);
	terminal_unregister_callback(terminal_custom_set_thread_prority);
	terminal_unregister_callback(terminal_custom_update_thread_settings);
}

// Create the custom analysis thread
static void app_custom_create_analysis_thread(){
	chThdCreateStatic(custom_analysis_thread_wa,
					sizeof(custom_analysis_thread_wa),
					custom_thread_priority, custom_analysis_thread, NULL);
}


// Reads hall-effect sensor data
// (ADC_IND_EXT2 =  HW: VESC 6 MkV, COMM PORT, MISO ADC2 Pin)
static double app_custom_read_hall_sensor(){
	return (double)ADC_Value(ADC_IND_EXT2);
}

// Read hall-effect sensor data in voltage level for 5V logic
// (Hall-sensor uses 5v source, ADC_IND_EXT2 pin is 5V TOLERANT)
static double app_custom_sensor_val_voltage_5V(){
	return (double)ADC_Value[ch] / 4096.0 * SENSOR_VCC;
}

// Read hall-effect sensor data in voltage level for 3.3V logic
static double app_custom_sensor_val_voltage_3V3(){
	// ADC_VOLTS(ch) == (float)ADC_Value[ch] / 4096.0 * V_REG
	// V_REG = 3.3
	return (double)ADC_VOLTS(ADC_IND_EXT2);
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





// Thread functions

// Called when the custom application is started.
void app_custom_start(void){
	commands_printf("Custom propeller controller app started");

	// TO START UP STUFF HERE
	//palReadPad(GPIOA, )
	// Pin: XXXX as digital output
	//palSetPadMode(GPIOA, 6, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(HW_UART_TX_PORT, HW_UART_TX_PIN, PAL_MODE_INPUT_PULLDOWN);



	// Set the MISO ADC2 pin (PA6) as a analog input
	// NB! Not to mix with ADC_IND_EXT2 = 7 which is part of the ADC Vector (ADC channel)
	// Commented out, because already established in hwconf/hw_60.c (HW: VESC 6 MkV)
	//palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_ANALOG);

	// Start Thread
	stop_now = false;
	app_custom_create_analysis_thread();
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

		custom_hall_sensor_val = app_custom_read_hall_sensor();
		custom_hall_sensor_val_voltage = app_custom_sensor_val_voltage_5V();







		// Put the thread to sleep for 10 ms
		chThdSleepMilliseconds(10);
	}
}

