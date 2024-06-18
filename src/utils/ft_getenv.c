/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:40:24 by darotche          #+#    #+#             */
/*   Updated: 2024/06/18 19:07:31 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *env_name, char **envs)
{
	int		i;
	char	*env_value;
	char	*val;

	val = NULL;
	i = 0;
	// printf("env_name: %s\n", env_name);
	while (envs[i])
	{
		if (ft_strncmp(envs[i], env_name, ft_strlen(env_name)) == 0 && envs[i][ft_strlen(env_name)] == '=')
		{
			free (val);
			val = ft_strdup(envs[i] + ft_strlen(env_name) + 1);
			env_value = val;
			//printf(GRN "Valid env: %s\n" RESET, env_value);
			return (env_value);
		}
		i++;
	}
	free (val);
	return (NULL);
}


// char *ft_getenv(char *env_name, char **envs)
// {
// 	int i;
// 	char *env_value;

// 	i = 0;
// 	// printf("env_name: %s\n", env_name);
// 	while (envs[i])
// 	{
// 		if (ft_strncmp(envs[i], env_name, ft_strlen(env_name)) == 0 && envs[i][ft_strlen(env_name)] == '=')
// 		{
// 			env_value = ft_strdup(envs[i] + ft_strlen(env_name) + 1);
// 			//printf(GRN "Valid env: %s\n" RESET, env_value);
// 			return (env_value);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_env_name(char *s, char c)
{
	int		i;
	int		len;
	char	*name;

	len = 0;
	i = 0;
	while(s[len] != '=' && s[len] != '\0')
		len++;
	name = malloc(sizeof(char) * len + 1);
	while (s[i] != c && s[i] != '\0')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}