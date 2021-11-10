/*
 * Custom Analysis Firmware (TTK8 Project)
 *
 * This custom app is used for analyzing the RTOS (ChibiOS) system in the VESC firmware.
 *
 * Created by:          Emil Jenssen
 * Last updated:        10.11.2021
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
static volatile tprio_t custom_thread_priority = NORMALPRIO;

// Variables
uint32_t analysis_time_start;
bool analysis_time_taker;
int analysis_time_sample;
double analysis_time_total;
double analysis_time_average;

void app_custom_set_thread_priority(tprio_t priority){
	custom_thread_priority = priority;
}

tprio_t app_custom_get_thread_priority(void){
	return custom_thread_priority;
}

void app_custom_set_analysis_time_taker(bool x){
	analysis_time_taker = x;
}

bool app_custom_get_tanalysis_time_taker(void){
	return analysis_time_taker;
}

void app_custom_reset_analysis_timer(void){
	analysis_time_start = 0.0;
	analysis_time_sample = 0;
	analysis_time_total = 0.0;
	analysis_time_average = 0.0;
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

	analysis_time_taker = false;
	analysis_time_start = 0.0;
	analysis_time_sample = 0;
	analysis_time_total = 0.0;
	analysis_time_average = 0.0;

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

		// Timer analyser
		// Take the time elapsed
		if(analysis_time_taker){
			double analysis_time_elapsed = timer_seconds_elapsed_since(analysis_time_start)/ 1000000000.0; // nanoseconds
			commands_printf("Time elapsed while NOT active: %.12f ns", analysis_time_elapsed);
			analysis_time_sample++;
			analysis_time_total = analysis_time_total + analysis_time_elapsed;
			analysis_time_average = analysis_time_total/analysis_time_sample;
			if(analysis_time_sample >= 100) analysis_time_sample = 1;
			commands_printf("Average time (100 samples): %.12f ns", analysis_time_average);
		}

		// Read and set the sensor state
		app_custom_set_sensor_state(app_custom_read_hall_state());


		// Set the indicator status corresponding to the sensor state
		if(app_custom_get_sensor_state()){
			CUSTOM_INDICATOR_ON();
		}else{
			CUSTOM_INDICATOR_OFF();
		}

		// Continuously plot the experiment plotter
		custom_experiment_plots();

		// Timer analyser
		if(analysis_time_taker){
			// start timer
			analysis_time_start = timer_time_now();
		}


		// Put the thread to sleep for 10 ms
		chThdSleepMilliseconds(10);
	}
}

