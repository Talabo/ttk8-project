/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             21.10.2021
 * Last updated:        21.10.2021
 *
 */

#ifndef APP_CUSTOM_HALL_SENSOR_H_
#define APP_CUSTOM_HALL_SENSOR_H_

// Variables

// Hall Sensor Pin (COMM PORT: MISO ADC2 pin (PA6))
// For more info for hardware VESC 6 MkV, see hw_60.c/.h
#define CUSTOM_HALL_GPIO		GPIOA
#define CUSTOM_HALL_PIN			6
#define CUSTOM_HALL_ADC_INDEX	ADC_IND_EXT2

// Timer for PA6 (See datasheet for STM32F40xxx, Table 9. Alternate function mapping)
#define HW_CUSTOM_HALL_TIM				TIM13
#define HW_CUSTOM_HALL_TIM_AF			GPIO_AF_TIM13

// TODO
#define HW_CUSTOM_HALL_TIM_CLK_EN()		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)
#define HW_CUSTOM_HALL_EXTI_PORTSRC		//EXTI_PortSourceGPIOC
#define HW_CUSTOM_HALL_EXTI_PINSRC		//EXTI_PinSource8
#define HW_CUSTOM_HALL_EXTI_CH			//EXTI9_5_IRQn
#define HW_CUSTOM_HALL_EXTI_LINE		//EXTI_Line8
#define HW_CUSTOM_HALL_EXTI_ISR_VEC		//EXTI9_5_IRQHandler
#define HW_CUSTOM_HALL_TIM_ISR_CH		//TIM3_IRQn
#define HW_CUSTOM_HALL_TIM_ISR_VEC		//TIM3_IRQHandler



// Define the voltage level (High level) of the output from sensor
#define SENSOR_VCC				5


// Functions
void app_custom_hall_init(void);
void app_custom_hall_deinit(void);
void app_custom_hall_reset(void);
double app_custom_read_hall(void);
double app_custom_read_hall_voltage(bool is_5V);

double app_custom_get_sensor_val(void);
double app_custom_get_sensor_val_voltage(void);
void app_custom_set_sensor_val(double x);
void app_custom_set_sensor_val_voltage(double x);

//void app_custom_hall_est_pos(void);


#endif /* APP_CUSTOM_HALL_SENSOR_H_ */
