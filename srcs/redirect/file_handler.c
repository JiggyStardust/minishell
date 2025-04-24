/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:24 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:23:26 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_mini *shell, char *infile)
{
	int	input_fd;

	input_fd = open(infile, O_RDONLY);
	if (input_fd == -1)
	{
		if (access(infile, F_OK) == -1)
		{
			error_file(shell, infile, "No such file or directory", 1);
			return (-2);
		}
		if (access(infile, R_OK) == -1)
		{
			error_file(shell, infile, "Permission denied", 126);
			return (-2);
		}
	}
	return (input_fd);
}

int	open_outfile(t_mini *shell, char *outfile)
{
	int	fd_out;

	fd_out = 0;
	if (is_dir(outfile) == true)
	{
		error_file(shell, outfile, "Is a directory", 1);
		return (-2);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		error_file(shell, outfile, "Permission denied", 1);
		return (-2);
	}
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		error_file(shell, outfile, "No such file or directory", 1);
		return (-2);
	}
	return (fd_out);
}

int	open_append_file(t_mini *shell, char *outfile)
{
	int	fd_out;

	if (is_dir(outfile) == true)
	{
		error_file(shell, outfile, "Is a directory", 1);
		return (-2);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		error_file(shell, outfile, "Permission denied", 1);
		return (-2);
	}
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		error_file(shell, outfile, "No such file or directory", 1);
		return (-2);
	}
	return (fd_out);
}
