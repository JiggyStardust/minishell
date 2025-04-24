/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:24:09 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:24:20 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (pipe(shell->pipes[i]) == -1)
		{
			perror("minishell: pipe failed");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	allocate_pipes(t_mini *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipes)
		return (FALSE);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int));
		if (!shell->pipes[i])
		{
			free_pipes(shell, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	allocate_pids(t_mini *shell)
{
	shell->pids = ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	init_pipeline(t_mini *shell)
{
	if (!allocate_pids(shell))
		return (FALSE);
	if (shell->cmd_count > 1)
	{
		if (!allocate_pipes(shell))
			return (FALSE);
		if (!create_pipes(shell))
			return (FALSE);
	}
	return (TRUE);
}
