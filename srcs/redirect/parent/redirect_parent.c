/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:49 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 14:46:26 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_fd(int src_fd, int dest_fd)
{
	if (src_fd != dest_fd)
	{
		if (dup2(src_fd, dest_fd) == -1)
		{
			perror("dup2 failed");
			close(src_fd);
			return (FALSE);
		}
		close(src_fd);
	}
	return (TRUE);
}

int	resolve_input(t_mini *shell, t_cmd *cmd, t_token *token)
{
	if (cmd->input_fd != -1)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (!token->next)
	{
		error_file(shell, NULL, AMBIG, 1);
		return (FALSE);
	}
	if (token->type == REDIR_IN)
		cmd->input_fd = open_infile(shell, token->next->value);
	else if (token->type == HEREDOC)
		cmd->input_fd = handle_heredoc(token->next->value);
	if (cmd->input_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	resolve_output(t_mini *shell, t_cmd *cmd, t_token *token)
{
	if (cmd->output_fd != -1)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	if (!token->next)
	{
		error_file(shell, NULL, AMBIG, 1);
		return (FALSE);
	}
	if (token->type == REDIR_OUT)
		cmd->output_fd = open_outfile(shell, token->next->value);
	else if (token->type == REDIR_APPEND)
		cmd->output_fd = open_append_file(shell, token->next->value);
	if (cmd->output_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	handle_redirection(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
		{
			if (!resolve_input(shell, cmd, token))
			{
				close_extra_fd(cmd->output_fd);
				return (FALSE);
			}
		}
		else if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
		{
			if (!resolve_output(shell, cmd, token))
			{
				close_extra_fd(cmd->input_fd);
				return (FALSE);
			}
		}
		token = token->next;
	}
	return (TRUE);
}
