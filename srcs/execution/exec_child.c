/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:56 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 15:51:33 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(t_mini *shell)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_mrworldwide = WTERMSIG(status);
			if (g_mrworldwide == SIGINT)
				shell->exit_code = 130;
		}
		i++;
	}
	return (shell->exit_code);
}

static void	exec_forked_builtin(t_mini *shell, t_cmd *cmd,
	t_cmd *head, int is_builtin)
{
	if (handle_builtin(is_builtin, shell, head, cmd->cmds) > 0)
		cleanup_failure_child(shell, head, shell->exit_code);
	cleanup_success_child(shell, head);
	exit(EXIT_SUCCESS);
}

static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd, t_cmd *head)
{
	char	*cmd_path;

	if (!cmd->cmds || !cmd->cmds[0])
		cleanup_failure_child(shell, head, 0);
	cmd_path = get_cmd_path(shell, cmd, cmd->cmds[0]);
	if (!cmd_path)
		check_access(shell, head, cmd->cmds[0]);
	else
		check_access(shell, head, cmd_path);
	sig_reset();
	if (execve(cmd_path, cmd->cmds, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, head, cmd->cmds[0], strerror(errno));
	}
}

int	fork_and_execute(t_mini *shell, t_cmd *cmd, t_cmd *head)
{
	int	is_builtin;

	sig_reset();
	is_builtin = builtins(cmd->cmds[0]);
	shell->pids[cmd->cmd_i] = fork();
	if (shell->pids[cmd->cmd_i] == -1)
	{
		perror("minishell: fork failed");
		return (FALSE);
	}
	else if (shell->pids[cmd->cmd_i] == 0)
	{
		close_unused_fds(shell, cmd->cmd_i);
		if (!configure_fds_child(shell, cmd))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (!dup_input(shell, cmd, cmd->cmd_i))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (!dup_output(shell, cmd, cmd->cmd_i))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (builtins(cmd->cmds[0]))
			exec_forked_builtin(shell, cmd, head, is_builtin);
		else
			exec_forked_cmd(shell, cmd, head);
	}
	return (TRUE);
}

int	exec_child(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*curr;

	if (!init_pipeline(shell))
		return (FALSE);
	curr = cmd;
	while (curr)
	{
		if (!resolve_heredoc(shell, curr)
			|| (!fork_and_execute(shell, curr, cmd)))
		{
			close_extra_fd(curr->input_fd);
			close_fds_and_pipes(shell, curr->cmd_i);
			break ;
		}
		sig_child(&sig_handler_child);
		close_extra_fd(curr->input_fd);
		close_fds_and_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	shell->exit_code = wait_for_children(shell);
	cleanup_success(shell, cmd);
	return (TRUE);
}
