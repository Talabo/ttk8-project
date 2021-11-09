/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        09.11.2021
 *
 */

#ifndef APP_CUSTOM_INDICATOR_H_
#define APP_CUSTOM_INDICATOR_H_

// Variables

// Indicator Pin (COMM PORT: MISO ADC2 pin (PA6)) for HW: VESC 6 MkV (hw_60.c/.h)
#define CUSTOM_INDICATOR_GPIO	GPIOA
#define CUSTOM_INDICATOR_PIN	6

#define CUSTOM_INDICATOR_ON()  palSetPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);
#define CUSTOM_INDICATOR_OFF() palClearPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);

// Functions
void app_custom_indicator_init(void);
void app_custom_indicator_deinit(void);
void app_custom_indicator_reset(void);



#endif /* APP_CUSTOM_INDICATOR_H_ */
