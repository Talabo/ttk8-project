/*
 * Custom firmware
 *
 * Created by:          Emil Jenssen
 * Last updated:        03.11.2021
 *
 */

#ifndef APP_CUSTOM_PLOTTER_H_
#define APP_CUSTOM_PLOTTER_H_

#define MAX_GRAPH_NAME_LENGTH 15
#define MAX_GRAPH_VALUES      7

// Functions
/*
void app_custom_set_graph_name(int graph, char name);
void app_custom_set_x_axis_name(char name);
void app_custom_set_y_axis_name(char name);
*/

void custom_experiment_plots_init(void);
void custom_experiment_plots(void);


#endif /* APP_CUSTOM_PLOTTER_H_ */
