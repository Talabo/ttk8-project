/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             21.10.2021
 * Last updated:        21.10.2021
 *
 */

#include "app_custom_analysis.h"

// Variables

// Functions

// Initialize the indicator
void app_custom_indicator_init(void){
	// Set the Indicator pin as a digital output
	palSetPadMode(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN,
			PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
}

// Deinitialize the indicator
void app_custom_indicator_deinit(void){
	// Set the Indicator Pin back to analog input (default)
	palSetPadMode(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN, PAL_MODE_INPUT_ANALOG);
}

// Resets the indicator
void app_custom_indicator_reset(void){
	CUSTOM_INDICATOR_OFF();
}
