/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        16.11.2021
 *
 */

#include "app_custom_analysis.h"


// Variables
static bool custom_hall_sensor_state = false;

// Functions

/*
// SOLUTION #1
// Initialize the hall-effect sensor
void app_custom_hall_init(void){
	// Set the Hall Sensor Pin as a DIGITAL PULLUP input
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_PULLUP);
}
*/

// SOLUTION #2
void app_custom_hall_init(void){

	// Set the Hall Sensor Pin as a (Digital) PULLUP input
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_PULLUP);

	// Interrupt on Hall effect sensor (index pulse)

	// Interrupt initial structure
	EXTI_InitTypeDef EXTI_InitStructure;

	// Connect EXTI Line to pin
	SYSCFG_EXTILineConfig(HW_CUSTOM_HALL_EXTI_PORTSRC, HW_CUSTOM_HALL_EXTI_PINSRC);

	// Configure EXTI Line
	EXTI_InitStructure.EXTI_Line = HW_CUSTOM_HALL_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // For experiment
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set EXTI Line Interrupt to the highest priority
	nvicEnableVector(HW_CUSTOM_HALL_EXTI_CH, 0);

}

// Deinitialize the hall-effect sensor
void app_custom_hall_deinit(void){
	// Deinitialize the External Interrupt for Hall Sensor
	nvicDisableVector(HW_ENC_EXTI_CH);
	nvicDisableVector(HW_ENC_TIM_ISR_CH);

	// Set the Hall Sensor Pin back to default (PA6)
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, CUSTOM_PA6_DEFAULT);
}

// Resets the hall-effect sensor
void app_custom_hall_reset(void){
	custom_hall_sensor_state = false;
}

// Reads hall-effect sensor data as digital values
// PAL_LOW (low state) and PAL_HIGH (high state)
bool app_custom_read_hall_state(void){
	// Checks if the in corresponds to logic level PAL_HIGH (opposite is PAL_LOW)
	return (palReadPad(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN) == PAL_HIGH);
}

bool app_custom_get_sensor_state(void){
	return custom_hall_sensor_state;
}

void app_custom_set_sensor_state(bool x){
	custom_hall_sensor_state = x;
}


// Interrupt ReQuest
CH_IRQ_HANDLER(HW_CUSTOM_HALL_EXTI_ISR_VEC) {
	if (EXTI_GetITStatus(HW_CUSTOM_HALL_EXTI_LINE) != RESET) {

		// Read and set the sensor state
		app_custom_set_sensor_state(app_custom_read_hall_state());
		// Set the indicator status corresponding to the sensor state
		if(app_custom_get_sensor_state()){
			CUSTOM_INDICATOR2_ON();
		}else{
			CUSTOM_INDICATOR2_OFF();
		}

		// Clear the EXTI line pending bit
		EXTI_ClearITPendingBit(HW_CUSTOM_HALL_EXTI_LINE);
	}
}

