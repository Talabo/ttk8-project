/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        11.11.2021
 *
 */

#ifndef APP_CUSTOM_INDICATOR_H_
#define APP_CUSTOM_INDICATOR_H_

// Functions

#define CUSTOM_INDICATOR_ON()  palSetPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);
#define CUSTOM_INDICATOR_OFF() palClearPad(CUSTOM_INDICATOR_GPIO, CUSTOM_INDICATOR_PIN);

#define CUSTOM_INDICATOR2_ON()  palSetPad(CUSTOM_INDICATOR2_GPIO, CUSTOM_INDICATOR2_PIN);
#define CUSTOM_INDICATOR2_OFF() palClearPad(CUSTOM_INDICATOR2_GPIO, CUSTOM_INDICATOR2_PIN);


void app_custom_indicator_init(void);
void app_custom_indicator_deinit(void);
void app_custom_indicator_reset(void);



#endif /* APP_CUSTOM_INDICATOR_H_ */
