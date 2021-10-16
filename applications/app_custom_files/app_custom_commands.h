/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             16.10.2021
 * Last updated:        16.10.2021
 *
 */

#ifndef APP_CUSTOM_COMMANDS_H_
#define APP_CUSTOM_COMMANDS_H_

// Functions

void app_custom_register_commands(void);
void app_custom_unregister_commands(void);

void terminal_custom_set_thread_prority(int argc, const char **argv);
void terminal_custom_get_thread_prority(int argc, const char **argv);
void terminal_custom_update_thread_settings(int argc, const char **argv);

#endif /* APP_CUSTOM_COMMANDS_H_ */
