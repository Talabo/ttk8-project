/*
 * Custom Analysis Firmware (TTK8 Project)
 *
 * This custom app is used for analyzing the RTOS (ChibiOS) system in the VESC firmware.
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             12.10.2021
 * Last updated:        16.10.2021
 *
 */

// Custom files
#include "app_custom_analysis.h"


// Threads
static THD_FUNCTION(custom_analysis_thread, arg);
static THD_WORKING_AREA(custom_analysis_thread_wa, 2048); // 2kb stack for this thread

// Function Headers
static void app_custom_create_analysis_thread(void);
static double app_custom_sensor_val_voltage_5V(void);
//static double app_custom_sensor_val_voltage_3V3(void);

// Define variables
#define SENSOR_VCC             5 // Define the voltage level (High level) of the output from sensor
// GPIOA 5 (PA5) is SCK ADC1 on COMM-port for HW: VESC 6 MkV
#define CUSTOM_INDICATOR_ON()  palSetPad(GPIOA, 5);
#define CUSTOM_INDICATOR_OFF() palClearPad(GPIOA, 5);

// Variables
static double custom_hall_sensor_val = 0.0;
static double custom_hall_sensor_val_voltage = 0.0;

// Thread variables
static volatile bool stop_now = true;
static volatile bool is_running = false;




// Create the custom analysis thread
static void app_custom_create_analysis_thread(void){
	chThdCreateStatic(custom_analysis_thread_wa,
					sizeof(custom_analysis_thread_wa),
					custom_thread_priority, custom_analysis_thread, NULL);
}

// Reads hall-effect sensor data
// (ADC_IND_EXT2 =  HW: VESC 6 MkV, COMM PORT, MISO ADC2 Pin)
static double app_custom_read_hall_sensor(void){
	return (double)ADC_Value[ADC_IND_EXT2];
}

// Read hall-effect sensor data in voltage level for 5V logic
// (Hall-sensor uses 5v source, ADC_IND_EXT2 pin is 5V TOLERANT)
static double app_custom_sensor_val_voltage_5V(void){
	return (double)(ADC_Value[ADC_IND_EXT2] / 4096.0 * SENSOR_VCC);
}

/*
// Read hall-effect sensor data in voltage level for 3.3V logic
static double app_custom_sensor_val_voltage_3V3(void){
	// ADC_VOLTS(ch) == (float)ADC_Value[ADC_IND_EXT2] / 4096.0 * V_REG
	// V_REG = 3.3
	return (double)ADC_VOLTS(ADC_IND_EXT2);
}
*/

double app_custom_get_sensor_val(void){
	return custom_hall_sensor_val;
}

double app_custom_get_sensor_val_voltage(void){
	return custom_hall_sensor_val_voltage;
}




// Thread functions

// Called when the custom application is started.
void app_custom_start(void){
	commands_printf("Custom propeller controller app started");

	// Set the SCK ADC1 pin (PA5) as a digital output
	// GPIOA 5 (PA5) is SCK ADC1 on COMM-port for HW: VESC 6 MkV
	palSetPadMode(GPIOA, 5,
			PAL_MODE_OUTPUT_PUSHPULL |
			PAL_STM32_OSPEED_HIGHEST);

	// Set the MISO ADC2 pin (PA6) as a analog input
	// NB! Not to mix with ADC_IND_EXT2 = 7 which is part of the ADC Vector (ADC channel)
	// Commented out, because already established in hwconf/hw_60.c (HW: VESC 6 MkV)
	/*palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_ANALOG);*/

	// Start Thread
	stop_now = false;
	app_custom_create_analysis_thread();
}

// Called when the custom application is stopped.
void app_custom_stop(void){
	commands_printf("Custom analysis app stopped");

	// Unregister all custom commands
	app_custom_unregister_commands();

	// Set PA5 (SCK ADC1 on COMM port) pin back to default (as in hw_60.c)
	palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);

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

		custom_hall_sensor_val = app_custom_read_hall_sensor();
		// utilize 5V (hardware spesific)
		custom_hall_sensor_val_voltage = app_custom_sensor_val_voltage_5V();







		// Put the thread to sleep for 10 ms
		chThdSleepMilliseconds(10);
	}
}

