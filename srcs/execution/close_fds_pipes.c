/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:30:47 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:30:48 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_extra_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_unused_fds(t_mini *shell, int i)
{
	int	j;

	j = i + 1;
	if (shell->cmd_count >= 2 && i < shell->cmd_count - 1)
		close(shell->pipes[i][0]);
	while (j < shell->cmd_count - 1)
	{
		if (shell->pipes[j])
		{
			close(shell->pipes[j][0]);
			close(shell->pipes[j][1]);
		}
		j++;
	}
}

void	close_all_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	close_fds_and_pipes(t_mini *shell, int i)
{
	if (shell->cmd_count > 1)
	{
		if (i == 0)
			close(shell->pipes[i][1]);
		else if (i < shell->cmd_count - 1)
		{
			close(shell->pipes[i - 1][0]);
			close(shell->pipes[i][1]);
		}
		else if (i == shell->cmd_count - 1)
			close(shell->pipes[i - 1][0]);
	}
}
