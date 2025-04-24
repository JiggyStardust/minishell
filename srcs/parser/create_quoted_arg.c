/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:20:48 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:20:50 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_quoted_arg(char *str, int *i, int len, int k)
{
	char	*arg;
	int		j;

	arg = (char *)malloc(sizeof(char) * len + 1);
	if (!arg)
		return (NULL);
	while (str[*i] && char_is_whitespace(str[*i]))
		(*i)++;
	while (str[*i] && !char_is_whitespace(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			j = *i;
			(*i)++;
			while (str[*i] && str[*i] != str[j])
				arg[k++] = str[(*i)++];
			if (str[*i] == str[j])
				(*i)++;
		}
		else
			arg[k++] = str[(*i)++];
	}
	arg[k] = '\0';
	return (arg);
}
