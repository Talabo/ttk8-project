/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        11.11.2021
 *
 */

#ifndef APP_CUSTOM_HALL_SENSOR_H_
#define APP_CUSTOM_HALL_SENSOR_H_

// Microcontroller spesific
#include "stm32f4xx_conf.h" // For STM32F4xx, HW: VESC 6 MkV
// Interrupt spesific
#include "isr_vector_table.h" // For interrupt service routine


// Functions
void app_custom_hall_init(void);
void app_custom_hall_deinit(void);
void app_custom_hall_reset(void);

bool app_custom_read_hall_state(void);
bool app_custom_get_sensor_state(void);
void app_custom_set_sensor_state(bool x);

#endif /* APP_CUSTOM_HALL_SENSOR_H_ */
