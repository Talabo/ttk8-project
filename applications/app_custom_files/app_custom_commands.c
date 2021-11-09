/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        09.11.2021
 *
 */


#include "app_custom_analysis.h"



// Register custom commands for callbacks
void app_custom_register_commands(void){
	// Thread Priority
	terminal_register_command_callback(
			"analysis_timer_off",
			"Set the analysis timer OFF",
			0,
			terminal_custom_analysis_timer_off);

	terminal_register_command_callback(
			"analysis_timer_on",
			"Set the analysis timer ON",
			0,
			terminal_custom_analysis_timer_on);

	terminal_register_command_callback(
			"custom_get_thread_priority",
			"Get the thread priority for the custom analysis thread.",
			0,
			terminal_custom_get_thread_prority);

	terminal_register_command_callback(
			"custom_set_thread_priority",
			"Set the thread priority for the custom analysis thread. Default: NORMALPRIO (128)",
			"[0-255]",
			terminal_custom_set_thread_prority);

	// Updates thread settings by restarting all apps
	terminal_register_command_callback(
			"custom_update_thread_settings",
			"Updates the thread settings by restarting all threads.",
			0,
			terminal_custom_update_thread_settings);
}

// Unregister custom commands for callbacks
void app_custom_unregister_commands(void){
	terminal_unregister_callback(terminal_custom_analysis_timer_off);
	terminal_unregister_callback(terminal_custom_analysis_timer_on);
	terminal_unregister_callback(terminal_custom_get_thread_prority);
	terminal_unregister_callback(terminal_custom_set_thread_prority);
	terminal_unregister_callback(terminal_custom_update_thread_settings);
}


// Callback functions for the terminal command with arguments.


// Gets the thread priority of the analysis thread
void terminal_custom_analysis_timer_off(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_custom_set_analysis_time_taker(false);
	commands_printf("The analysis time taker is OFF");

}

// Gets the thread priority of the analysis thread
void terminal_custom_analysis_timer_on(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_custom_set_analysis_time_taker(true);
	commands_printf("The analysis time taker is ON");
}

// Gets the thread priority of the analysis thread
void terminal_custom_get_thread_prority(int argc, const char **argv){
	(void)argc;
	(void)argv;
	commands_printf("The thread priority is: %d ", app_custom_get_thread_priority());
}

// Sets the thread priority of the analysis thread
void terminal_custom_set_thread_prority(int argc, const char **argv){
	if(argc == 2) {
		int d = -1;
		sscanf(argv[1], "%d", &d);
		commands_printf("You have entered %d", d);

		if(d < 0 || d > 255) {
			commands_printf("Invalid range. Range is [0, 255]");
			return;
		}

		app_custom_set_thread_priority(d);
		commands_printf("The thread priority is set to %d", d);

	}else{
		commands_printf("This command requires one argument.\n");
	}
}

// Updates the thread settings to the thread, by calling app_set_configuration()
// app_set_configuration() stops all app threads, starts them and configures them.
void terminal_custom_update_thread_settings(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_configuration *appconf = mempools_alloc_appconf();
	conf_general_read_app_configuration(appconf);
	app_set_configuration(appconf);
}

