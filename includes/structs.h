/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:27:10 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:27:12 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

extern volatile sig_atomic_t	g_mrworldwide;

typedef struct s_mini
{
	char	**env;
	int		cmd_count;
	char	*cwd;
	char	*input;
	int		**pipes;
	int		*pids;
	int		exit_code;
}	t_mini;

enum e_builtins
{
	BUILTIN_NONE,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET
};

typedef enum e_token_type
{
	CMD,
	FILENAME,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	DELIMITER
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*tokens;
	char			**cmds;
	int				input_fd;
	int				output_fd;
	int				saved_stdin;
	int				saved_stdout;
	int				heredoc_i;
	int				cmd_i;
	struct s_cmd	*next;
}	t_cmd;

#endif