/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        10.11.2021
 *
 */


#include "app_custom_analysis.h"



// Register custom commands for callbacks
void app_custom_register_commands(void){

	terminal_register_command_callback(
			"custom_analysis_timer_off",
			"Set the analysis timer OFF",
			0,
			terminal_custom_analysis_timer_off);

	terminal_register_command_callback(
			"custom_analysis_timer_on",
			"Set the analysis timer ON and resets the timer",
			0,
			terminal_custom_analysis_timer_on);

	// Priority
	terminal_register_command_callback(
			"custom_get_thread_priority",
			"Get the thread priority for the custom analysis thread.",
			0,
			terminal_custom_get_thread_prority);

	// Priority NORMALPRIO
	terminal_register_command_callback(
			"custom_set_NORMALPRIO",
			"Set the thread priority for the custom analysis thread to NORMALPRIO",
			0,
			terminal_custom_set_NORMALPRIO);

	// Priority LOWPRIO
	terminal_register_command_callback(
			"custom_set_LOWPRIO",
			"Set the thread priority for the custom analysis thread to LOWPRIO",
			0,
			terminal_custom_set_LOWPRIO);

	// Priority HIGHPRIO
	terminal_register_command_callback(
			"custom_set_HIGHPRIO",
			"Set the thread priority for the custom analysis thread to HIGHPRIO",
			0,
			terminal_custom_set_HIGHPRIO);

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
	terminal_unregister_callback(terminal_custom_set_NORMALPRIO);
	terminal_unregister_callback(terminal_custom_set_LOWPRIO);
	terminal_unregister_callback(terminal_custom_set_HIGHPRIO);
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
	app_custom_reset_analysis_timer();
	commands_printf("The analysis time taker is ON");
}

// Gets the thread priority of the analysis thread
void terminal_custom_get_thread_prority(int argc, const char **argv){
	(void)argc;
	(void)argv;

	tprio_t priority = app_custom_get_thread_priority();

	if(priority == NORMALPRIO){
		commands_printf("The thread priority is NORMALPRIO");
	}else if(priority == LOWPRIO){
		commands_printf("The thread priority is LOWPRIO");
	}else if(priority == HIGHPRIO){
		commands_printf("The thread priority is HIGHPRIO");
	}else{
		commands_printf("The thread priority is (unknown type)");
	}
}

// Sets the thread priority to NORMALPRIO
void terminal_custom_set_NORMALPRIO(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_custom_set_thread_priority(NORMALPRIO);
	commands_printf("The thread priority is set to NORMALPRIO");
}

// Sets the thread priority to LOWPRIO
void terminal_custom_set_LOWPRIO(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_custom_set_thread_priority(LOWPRIO);
	commands_printf("The thread priority is set to LOWPRIO");
}


// Sets the thread priority to HIGHPRIO
void terminal_custom_set_HIGHPRIO(int argc, const char **argv){
	(void)argc;
	(void)argv;
	app_custom_set_thread_priority(HIGHPRIO);
	commands_printf("The thread priority is set to HIGHPRIO");
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

