/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:21:52 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/18 13:21:53 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_array_elements(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (count);
	while (array[count])
		count++;
	return (count);
}
