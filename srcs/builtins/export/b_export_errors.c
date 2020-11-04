/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:45:19 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 22:01:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_first_char(char c)
{
	char	*range;
	int		i;

	range = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
	i = 0;
	while (range[i])
	{
		if (range[i] == c)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

static t_bool	check_export_cmd(char *str)
{
	t_bool	valid;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		valid = FALSE;
		j = 0;
		while (STRNG[j])
		{
			if (!valid)
				if (str[i] == STRNG[j])
					valid = TRUE;
			++j;
		}
		if (!valid)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int				check_export_warnings(t_b_export *export_s)
{
	if (export_s->already_existing >= 0 && !export_s->value)
		return (FALSE);
	return (TRUE);
}

int				check_export_errors(t_b_export *export_s)
{
	if (!(check_first_char(export_s->cmd[0])))
		return (FALSE);
	if (!(check_export_cmd(export_s->cmd)))
		return (FALSE);
	if (!export_s->cmd)
		return (FALSE);
	return (TRUE);
}
