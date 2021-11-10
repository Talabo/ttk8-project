/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        10.11.2021
 *
 * Hardware Specific: VESC 6 MkV (hw_60.c/-.h)
 *
 * This configuration is used for the custom application
 *
 */

#ifndef APP_CUSTOM_HW_H_
#define APP_CUSTOM_HW_H_


// Indicator Pin (COMM PORT: MISO ADC2 pin (PA6)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_INDICATOR_GPIO	GPIOA
#define CUSTOM_INDICATOR_PIN	6

// Hall Sensor Pin (COMM PORT: SCK ADC1 pin (PA5)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_HALL_GPIO		GPIOA
#define CUSTOM_HALL_PIN			5
#define CUSTOM_HALL_ADC_INDEX	ADC_IND_EXT1

// Only meant for if sensor pin is used as ANALOG
// Define the voltage level (High level) of the output from sensor
//#define SENSOR_VCC				3.3f


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



// Alternative, use new Hall Sensor Pin (COMM PORT: SDA NSS RX pin (PB11)) for HW: VESC 6 MkV (hw_60.c/.h)
// Pin (RX_SDA_NSS) PB11, AF: TIM2_CH4, Ext. interrupt: EXTI11

//which utilizes the EXTI11, hence: EXTI15_10_IRQHandler
#define HW_CUSTOM_HALL_EXTI_LINE		EXTI_Line11
#define HW_CUSTOM_HALL_EXTI_ISR_VEC     EXTI15_10_IRQHandler
#define HW_CUSTOM_HALL_TIM_ISR_CH		//TIM13_IRQn

*/

//EXTI15_10_IRQHandler



#endif /* APP_CUSTOM_HW_H_ */
