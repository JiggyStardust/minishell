/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:21:43 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:21:47 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_mrworldwide = 0;

static char	*setup_input(t_mini *shell)
{
	char	*input;
	char	prompt[1024];

	input = NULL;
	get_prompt(shell, prompt, sizeof(prompt));
	input = readline(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

static void	minishell(t_mini *shell)
{
	char	*input;
	t_cmd	*cmds;

	while (TRUE)
	{
		sig_init(&sig_handler_sigint);
		input = setup_input(shell);
		if (input == NULL)
			break ;
		if (*input)
		{
			if (!lexer(shell, input))
			{
				if (input && *input)
				{
					free(input);
					continue ;
				}
			}
			cmds = tokenizer(shell, shell->input);
			if (cmds)
				execute(shell, cmds);
		}
		shell->cmd_count = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini		shell;

	(void)argc;
	(void)argv;
	if (!setup(&shell, env))
	{
		ft_putstr_fd("minishell: initialization error\n", STDERR_FILENO);
		ft_free_array(&shell.env);
		exit(EXIT_FAILURE);
	}
	minishell(&shell);
	ft_free_array(&shell.env);
	free_null(&shell.cwd);
	return (shell.exit_code);
}
