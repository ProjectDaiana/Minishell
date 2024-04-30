#include "minishell.h"

void free_arr2D(char **arr2D)
{
    int i;

    i = 0;
    while (arr2D[i] != NULL && arr2D[i][0] != '\n')
        free(arr2D[i++]);
    free(arr2D);
}

void free_data(t_data *data, char *input)
{
    t_cmd *current;
    t_cmd *next;

    current = data->commands;
    while (current != NULL)
    {
        next = current->next;
        free_arr2D(current->args);
        free(current);
        current = next;
    }
    free(input);
    free(data);
	// while (commands)
	// {
	// 	tmp = commands;
	// 	commands = commands->next;
	// 	free_command(tmp);
	// }	
}

// void free_command(t_cmd *command)
// {
//     free_arr2D(command->args);
//     free(command);
// }

// void free_commands(t_cmd *commands)
// {
//     t_cmd *tmp;

// 	while (commands)
// 	{
// 		tmp = commands;
// 		commands = commands->next;
// 		free_command(tmp);
// 	}	
// }