/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:41:01 by darotche          #+#    #+#             */
/*   Updated: 2024/06/26 19:11:14 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_data *data, char *arg)
{
	int		i;
	char	*env_name;

	i = 0;
	while (data->envs[i] != NULL)
	{
		env_name = get_env_name(data->envs[i], '=');
		if (ft_strcmp(env_name, arg) == 0)
		{
			free(data->envs[i++]);
			while (data->envs[i] != NULL)
			{
				data->envs[i - 1] = data->envs[i];
				i++;
			}
			data->envs[i - 1] = NULL;
			free(env_name);
			return ;
		}
		i++;
		free(env_name);
	}
}

void	ft_unset(t_data *data, t_cmd *cmd, int i)
{
	i++;
	while (cmd->args[i] != NULL)
	{
		remove_env(data, cmd->args[i]);
		i++;
	}
	data->exit_code = 0;
}
