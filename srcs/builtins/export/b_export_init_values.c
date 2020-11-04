/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_init_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:30:00 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 10:46:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*get_cmd(char *line, int *start, char delimiteur)
{
	char	cmd[MAX_CHAR_IN_PROMPT];

	while (line[*start] && line[*start] != delimiteur)
	{
		cmd[*start] = line[*start];
		++(*start);
	}
	cmd[*start] = '\0';
	++(*start);
	if (delimiteur == ENV_JOIN_DELIMITEUR)
		++(*start);
	if (*start - (delimiteur == ENV_JOIN_DELIMITEUR ? 2 : 1) <= 0)
		return (NULL);
	return (ft_strdup(cmd));
}

static char			*get_value(char *line, int *start)
{
	char	value[MAX_CHAR_IN_PROMPT];
	int		j;

	j = 0;
	while (line[*start])
	{
		value[j] = line[*start];
		++(*start);
		++j;
	}
	value[j] = '\0';
	return (ft_strdup(value));
}

int					get_export_values(t_b_export *export_s, char *line)
{
	int gi;

	gi = 0;
	if (!(export_s->cmd = get_cmd(line, &gi, export_s->use_join
	? ENV_JOIN_DELIMITEUR : ENV_DELIMITEUR)))
		return (FALSE);
	if (export_s->has_equal)
		export_s->value = get_value(line, &gi);
	return (TRUE);
}
