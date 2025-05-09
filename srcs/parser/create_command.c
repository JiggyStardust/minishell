/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:20:41 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:20:44 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd(int i)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmds = NULL;
	cmd->tokens = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->saved_stdin = -1;
	cmd->saved_stdout = -1;
	cmd->cmd_i = i;
	cmd->heredoc_i = 0;
	cmd->next = NULL;
	return (cmd);
}

static char	**allocate_cmd_array(t_cmd *cmd)
{
	int		count;
	char	**cmd_array;
	t_token	*token;

	token = cmd->tokens;
	count = count_token_type(token, CMD);
	cmd_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd_array)
		return (NULL);
	return (cmd_array);
}

static char	**extract_cmd(t_cmd *cmd)
{
	t_token	*token;
	char	**cmd_array;
	int		i;

	if (!cmd || !cmd->tokens)
		return (NULL);
	cmd_array = allocate_cmd_array(cmd);
	if (!cmd_array)
		return (NULL);
	i = 0;
	token = cmd->tokens;
	while (token)
	{
		if (token->type == CMD)
		{
			cmd_array[i] = ft_strdup(token->value);
			if (!cmd_array[i])
				ft_free_array(&cmd_array);
			i++;
		}
		token = token->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

t_cmd	*create_command(char *cmd_str, int i)
{
	t_cmd	*cmd;
	char	**args;

	cmd = init_cmd(i);
	if (!cmd)
		return (NULL);
	args = split_cmd_args(cmd_str);
	if (!args)
		return (NULL);
	if (!tokenize_args(cmd, args))
	{
		ft_free_array(&args);
		free(cmd);
		return (NULL);
	}
	cmd->cmds = extract_cmd(cmd);
	if (!cmd->cmds)
	{
		free(cmd);
		ft_free_array(&args);
		return (NULL);
	}
	free_2d_array(args);
	cmd->next = NULL;
	return (cmd);
}
