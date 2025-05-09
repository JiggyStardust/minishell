/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:24:45 by prynty            #+#    #+#             */
/*   Updated: 2025/01/16 21:56:56 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char ***str)
{
	size_t	i;

	if (!str || !*str)
		return ;
	i = 0;
	while ((*str)[i] != NULL)
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}
