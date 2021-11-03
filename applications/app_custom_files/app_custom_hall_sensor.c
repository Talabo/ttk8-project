/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        03.11.2021
 *
 */


#include "app_custom_analysis.h"


// Variables
/*
static double custom_hall_sensor_val = 0.0;
static double custom_hall_sensor_val_voltage = 0.0;
*/
static bool custom_hall_sensor_state = false;
// Functions

// Initialize the hall-effect sensor
void app_custom_hall_init(void){

	// Set the Hall Sensor Pin as a DIGITAL PULLUP input
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_PULLUP);

	/*
	// Set the Hall Sensor Pin as an alternate mode for TIM
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_ALTERNATE(HW_CUSTOM_HALL_TIM_AF));

	// TODO: Interrupt functionality
	EXTI_InitTypeDef EXTI_InitStructure;

	// Enable timer clock
	HW_CUSTOM_TIM_CLK_EN();

	// Enable SYSCFG clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);


	// TODO

	//
	TIM_EncoderInterfaceConfig(HW_ENC_TIM, TIM_EncoderMode_TI12,
			TIM_ICPolarity_Rising,
			TIM_ICPolarity_Rising);
	// Replace with (?)

	// NB! TIMx limited to 1,2,3,..,9 or 12!
	// NewState = ENABLE or DISABLE
	TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);


	TIM_SetAutoreload(HW_ENC_TIM, enc_counts - 1);

	// Filter
	HW_ENC_TIM->CCMR1 |= 6 << 12 | 6 << 4;
	HW_ENC_TIM->CCMR2 |= 6 << 4;

	TIM_Cmd(HW_ENC_TIM, ENABLE);

	// Interrupt on index pulse

	// Connect EXTI Line to pin
	SYSCFG_EXTILineConfig(HW_ENC_EXTI_PORTSRC, HW_ENC_EXTI_PINSRC);

	// Configure EXTI Line
	EXTI_InitStructure.EXTI_Line = HW_ENC_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set EXTI Line Interrupt to the highest priority
	nvicEnableVector(HW_ENC_EXTI_CH, 0);

	*/
}

// Deinitialize the hall-effect sensor
void app_custom_hall_deinit(void){

	// Set the Hall Sensor Pin back to analog input (default)
	palSetPadMode(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN, PAL_MODE_INPUT_ANALOG);

	// TODO
	/*
	nvicDisableVector(HW_ENC_EXTI_CH);
	nvicDisableVector(HW_ENC_TIM_ISR_CH);

	TIM_DeInit(HW_ENC_TIM);
	*/
}

// Resets the hall-effect sensor
void app_custom_hall_reset(void){
	// TODO

}

// Reads hall-effect sensor data as digital values
// PAL_LOW (low state) and PAL_HIGH (high state)
// Only works if the pin is defined as DIGITAL
bool app_custom_read_hall_state(void){
	return (palReadPad(CUSTOM_HALL_GPIO, CUSTOM_HALL_PIN) == PAL_HIGH);
}


// Only works if the pin is defined as DIGITAL
bool app_custom_get_sensor_state(void){
	return custom_hall_sensor_state;
}

// Only works if the pin is defined as DIGITAL
void app_custom_set_sensor_state(bool x){
	custom_hall_sensor_state = x;
}


/*
// Reads hall-effect sensor data as ADC (analog value)
// Only works if the pin is defined as ANALOG
double app_custom_read_hall_ADC(void){
	return (double)ADC_Value[CUSTOM_HALL_ADC_INDEX];
}

// Read hall-effect sensor data in voltage level for sensors VCC (typically 5V) or 3.3V
// (Hall-sensor uses 5v source, ADC_IND_EXT2 pin is 5V TOLERANT)
// Only works if the pin is defined as ANALOG
double app_custom_read_hall_voltage(bool is_5V){
	if(is_5V){
		return (double)(ADC_Value[CUSTOM_HALL_ADC_INDEX] / 4096.0 * SENSOR_VCC);
	}else{
		// ADC_VOLTS(ch) == (float)ADC_Value[ADC_IND_EXT2] / 4096.0 * V_REG
		// V_REG = 3.3
		return (double)ADC_VOLTS(CUSTOM_HALL_ADC_INDEX);
	}
}

// Only works if the pin is defined as ANALOG
double app_custom_get_sensor_adc_value(void){
	return custom_hall_sensor_val;
}

// Only works if the pin is defined as ANALOG
double app_custom_get_sensor_adc_voltage(void){
	return custom_hall_sensor_val_voltage;
}

// Only works if the pin is defined as ANALOG
void app_custom_set_sensor_adc_value(double x){
	custom_hall_sensor_val = x;
}

// Only works if the pin is defined as ANALOG
void app_custom_set_sensor_adc_voltage(double x){
	custom_hall_sensor_val_voltage = x;
}
*/


/*
// Estimation of position based on estimator and hall-effect sensor
void app_custom_hall_est_pos(void){

}
*/

