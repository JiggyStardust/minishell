/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:00 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 14:50:21 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_eof(int line, char *lim)
{
	char	*line_str;
	char	buffer[1024];

	line_str = ft_itoa(line);
	if (!line_str)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (FALSE);
	}
	ft_strlcpy(buffer, "minishell: warning: here-document at line ",
		sizeof(buffer) - 1);
	ft_strlcat(buffer, line_str, sizeof(buffer) - 1);
	ft_strlcat(buffer, " delimited by end-of-file (wanted `",
		sizeof(buffer) - 1);
	ft_strlcat(buffer, lim, sizeof(buffer) - 1);
	ft_strlcat(buffer, "')\n", sizeof(buffer) - 1);
	ft_putstr_fd(buffer, STDERR_FILENO);
	free(line_str);
	return (TRUE);
}

int	resolve_heredoc(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	token = cmd->tokens;
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (cmd->input_fd != -1)
			{
				close(cmd->input_fd);
				cmd->input_fd = -1;
			}
			if (!token->next)
				return (error_file(shell, NULL, AMBIG, 1), FALSE);
			cmd->input_fd = handle_heredoc(token->next->value);
			if (cmd->input_fd == -1)
				return (FALSE);
			cmd->heredoc_i = i;
		}
		token = token->next;
		i++;
	}
	return (TRUE);
}

static void	heredoc_loop(char *line, char *delimiter, int *pipe_fd)
{
	write(STDOUT_FILENO, "> ", 2);
	while (TRUE)
	{
		sig_heredoc(&sig_handler_heredoc);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			heredoc_eof(__LINE__, delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
	}
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	line = NULL;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (FALSE);
	}
	sig_heredoc(&sig_handler_heredoc);
	heredoc_loop(line, delimiter, pipe_fd);
	sig_reset();
	sig_init(&sig_handler_sigint);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
