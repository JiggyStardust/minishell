/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:22:36 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:22:37 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_pipes(t_mini *shell, int i)
{
	while (i >= 0)
	{
		free(shell->pipes[i]);
		i--;
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

static void	clean_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		tokens->value = NULL;
		free(tokens);
		tokens = temp;
	}
}

void	clean_commands(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		clean_tokens(cmd->tokens);
		cmd->tokens = NULL;
		if (cmd->cmds)
			ft_free_array(&cmd->cmds);
		free(cmd);
		cmd = temp;
	}
}
