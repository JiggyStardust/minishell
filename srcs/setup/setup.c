/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:24:39 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:24:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup(t_mini *shell, char **env)
{
	if (env == NULL)
		shell->env = NULL;
	else
	{
		shell->env = clone_env(env);
		if (!shell->env)
			return (FALSE);
	}
	sig_init(&sig_handler_sigint);
	shell->cwd = NULL;
	shell->cmd_count = 0;
	shell->input = NULL;
	shell->pipes = NULL;
	shell->pids = NULL;
	shell->exit_code = 0;
	if (!env_update_shlvl(shell))
		return (FALSE);
	if (!env_set_cwd(shell))
		return (FALSE);
	return (TRUE);
}
