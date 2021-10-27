/*
 * Custom Analysis Firmware (TTK8 Project)
 *
 * This custom app is used for analyzing the RTOS (ChibiOS) system in the VESC firmware.
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             12.10.2021
 * Last updated:        23.10.2021
 *
 */

// Custom files
#include "app_custom_analysis.h"


// Threads
static THD_FUNCTION(custom_analysis_thread, arg);
static THD_WORKING_AREA(custom_analysis_thread_wa, 2048); // 2kb stack for this thread

// Function Headers
static void app_custom_create_analysis_thread(void);

// Thread variables
static volatile bool stop_now = true;
static volatile bool is_running = false;
static volatile int custom_thread_priority = NORMALPRIO;


void app_custom_set_thread_priority(int priority){
	custom_thread_priority = priority;
}

int app_custom_get_thread_priority(void){
	return custom_thread_priority;
}


// Create the custom analysis thread
static void app_custom_create_analysis_thread(void){
	chThdCreateStatic(custom_analysis_thread_wa,
					sizeof(custom_analysis_thread_wa),
					custom_thread_priority, custom_analysis_thread, NULL);
}


// Thread functions

// Called when the custom application is started.
void app_custom_start(void){
	commands_printf("Custom propeller controller app started");

	// Register all custom commands
	app_custom_register_commands();
	// Initialize the hall-effect sensor
	app_custom_hall_init();
	// Initialize the indicator
	app_custom_indicator_init();
	// Initialize the experiment plotter
	custom_experiment_plots_init();

	// Start Thread
	stop_now = false;
	app_custom_create_analysis_thread();
}

// Called when the custom application is stopped.
void app_custom_stop(void){
	commands_printf("Custom analysis app stopped");

	// Unregister all custom commands
	app_custom_unregister_commands();
	// Deinitialize the hall-effect sensor
	app_custom_hall_deinit();
	// Deinitialize the indicator
	app_custom_indicator_deinit();


	// Sets true to exit the loop in the thread
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

		app_custom_set_sensor_val(app_custom_read_hall());
		// Read hall sensor voltage (false is for 3.3V, hardware spesific)
		app_custom_set_sensor_val_voltage(app_custom_read_hall_voltage(false));

		// Continuously plot the experiment plotter
		custom_experiment_plots();

		// TODO




		// Put the thread to sleep for 10 ms
		chThdSleepMilliseconds(10);
	}
}

