/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:04:29 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/01 10:48:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			remove_parenthesis(char *str)
{
	int			drift;
	int			i;

	drift = 0;
	i = -1;
	while (str[++i])
	{
		str[i - drift] = str[i];
		if (str[i] == '(' || str[i] == ')')
			drift++;
	}
	str[i - drift] = str[i];
}
