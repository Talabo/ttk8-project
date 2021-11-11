/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        11.11.2021
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

	// Set the Indicator2 pin as a digital output
	palSetPadMode(CUSTOM_INDICATOR2_GPIO, CUSTOM_INDICATOR2_PIN,
			PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);

	// Set indicators to default OFF
	app_custom_indicator_reset();
}

// Deinitialize the indicator
void app_custom_indicator_deinit(void){
	// Set the Indicator Pin back to analog input (default)
	palSetPadMode(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN, CUSTOM_PA6_DEFAULT);
	// Set the Indicator2 Pin back to analog input (default)
	palSetPadMode(CUSTOM_INDICATOR2_GPIO, CUSTOM_INDICATOR2_PIN, CUSTOM_PA7_DEFAULT);
}

// Resets the indicator
void app_custom_indicator_reset(void){
	CUSTOM_INDICATOR_OFF();
	CUSTOM_INDICATOR2_OFF();
}
