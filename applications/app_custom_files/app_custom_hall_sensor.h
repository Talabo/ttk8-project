/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        10.11.2021
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
