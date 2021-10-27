/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Modified by:         Emil Jenssen
 * Created:             16.10.2021
 * Last updated:        27.10.2021
 *
 */


#include "app_custom_analysis.h"

static float custom_samp = 0.0;

/*
static char x_axis_name[] = "Sample"; // Default name: Sample
static char y_axis_name[] = "Value"; // Default name: Value
static char graph_names[MAX_GRAPH_VALUES][MAX_GRAPH_NAME_LENGTH] = {
								"Value 1",
								"value 2",
								"value 3",
								"value 4",
								"value 5",
								"value 6",
								"value 7"
							  };

// Sets a name to the given graph value
void app_custom_set_graph_name(int graph, char name){
	graph_names[graph] = name;
}

void app_custom_set_x_axis_name(char name){
	x_axis_name = name;
}

void app_custom_set_y_axis_name(char name){
	y_axis_name = name;
}
*/

// Initiate the custom experiment plots
void custom_experiment_plots_init(void){
	// Exit function
	//if (!custom_get_custom_plot()) return;

	commands_init_plot("Sample", "ADC Value");
	commands_plot_add_graph("Hall raw"); // graph 1
	commands_plot_add_graph("Hall 3.3v logic"); // graph 2
	//commands_plot_add_graph("PID set point"); // graph 3
	//commands_plot_add_graph("PID error"); // graph 4
	//commands_plot_add_graph("PID position mapped"); // graph 5
	//commands_plot_add_graph("PID set point mapped"); // graph 6
	custom_samp = 0.0;
}

// Samples the custom experiment plots
void custom_experiment_plots(void){
	// Exit function
	//if (!custom_get_custom_plot()) return;

	// graph 1 (Hall sensor Raw value)
	commands_plot_set_graph(0);
	commands_send_plot_points(custom_samp, app_custom_get_sensor_val());

	// graph 2 ((Hall sensor, 5V logic)
	commands_plot_set_graph(1);
	commands_send_plot_points(custom_samp, app_custom_get_sensor_val_voltage());

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
