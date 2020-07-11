/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:15:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 16:16:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*epur_b_str(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;

	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			new_str[j] = str[i];
			++j;
		}
		++i;
	}
	new_str[j] = '\0';
	return (new_str);
}
