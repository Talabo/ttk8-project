/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        11.11.2021
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
#define CUSTOM_PA6_DEFAULT      PAL_MODE_INPUT_ANALOG  // Default type from original firmware

// Indicator2 Pin (COMM PORT: SCL MOSI pin (PA7)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_INDICATOR2_GPIO	GPIOA
#define CUSTOM_INDICATOR2_PIN	7
#define CUSTOM_PA7_DEFAULT      PAL_MODE_INPUT_ANALOG  // Default type from original firmware


// Hall Sensor Pin (COMM PORT: SCK ADC1 pin (PA5)) for HW: VESC 6 MkV (hw_60.c/.h)
//#define CUSTOM_HALL_GPIO		GPIOA
//#define CUSTOM_HALL_PIN	    5
//#define CUSTOM_PA5_DEFAULT    PAL_MODE_INPUT_ANALOG  // Default type from original firmware


// Hall Sensor Pin (COMM PORT: SDA NSS RX pin (PB11)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_HALL_GPIO		GPIOB
#define CUSTOM_HALL_PIN			11
#define CUSTOM_PA11_DEFAULT     PAL_MODE_INPUT // Default type from original firmware

// External interrupt (EXTI) for PB11
#define HW_CUSTOM_HALL_EXTI_PORTSRC		EXTI_PortSourceGPIOB
#define HW_CUSTOM_HALL_EXTI_PINSRC		EXTI_PinSource11
#define HW_CUSTOM_HALL_EXTI_CH			EXTI15_10_IRQn
#define HW_CUSTOM_HALL_EXTI_LINE		EXTI_Line11
#define HW_CUSTOM_HALL_EXTI_ISR_VEC		EXTI15_10_IRQHandler // See isr_vector_table.h


#endif /* APP_CUSTOM_HW_H_ */
