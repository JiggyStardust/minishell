/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:55 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 14:26:54 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resolve_input_child(t_mini *shell, t_cmd *cmd, t_token *token, int redir_i)
{
	int	fd;

	fd = -1;
	if (!token->next)
	{
		error_file(shell, NULL, AMBIG, 1);
		return (FALSE);
	}
	if (token->type == REDIR_IN)
		fd = open_infile(shell, token->next->value);
	if (fd == -2)
	{
		if (cmd->input_fd > -1)
			close(cmd->input_fd);
		cmd->input_fd = -1;
		return (FALSE);
	}
	else if (redir_i >= cmd->heredoc_i)
	{
		if (cmd->input_fd > -1)
			close(cmd->input_fd);
		cmd->input_fd = fd;
	}
	return (TRUE);
}

int	handle_redirection_child(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	token = cmd->tokens;
	i = 0;
	while (token)
	{
		if (token->type == REDIR_IN)
		{
			if (!resolve_input_child(shell, cmd, token, i))
				return (close_extra_fd(cmd->output_fd), FALSE);
		}
		else if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
		{
			if (!resolve_output(shell, cmd, token))
				return (close_extra_fd(cmd->input_fd), FALSE);
		}
		token = token->next;
		i++;
	}
	return (TRUE);
}
