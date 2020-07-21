/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:44:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/21 16:57:48 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_home(char **str, t_mns *mns, char **new, int *i)
{
	if ((((str[0][*i - 1] && str[0][*i - 1] == ' ') || *i == 0)))
	{
		if (!(*new = ft_straddstr(*new, get_env_var(mns->envp, "HOME", 0), 0)))
			return (1);
	}
	return (0);
}

static int		check_dollar(char **str, t_mns *mns, char **new, int *i)
{
	if (str[0][*i + 1] == '?')
	{
		if (!(new[0] = ft_straddstr(new[0], ft_itoa(mns->last_return), 1)))
			return (1);
		(*i)++;
		return (0);
	}
	if (!(new[0] = ft_straddstr(new[0], get_env_var(mns->envp,
		get_env_name(*str, *i + 1), 1), 1)))
		return (1);
	(*i)++;
	while (str[0][*i] && (str[0][*i] == '_' || ft_isalpha(str[0][*i]) ||
		ft_isdigit(str[0][*i])))
		(*i)++;
	return (0);
}

static char	*update_home_dollar(char **str, t_mns *mns)
{
	int		i;
	char	*new;

	if (!(new = ft_strnew(1)))
		return (NULL);
	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '~')
		{
			if (check_home(str, mns, &new, &i))
				return (NULL);
		}
		else if (str[0][i] == '$')
		{
			if (check_dollar(str, mns, &new, &i))
				return (NULL);
		} 
		else
			if (!(new = ft_straddchar(new, str[0][i])))
				return (NULL);
	}
	free(*str);
	return (new);
}

char		*update_star(char **str, int first)
{
	int		i;
	char	*new;

	if (!(new = ft_strnew(1)))
		return (NULL);
	i = 0;
	while (str[0][i])
	{
		// printf("newchar[%d] : [%s]\n", i, str[0] + i);
		if (str[0][i] == '*' && !is_in_quotes(str[0], i))
		{
			// printf("new star at %d\n", i);
			if (check_star(str, &new, &i, first))
				return (NULL);
			continue ;
			// printf("---> new : [%s]\n", new);
		}
		if (!(new = ft_straddchar(new, str[0][i])))
			return (NULL);
		i++;
	}
	free(*str);
	return (new);
}

int		contain_star(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !is_in_quotes(str, i))
			return (1);
		i++;
	}
	return (0);
}

int		update_input(char **str, t_mns *mns)
{
	int first;

	if (!(*str = update_home_dollar(str, mns)))
		return (1);
	first = 1;
	while (contain_star(*str))
	{
		// printf("--> str : [%s]\n", *str);
		if (!(*str = update_star(str, first)))
			return (1);
		first = 0;
	}
	return (0);
}
