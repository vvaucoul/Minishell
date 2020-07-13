/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:44:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/13 22:40:33 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_home(char **str, t_mns *mns, char **new, int *i)
{
	if ((((str[0][*i - 1] && str[0][*i - 1] == ' ') || *i == 0) &&
		((str[0][*i + 1] && str[0][*i + 1] == ' ') || str[0][*i + 1] == '\0')))
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

char		*update_input(char **str, t_mns *mns)
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
		else if (str[0][i] == '*')
		{
			if(check_star(str, mns, &new, &i))
				return (NULL);
		}
		else
			if (!(new = ft_straddchar(new, str[0][i])))
				return (NULL);
	}
	free(*str);
	return (new);
}
