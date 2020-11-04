/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:31:13 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:34:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Split by operators
*/

/*
** Part 01 | Split cmd & args
*/

int		split_operators_valid_char(t_operator_split *op_s, char *str)
{
	if (!(op_s->splited_str[op_s->j] = malloc(sizeof(char) *
	(ft_strlen(str) + 1))))
		return (-1);
	while (str[op_s->i] && (str[op_s->i] != '&' && str[op_s->i] != '|'))
	{
		op_s->splited_str[op_s->j][op_s->k] = str[op_s->i];
		++op_s->i;
		++op_s->k;
	}
	op_s->splited_str[op_s->j][op_s->k] = 0;
	op_s->k = 0;
	++op_s->j;
	op_s->splited_str[op_s->j] = NULL;
	while (str[op_s->i] && str[op_s->i] == ' ')
		++op_s->i;
	return (0);
}

/*
** Part 02 | Split operators
*/

int		split_operators_op(t_operator_split *op_s, char *str)
{
	if (!(op_s->splited_str[op_s->j] = malloc(sizeof(char) *
	(ft_strlen(str) + 1))))
		return (-1);
	while (str[op_s->i] && (str[op_s->i] == '&' || str[op_s->i] == '|'))
	{
		op_s->splited_str[op_s->j][op_s->k] = str[op_s->i];
		++op_s->i;
		++op_s->k;
	}
	op_s->splited_str[op_s->j][op_s->k] = 0;
	op_s->k = 0;
	++op_s->j;
	op_s->splited_str[op_s->j] = NULL;
	while (str[op_s->i] && str[op_s->i] && str[op_s->i] == ' ')
		++op_s->i;
	return (0);
}

char	**split_operators(char *str)
{
	t_operator_split op_s;

	op_s.i = 0;
	op_s.j = 0;
	op_s.k = 0;
	if (!(op_s.splited_str = malloc(sizeof(char *) * (ft_strlen(str) *
	ft_strlen(str)))))
		return (NULL);
	while (str[op_s.i])
	{
		if ((split_operators_valid_char(&op_s, str)) == -1)
			return (NULL);
		if ((split_operators_op(&op_s, str)) == -1)
			return (NULL);
	}
	if (op_s.splited_str[op_s.j - 1])
		free(op_s.splited_str[op_s.j - 1]);
	op_s.splited_str[op_s.j - 1] = NULL;
	return (op_s.splited_str);
}
