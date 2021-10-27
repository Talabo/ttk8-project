/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             21.10.2021
 * Last updated:        27.10.2021
 *
 */


#include "app_custom_analysis.h"


// Variables
static double custom_hall_sensor_val = 0.0;
static double custom_hall_sensor_val_voltage = 0.0;

// Functions

// Initialize the hall-effect sensor
void app_custom_hall_init(void){
	// TODO: For interrupt functionality
	//EXTI_InitTypeDef   EXTI_InitStructure;


	// Set the Hall Sensor Pin as a analog input
	// Already defined correctly in original firmware, in hwconf/hw_60.c (HW: VESC 6 MkV)
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_PULLUP);

	// TODO Replace to this, for interrupt functionality
	//palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_ALTERNATE(HW_CUSTOM_HALL_TIM_AF));

	// TODO
}

// Deinitialize the hall-effect sensor
void app_custom_hall_deinit(void){

	// Set the Hall Sensor Pin back to analog input (default)
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_ANALOG);

	// TODO

}

// Resets the hall-effect sensor
void app_custom_hall_reset(void){
	// TODO

}

// Reads hall-effect sensor data
// (ADC_IND_EXT2 =  HW: VESC 6 MkV, COMM PORT, MISO ADC2 Pin)
double app_custom_read_hall(void){
	return (double)ADC_Value[CUSTOM_HALL_ADC_INDEX];
}

// Read hall-effect sensor data in voltage level for sensors VCC (typically 5V) or 3.3V
// (Hall-sensor uses 5v source, ADC_IND_EXT2 pin is 5V TOLERANT)
double app_custom_read_hall_voltage(bool is_5V){
	if(is_5V){
		return (double)(ADC_Value[CUSTOM_HALL_ADC_INDEX] / 4096.0 * SENSOR_VCC);
	}else{
		// ADC_VOLTS(ch) == (float)ADC_Value[ADC_IND_EXT2] / 4096.0 * V_REG
		// V_REG = 3.3
		return (double)ADC_VOLTS(CUSTOM_HALL_ADC_INDEX);
	}
}


double app_custom_get_sensor_val(void){
	return custom_hall_sensor_val;
}

double app_custom_get_sensor_val_voltage(void){
	return custom_hall_sensor_val_voltage;
}

void app_custom_set_sensor_val(double x){
	custom_hall_sensor_val = x;
}

void app_custom_set_sensor_val_voltage(double x){
	custom_hall_sensor_val_voltage = x;
}

/*
// Estimation of position based on estimator and hall-effect sensor
void app_custom_hall_est_pos(void){

}
*/

