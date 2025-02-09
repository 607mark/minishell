/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:45 by amaula            #+#    #+#             */
/*   Updated: 2024/12/12 15:07:21 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_run_norm(t_main *main_struct, t_run *run)
{
	run->cmd_curr = main_struct->cmd_list;
	run->cmd_list = main_struct->cmd_list;
	run->len = list_len(run->cmd_list);
	run->env = main_struct->env;
	run->pids = malloc(run->len * sizeof(pid_t));
	run->pipefds = allocate_pipefds(run->len);
}

/* memset pids to -2 explanation:
 * 	in case of builtin, it stays at -2,
 * 	then waitpids will not wait for it,
 * 	because builtins are run in parent process */
int	init_run(t_main *main_struct, t_run **result)
{
	t_run	*run;

	run = 0;
	if (setup_signals(FORK_SIG))
		return (1);
	if (!*main_struct->cmd_list->args[0])
		return (1);
	run = malloc(sizeof(t_run));
	if (run == NULL)
		return (1);
	init_run_norm(main_struct, run);
	if (run->pids == NULL || run->pipefds == NULL
		|| create_pipes(run->pipefds, run->len) == 0)
	{
		free(run->pids);
		free_pipefds(run->pipefds, run->len);
		free(run);
		return (1);
	}
	ft_memset(run->pids, -2, run->len * sizeof(pid_t));
	run->i = 0;
	run->builtin = 0;
	*result = run;
	return (0);
}

/* If its a builtin, runs it and sets exit_code
 * Return values:
 *	0: its not a builtin
 *	1: cd
 *	2: export
 *	3: unset
 *	4: exit, will return 0 from run()
 */
int	run_builtin(t_command *cmd, t_env *env)
{
	char	*builtins[4];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "export";
	builtins[2] = "unset";
	builtins[3] = "exit";
	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
		{
			if (ft_strcmp("cd", cmd->args[0]) == 0)
				env->exit_code = ft_cd(cmd->args, env);
			else if (ft_strcmp("export", cmd->args[0]) == 0)
				env->exit_code = ft_export(cmd->args + 1, env);
			else if (ft_strcmp("unset", cmd->args[0]) == 0)
				env->exit_code = ft_unset(cmd->args + 1, env);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

static int	finish_run(t_run *run, t_main *main_struct)
{
	if (run)
	{
		close_pipes(run->pipefds, run->len);
		wait_pids(run);
		free(run);
	}
	free_list(main_struct->cmd_list);
	return (1);
}

int	run(t_main *main_s)
{
	t_run	*run;
	int		ret;

	ret = 1;
	if (main_s->cmd_list->args[0] == 0 || main_s->cmd_list->args[0][0] == 0)
		return (free_list(main_s->cmd_list));
	if (init_run(main_s, &run) && finish_run(run, main_s))
		return (0);
	while (run->cmd_curr && ret != 0)
	{
		run->builtin = get_builtin_type(run);
		if (run->builtin && run->len == 1)
			run_builtin(run->cmd_curr, run->env);
		if (run->builtin == 0)
		{
			if (do_fork(run) == -1)
				return (0);
			run->i++;
		}
		run->cmd_curr = run->cmd_curr->next;
	}
	finish_run(run, main_s);
	return (ret);
}
