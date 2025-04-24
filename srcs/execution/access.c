/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:22:06 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 15:51:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (false);
	return (S_ISDIR(sb.st_mode));
}

static void	access_exists(t_mini *shell, t_cmd *head, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 1;
			error_cmd(shell, head, cmd, "No such file or directory");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
}

static void	access_is_dir(t_mini *shell, t_cmd *head, char *cmd)
{
	if (is_dir(cmd) == true)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 126;
			error_cmd(shell, head, cmd, "Is a directory");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
}

static void	access_is_executable(t_mini *shell, t_cmd *head, char *cmd)
{
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 126;
			error_cmd(shell, head, cmd, "Permission denied");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
}

void	check_access(t_mini *shell, t_cmd *head, char *cmd)
{
	if (!cmd)
	{
		shell->exit_code = 127;
		error_cmd(shell, head, cmd, "command not found");
	}
	access_exists(shell, head, cmd);
	access_is_dir(shell, head, cmd);
	access_is_executable(shell, head, cmd);
}
