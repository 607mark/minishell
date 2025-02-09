/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:32:01 by amaula            #+#    #+#             */
/*   Updated: 2024/12/03 20:20:47 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns:
 * 	- NULL if PATH is unset and command was just "cd"
 * 	- HOME if PATH is set and command was just "cd"
 * 	- "minishell", f.e. if "cd minishell"*/
static char	*get_cd_path(char *arg, t_env *env)
{
	char	*path;

	if (arg == NULL || *arg == '\0')
		path = ft_getenv("HOME", env);
	else
		path = ft_strdup(arg);
	return (path);
}

static int	changedir(char *path)
{
	if (chdir(path) != 0)
	{
		perror(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (len(args) > 2)
	{
		print_error("-minishell: cd: too many args", 2);
		return (1);
	}
	path = get_cd_path(args[1], env);
	if (path == NULL)
	{
		print_error("-minishell: cd: could not get path", 2);
		return (1);
	}
	return (changedir(path));
}
