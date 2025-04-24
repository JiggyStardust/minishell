/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:46 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:23:47 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std(t_mini *shell, t_cmd *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		if (cmd->saved_stdin == -1)
		{
			shell->exit_code = 1;
			ft_putstr_fd("minishell: failed to save stdin\n", 2);
			return (FALSE);
		}
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->saved_stdout == -1)
		{
			shell->exit_code = 1;
			ft_putstr_fd("minishell: failed to save stdout\n", 2);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	reset_std(t_mini *shell, t_cmd *cmd)
{
	if (cmd->saved_stdin != -1 && cmd->saved_stdin != STDIN_FILENO)
	{
		if (!dup2_close(cmd->saved_stdin, STDIN_FILENO))
		{
			ft_putstr_fd("minishell: failed to restore stdin\n", 2);
			shell->exit_code = 1;
			cmd->saved_stdin = -1;
			return (FALSE);
		}
		cmd->saved_stdin = -1;
	}
	if (cmd->saved_stdout != -1 && cmd->saved_stdout != STDOUT_FILENO)
	{
		if (!dup2_close(cmd->saved_stdout, STDOUT_FILENO))
		{
			ft_putstr_fd("minishell: failed to restore stdout\n", 2);
			shell->exit_code = 1;
			cmd->saved_stdout = -1;
			return (FALSE);
		}
		cmd->saved_stdout = -1;
	}
	return (TRUE);
}
