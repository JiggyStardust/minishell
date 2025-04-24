/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:24:00 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:24:05 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_parent(t_mini *shell, t_cmd *cmd, int is_builtin)
{
	if (!configure_fds(shell, cmd) || !save_std(shell, cmd))
	{
		clean_commands(cmd);
		return (FALSE);
	}
	if (!redirect_fd(cmd->input_fd, STDIN_FILENO)
		|| !redirect_fd(cmd->output_fd, STDOUT_FILENO))
		return (FALSE);
	if (handle_builtin(is_builtin, shell, cmd, cmd->cmds) > 0)
	{
		reset_std(shell, cmd);
		clean_commands(cmd);
		return (FALSE);
	}
	if (cmd->input_fd != STDIN_FILENO || cmd->output_fd != STDOUT_FILENO)
	{
		if (!reset_std(shell, cmd))
			return (FALSE);
	}
	cleanup_success(shell, cmd);
	return (TRUE);
}

int	execute(t_mini *shell, t_cmd *cmd)
{
	int			is_builtin;

	is_builtin = builtins(cmd->cmds[0]);
	if (shell->cmd_count == 1 && is_builtin)
	{
		if (!exec_parent(shell, cmd, is_builtin))
			return (shell->exit_code);
		shell->exit_code = 0;
		return (shell->exit_code);
	}
	else
	{
		if (!exec_child(shell, cmd))
			cleanup_failure(shell, cmd);
	}
	return (shell->exit_code);
}
