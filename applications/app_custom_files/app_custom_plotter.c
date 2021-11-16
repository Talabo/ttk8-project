/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        16.11.2021
 *
 */

#include "app_custom_analysis.h"


static float custom_samp = 0.0;

// Initiate the custom experiment plots
void custom_experiment_plots_init(void){
	commands_init_plot("Sample", "I/O state");
	commands_plot_add_graph("Hall sensor state"); // graph 1
	//commands_plot_add_graph("Hall 3.3v logic"); // graph 2
	//commands_plot_add_graph("PID set point"); // graph 3
	//commands_plot_add_graph("PID error"); // graph 4
	//commands_plot_add_graph("PID position mapped"); // graph 5
	//commands_plot_add_graph("PID set point mapped"); // graph 6
	custom_samp = 0.0;
}

// Samples the custom experiment plots
void custom_experiment_plots(void){

	// graph 1 (Hall sensor Raw value)
	commands_plot_set_graph(0);
	commands_send_plot_points(custom_samp, app_custom_get_sensor_state());

	// graph 2 ((Hall sensor, 5V logic)
	//commands_plot_set_graph(1);
	//commands_send_plot_points(custom_samp, VALUE);

	// graph 3 (PID position set point)
	//commands_plot_set_graph(2);
	//commands_send_plot_points(custom_samp, VALUE);

	// graph 4
	//commands_plot_set_graph(3);
	//commands_send_plot_points(custom_samp, VALUE);

	// graph 5
	//commands_plot_set_graph(4);
	//commands_send_plot_points(custom_samp, VALUE);

	// graph 6
	//commands_plot_set_graph(5);
	//commands_send_plot_points(custom_samp, VALUE);

	custom_samp++;
}
