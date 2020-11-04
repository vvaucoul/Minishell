/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:55:23 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 16:13:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_size(char *str, char c, int keep)
{
	unsigned int	i;
	int				size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] == c)
		{
			i++;
			size += keep;
		}
		if (!str[i])
			return (size);
		while (str[i] && (str[i] != c || is_in_quotes(str, i)))
			i++;
		size++;
		size += keep;
	}
	return (size);
}

int				split_loop(char *str, char c, int keep, t_split *splt)
{
	while (str[splt->start] == c)
		splt->start++;
	splt->end = splt->start;
	if (!str[splt->start])
		return (2);
	while (str[splt->end] && (str[splt->end] != c
		|| is_in_quotes(str, splt->end)))
		splt->end++;
	if (!(splt->res[splt->i] = ft_substr(str, splt->start,
		(splt->end - splt->start))))
		return (1);
	if (keep)
		if (!(splt->res[splt->i + 1] = ft_strdup(&c)))
			return (1);
	splt->start = splt->end;
	splt->i += keep + 1;
	return (0);
}

void			*return_free(void *to_return, void *to_free)
{
	free(to_free);
	return (to_return);
}

char			**quotesplit(char **str, char c, int keep)
{
	t_split		splt;
	int			size;
	int			ret;

	size = get_size(*str, c, keep);
	if (!(splt.res = ft_calloc(sizeof(char *), size + 1)))
		return (NULL);
	splt.start = 0;
	splt.end = 0;
	splt.i = 0;
	while (splt.i < size)
	{
		ret = split_loop(*str, c, keep, &splt);
		if (ret == 1)
			return (return_free(NULL, *str));
		if (ret == 2)
			return (return_free(splt.res, *str));
	}
	return (return_free(splt.res, *str));
}

char			**check_semicolon(char **input, t_mns *mns)
{
	int			is_ok;
	int			i;

	is_ok = 0;
	i = -1;
	while (input[0][++i])
	{
		if (input[0][i] == ';' && is_ok == 1)
			is_ok = 0;
		else if (input[0][i] == ';' && is_ok == 0)
		{
			update_last_return(mns, MNS_ERROR);
			if (
				input[0][i + 1] == ';' || (i > 0 && input[0][i - 1] == ';'))
			{
				free(*input);
				return (disperr_nul("syntax error near unexpected token `;;'"));
			}
			free(*input);
			return (disperr_nul("syntax error near unexpected token `;'"));
		}
		else if (!ft_strchr("<> (", input[0][i]))
			is_ok = 1;
	}
	return (quotesplit(input, ';', FALSE));
}
