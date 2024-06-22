/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:46 by darotche          #+#    #+#             */
/*   Updated: 2024/06/22 23:51:23 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int varname_len(char *var)
{
    int i;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    return (i);
}

// int var_cmp(char **envar, char *newvar)
// {
//     int i = 0;
//     while (envar[i])
//     {
//         if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
//             return (1);
//         i++;
//     }
//     return (0);
// }

int replace_var(char **envar, char *newvar)
{
    int i;

    i = 0;
    while (envar[i])
    {
        if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
        {
            free(envar[i]);
            envar[i] = ft_strdup(newvar);
            return (1);
        }
        i++;
    }
    return (0);
}

int add_var(char ***envar, char *newvar)
{
    char **tmp;
    int i;

    tmp = malloc(sizeof(char *) * (count_env(*envar) + 2));
    i = 0;
    while ((*envar)[i])
    {
        tmp[i] = ft_strdup((*envar)[i]);
        i++;
    }
    tmp[count_env(*envar)] = ft_strdup(newvar);
    tmp[count_env(*envar) + 1] = NULL;
    free_arr2D(*envar);
    *envar = tmp;
//	print_2D(*envar);
    return (0);
}

void ft_export(t_data *data, t_cmd *cmd, int i)
{
	char *env_name;
	//printf(RED"cmd->args[i]: %s\n"RESET, cmd->args[i]);
	//printf(RED"cmd->num_args: %d\n"RESET, cmd->num_args);
	i++;
    if (cmd->num_args > 1)
    {	//printf(RED"cmd->args[i]: %s\n"RESET, cmd->args[i]);
		while (cmd->args[i] != NULL)
		{
			env_name = get_env_name(cmd->args[i], '=');
		//	printf(RED"env_name: %s\n"RESET, env_name);
		//	printf(RED"cmd->args[i]: %s\n"RESET, cmd->args[i]);
			if (!(ft_strchr(cmd->args[i], '=')) && ft_isallalpha(cmd->args[i]))
			{
				//printf(RED"cmd->args[i]: %s\n"RESET, cmd->args[i]);
			//	data->exit_code = 1;
				i++;
				return;
			}
			else if (cmd->args[i][0] == '=' || !ft_isall_alnum(env_name) || ft_isall_digit(env_name) || ft_strchr(cmd->args[i], '=') == NULL)
			{
				write_error("minishell: export: ");
				write_error(cmd->args[i]);
				write_error(": not a valid identifier\n");
				data->exit_code = 1;
				free(env_name);
				return;
			}
			if (ft_strchr(cmd->args[i], '=') == NULL)
			{
				data->exit_code = 1;
				i++;
			}
			free(env_name);
			if (!replace_var(data->envs, cmd->args[i]))
			{
				//printf(GRN "Add variable %s\n" RESET, cmd->args[i]);
				add_var(&data->envs, cmd->args[i]);
			}
			i++;
		}
    }
    data->exit_code = 0;
}


// void ft_export(t_data *data, t_cmd *cmd, int i)
// {
// 	char *env_name;
// 	i++;
//     if (cmd->num_args > 1)
//     {
//         env_name = get_env_name(cmd->args[i], '=');
//         if (cmd->args[i][0] == '=' || !ft_isall_alnum(env_name) || ft_isall_digit(env_name))
//         {
//             write_error("minishell: export: ");
//             write_error("not a valid env_name\n");
//             data->exit_code = 1;
//             free(env_name);
//             return;
//         }
//         free(env_name);
//         if (ft_strchr(cmd->args[i], '=') == NULL)
//         {
//             data->exit_code = 1;
//             i++;
//         }
//     }
//     while (cmd->args[i] != NULL)
//     {
//         if (!replace_var(data->envs, cmd->args[i]))
//         {
//             // printf(GRN "Add variable\n" RESET);
//             add_var(&data->envs, cmd->args[i]);
//         }
//         i++;
//     }
//     data->exit_code = 0;
// }
