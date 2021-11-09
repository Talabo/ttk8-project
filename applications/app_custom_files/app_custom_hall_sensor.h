/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        09.11.2021
 *
 */

#ifndef APP_CUSTOM_HALL_SENSOR_H_
#define APP_CUSTOM_HALL_SENSOR_H_

// Variables

// Hall Sensor Pin (COMM PORT: SCK ADC1 pin (PA5)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_HALL_GPIO		GPIOA
#define CUSTOM_HALL_PIN			5
#define CUSTOM_HALL_ADC_INDEX	ADC_IND_EXT1

// Timer for PA6 (See datasheet for STM32F40xxx, Table 9. Alternate function mapping)
/*
#define HW_CUSTOM_HALL_TIM				TIM13
#define HW_CUSTOM_HALL_TIM_AF			GPIO_AF_TIM13
#define HW_CUSTOM_TIM_CLK_EN()          RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE)
#define HW_CUSTOM_HALL_EXTI_PORTSRC		EXTI_PortSourceGPIOA
#define HW_CUSTOM_HALL_EXTI_PINSRC		EXTI_PinSource5
#define HW_CUSTOM_HALL_EXTI_CH			EXTI9_5_IRQn
#define HW_CUSTOM_HALL_EXTI_LINE		EXTI_Line5
#define HW_CUSTOM_HALL_EXTI_ISR_VEC		//EXTI9_5_IRQHandler
#define HW_CUSTOM_HALL_TIM_ISR_CH		//TIM13_IRQn
#define HW_CUSTOM_HALL_TIM_ISR_VEC		//TIM13_IRQHandler
*/


// Define the voltage level (High level) of the output from sensor
#define SENSOR_VCC				5


// Functions
void app_custom_hall_init(void);
void app_custom_hall_deinit(void);
void app_custom_hall_reset(void);

// Only works if the pin is defined as DIGITAL (PULLUP)
bool app_custom_read_hall_state(void);
bool app_custom_get_sensor_state(void);
void app_custom_set_sensor_state(bool x);

// Only works if the pin is defined as ANALOG
/*
double app_custom_read_hall_ADC(void);
double app_custom_read_hall_voltage(bool is_5V);
double app_custom_get_sensor_adc_value(void);
double app_custom_get_sensor_adc_voltage(void);
void app_custom_set_sensor_adc_value(double x);
void app_custom_set_sensor_adc_voltage(double x);
*/

//void app_custom_hall_est_pos(void);


#endif /* APP_CUSTOM_HALL_SENSOR_H_ */
