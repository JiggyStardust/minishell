/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:19:28 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:19:30 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(int id, t_mini *shell, t_cmd *head, char **args)
{
	int	code;

	sig_reset();
	code = 0;
	if (id == BUILTIN_CD)
		code = builtin_cd(shell, args);
	if (id == BUILTIN_ECHO)
		code = builtin_echo(args);
	else if (id == BUILTIN_ENV)
		code = builtin_env(shell);
	else if (id == BUILTIN_EXIT)
		code = builtin_exit(shell, head, args);
	else if (id == BUILTIN_EXPORT)
		code = builtin_export(shell, args);
	else if (id == BUILTIN_PWD)
		code = builtin_pwd(shell);
	else if (id == BUILTIN_UNSET)
		code = builtin_unset(shell, args);
	shell->exit_code = code;
	return (code);
}

int	builtins(char *cmd)
{
	if (!cmd)
		return (BUILTIN_NONE);
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
