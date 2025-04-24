/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:20:04 by prynty            #+#    #+#             */
/*   Updated: 2025/01/18 13:20:05 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_mini *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_builtin(PWD, NULL, "cannot access current directory");
		return (1);
	}
	printf("%s\n", shell->cwd);
	free(cwd);
	return (0);
}
