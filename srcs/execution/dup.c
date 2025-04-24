/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:22:32 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:22:58 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	configure_fds(t_mini *shell, t_cmd *cmd)
{
	if (!handle_redirection(shell, cmd))
		return (FALSE);
	if (cmd->input_fd == -1)
		cmd->input_fd = STDIN_FILENO;
	if (cmd->output_fd == -1)
		cmd->output_fd = STDOUT_FILENO;
	return (TRUE);
}

int	configure_fds_child(t_mini *shell, t_cmd *cmd)
{
	if (!handle_redirection_child(shell, cmd))
		return (FALSE);
	if (cmd->input_fd == -1)
		cmd->input_fd = STDIN_FILENO;
	if (cmd->output_fd == -1)
		cmd->output_fd = STDOUT_FILENO;
	return (TRUE);
}

int	dup_input(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (!dup2_close(cmd->input_fd, STDIN_FILENO))
		{
			perror("dup2 failed for input redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i > 0)
			close(shell->pipes[i - 1][0]);
	}
	else if (i > 0)
	{
		if (!dup2_close(shell->pipes[i - 1][0], STDIN_FILENO))
		{
			perror("dup2 failed for pipe input");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

int	dup_output(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (!dup2_close(cmd->output_fd, STDOUT_FILENO))
		{
			perror("dup2 failed for output redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i < shell->cmd_count - 1)
			close(shell->pipes[i][1]);
	}
	else if (i < shell->cmd_count - 1)
	{
		if (!dup2_close(shell->pipes[i][1], STDOUT_FILENO))
		{
			perror("dup2 failed for pipe output");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

int	dup2_close(int old_fd, int new_fd)
{
	if (old_fd < 0)
	{
		ft_putstr_fd("minishell: invalid file descriptor\n", 2);
		return (FALSE);
	}
	if (dup2(old_fd, new_fd) == -1)
	{
		close(old_fd);
		return (FALSE);
	}
	close(old_fd);
	return (TRUE);
}
