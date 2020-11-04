/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:44:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 13:10:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_home(char **str, t_mns *mns, char **new, int *i)
{
	if ((((str[0][*i - 1] && str[0][*i - 1] == ' ') || *i == 0)))
	{
		if (!(*new = ft_straddstr(*new, get_env_var(mns->envp, "HOME", 0), 3)))
			return (1);
	}
	return (0);
}

static int		check_dollar(char **str, t_mns *mns, char **new, int *i)
{
	if (str[0][*i + 1] == '?')
	{
		if (!(*new = ft_straddstr(*new, ft_itoa(mns->last_return), 3)))
			return (1);
		(*i)++;
		return (0);
	}
	if (!(*new = ft_straddstr(*new, get_env_var(mns->envp, get_env_name(
		*str, *i + 1), 1), 3)))
		return (1);
	while (str[0][*i + 1] == '_' || ft_isalpha(str[0][*i + 1])
		|| ft_isdigit(str[0][*i + 1]))
		(*i)++;
	return (0);
}

static char		*update_dollar(char **str, t_mns *mns)
{
	int		i;
	char	*new;

	if (!(new = ft_strdup("")))
		return (NULL);
	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && str[0][i + 1] && ft_strchr(
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_?",
			str[0][i + 1]) && is_in_quotes(str[0], i) != 1)
		{
			if (check_dollar(str, mns, &new, &i))
				return (NULL);
		}
		else if (str[0][i] == '$' && str[0][i + 1] && ft_strchr(
			"1234567890@*", str[0][i + 1]) && is_in_quotes(str[0], i) != 1)
			i++;
		else if (!(new = ft_straddchar(new, str[0][i])))
			return (NULL);
	}
	free(*str);
	return (new);
}

static char		*update_home_tabs(char **str, t_mns *mns)
{
	int		i;
	char	*new;

	if (!(new = ft_strdup("")))
		return (NULL);
	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '~')
		{
			if (check_home(str, mns, &new, &i))
				return (NULL);
		}
		else if (str[0][i] == '\t' && !is_in_quotes(str[0], i))
		{
			if (!(new = ft_straddchar(new, ' ')))
				return (NULL);
		}
		else if (!(new = ft_straddchar(new, str[0][i])))
			return (NULL);
	}
	free(*str);
	return (new);
}

int				update_input(char **str, t_mns *mns)
{
	if (!(*str = update_home_tabs(str, mns)))
		return (1);
	if (!(*str = update_dollar(str, mns)))
		return (1);
	if (!(*str = update_star(str)))
		return (1);
	return (0);
}
