
#include "minishell.h"

int parse(char *input, t_data *data)
{
    char *line_copy;
    char **future_children;
    int nch;

    line_copy = ft_strdup(input);
    if (sub_quotes(line_copy, data))
        return (1);

    char *expanded_line = expand_line(line_copy, data);

    if (cnt_missing_space(expanded_line) > 0)
    {
        free(expanded_line);
        expanded_line = add_space_to_redirect(input);
    }

    future_children = ft_split(expanded_line, '|');
    free(line_copy);
    free(expanded_line);

    t_cmd *new_node = NULL;
    nch = 0;
    while (future_children[nch])
    {
        new_node = malloc(sizeof(t_cmd));
        new_node->args = ft_split(future_children[nch], ' ');
        new_node->num_args = cnt_args(new_node->args);
        new_node->pipe_in = -1;
        new_node->pipe_out = -1;
        new_node->redirect_in = -1;
        new_node->redirect_out = -1;
        new_node->here_doc = 0;
        new_node->next = NULL;

        if (heredoc_preprocess(new_node))
        {
            data->exit_code = 2;
            return (1);
        }

        return_dub_quotes(new_node->args, data);

        expand_arg(new_node->args, data);
        
        return_sin_quotes(new_node->args, data);

        int j = 0;
        j = redirect_assign(new_node, data);
        if (j != 0)
        {
            data->exit_code = j;
            return (1);
        }

        if (new_node->num_args == 0)
        {
            data->exit_code = 1;
            return (1);
        }

        new_node->args = realloc(new_node->args, sizeof(char *) * (new_node->num_args + 1));
        new_node->args[new_node->num_args] = NULL;

        if (nch++ == 0)
            data->commands = new_node;
        else
        {
            t_cmd *current = data->commands;
            while (current->next)
                current = current->next;
            current->next = new_node;
        }
    }
    data->num_of_children = nch;
    pipe_assign(data->commands);
    free_arr2D(future_children);
    // print_2D(data->commands->args);
    return (0);
}