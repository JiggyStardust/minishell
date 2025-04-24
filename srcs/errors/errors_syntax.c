/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:21:08 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:21:09 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_quotes(t_mini *shell, char *str)
{
	char	buffer[1024];

	shell->exit_code = 2;
	ft_strlcpy(buffer, "minishell: syntax error: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, "unexpected end of file while ", sizeof(buffer) - 1);
	ft_strlcat(buffer, "looking for matching `", sizeof(buffer) - 1);
	ft_strlcat(buffer, str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "'\n", sizeof(buffer) - 1);
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_syntax(t_mini *shell, char *str)
{
	char	buffer[1024];

	shell->exit_code = 2;
	ft_strlcpy(buffer, "minishell: syntax error ", sizeof(buffer) - 1);
	ft_strlcat(buffer, "near unexpected token `", sizeof(buffer) - 1);
	ft_strlcat(buffer, str, sizeof(buffer) - 1);
	ft_strlcat(buffer, "'\n", sizeof(buffer) - 1);
	ft_putstr_fd(buffer, STDERR_FILENO);
}
