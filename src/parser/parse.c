
#include "minishell.h"

int parse(char *input, t_data *data)
{
	char **future_children;
	t_cmd *new_node;
	int nch;
	char *expanded_line;

	expanded_line = refine_input(input, data);
	if (!expanded_line)
		return (1);
		
	future_children = ft_split(expanded_line, '|');
	free(expanded_line);
	new_node = NULL;
	nch = 0;
	while (future_children[nch])
	{
		new_node = create_cmd_node(future_children[nch]);
		if (heredoc_preprocess(new_node, data))
			return (1);
		return_dub_quotes(new_node->args, data);
		expand_arg(new_node->args, data);
		return_sin_quotes(new_node->args, data);
		if (handle_redirects(new_node, data, future_children))
			return (1);
		args_realloc(new_node);
		add_cmd_to_list(&(data->commands), new_node);
		nch++;
	}
	data->num_of_children = nch;
	pipe_assign(data->commands);
	free_arr2D(future_children);
	//print_cmd_nodes(data);
	return (0);
}
