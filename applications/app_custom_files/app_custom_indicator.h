/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             21.10.2021
 * Last updated:        21.10.2021
 *
 */

#ifndef APP_CUSTOM_INDICATOR_H_
#define APP_CUSTOM_INDICATOR_H_

// Variables

// Indicator Pin (COMM PORT: SCK ADC1 pin (PA5)) for HW: VESC 6 MkV
#define CUSTOM_INDICATOR_GPIO	GPIOA
#define CUSTOM_INDICATOR_PIN	5

#define CUSTOM_INDICATOR_ON()  palSetPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);
#define CUSTOM_INDICATOR_OFF() palClearPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);

// Functions
void app_custom_indicator_init(void);
void app_custom_indicator_deinit(void);
void app_custom_indicator_reset(void);



#endif /* APP_CUSTOM_INDICATOR_H_ */
