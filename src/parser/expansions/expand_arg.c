#include "minishell.h"

int is_all_dollars(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

void expand_dollar_question(char **arg, t_data *data)
{
	if (g_signal == 2)
	{
		data->exit_code = 130;
		g_signal = 0;
	}
	*arg = ft_itoa(data->exit_code);
}

void expand_env_variable(char **arg, t_data *data)
{
	// char *env_name = ft_strdup(*arg + 1);
	char *env_value;
	
	env_value = ft_getenv(ft_strdup(*arg + 1), data->envs);
	if (env_value != NULL)
		replace_for_expansion(arg, env_value);
	else
		(*arg)[0] = ft_strdup("")[0];
	free(env_value);
}

void expand_multiple_args(char **split, t_data *data)
{
	int j = 0;
	while (split[j])
	{
		if (ft_strcmp(split[j], "$?") == 0)
		{
			expand_dollar_question(&split[j], data);
			return;
		}
		else if (split[j][0] == '$')
			expand_env_variable(&split[j], data);
		j++;
	}
}

void expand_single_arg(char **arg, t_data *data)
{
	if (ft_strcmp(*arg, "$?") == 0)
		expand_dollar_question(arg, data);
	else if ((*arg)[0] == '$')
		expand_env_variable(arg, data);
}

void expand_arg(char **args, t_data *data)
{
	int i = 0;

	while (args[i])
	{
		if (!is_all_dollars(args[i]))
		{
			if (is_multi_words(args[i]))
			{
				char **split = ft_split(args[i], ' ');
				expand_multiple_args(split, data);
				char *tmp = arr2D_to_str(split);
				free(args[i]);
				args[i] = ft_strdup(tmp);
				free(tmp);
			}
			else
				expand_single_arg(&args[i], data);
		}
		i++;
	}
}

// void expand_arg(char **args, t_data *data)
// {

// 	int i = 0;

// 	if (is_all_dollars(args[0]))
// 		return;

// 	while (args[i])
// 	{
// 		if (is_multi_words(args[i]))
// 		{
// 			char **split = ft_split(args[i], ' ');
// 			int j = 0;
// 			while (split[j])
// 			{
// 				if (ft_strcmp(split[j], "$?") == 0)
// 				{
// 					if (g_signal == 2)
// 					{
// 						data->exit_code = 130;
// 						g_signal = 0;
// 					}
// 					split[j] = ft_itoa(data->exit_code); /// Check this later for proper allocation
// 					return;
// 				}
// 				else if (split[j][0] == '$')
// 				{
// 					char *env_name = ft_strdup(split[j] + 1);
// 					if (ft_getenv(env_name, data->envs) != NULL)
// 						replace_for_expansion(&split[j], ft_getenv(env_name, data->envs));
// 					else
// 						split[j][0] = '\0';
// 					free(env_name);
// 				}
// 				j++;
// 			}
// 			char *tmp = arr2D_to_str(split);
// 			free(args[i]);
// 			args[i] = ft_strdup(tmp);
// 			free(tmp);
// 		}
// 		else
// 		{
// 			if (ft_strcmp(args[i], "$?") == 0)
// 			{
// 				if (g_signal == 2)
// 				{
// 					data->exit_code = 130;
// 					g_signal = 0;
// 				}
// 				args[i] = ft_itoa(data->exit_code);
// 				return;
// 			}
// 			else if (args[i][0] == '$')
// 			{
// 				char *env_name = ft_strdup(args[i] + 1);
// 				if (ft_getenv(env_name, data->envs) != NULL)
// 					replace_for_expansion(&args[i], ft_getenv(args[i] + 1, data->envs));
// 				else
// 					args[i][0] = '\0';// We need to find another way for this. non valid expansios should not print anything
// 				free(env_name);
// 			}
// 		}
// 		i++;
// 	}
// }