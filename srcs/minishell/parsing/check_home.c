/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:44:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/09 18:44:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*check_homedollar(char **str, t_mns *mns)
{
	int		i;
	char	*new;

	if (!(new = ft_strnew(1)))
		return (NULL);
	i = -1;
	// printf("$ input [%s]\n", *str);
	while (str[0][++i])
	{
		// printf("input [%s]\n", *str);
		// printf("i : %d, new char : '%c'\n", i, str[0][i]);
		if (str[0][i] == '$')
		{
			// printf("lol $\n");
			if (str[0][i + 1] == '?')
			{
				if (!(new = ft_straddstr(new, ft_itoa(mns->last_return), 1)))
					return (NULL);
				i++;
				continue ;
			}
			if (!(new = ft_straddstr(new, get_env_var(mns->envp,
				get_env_name(*str, i + 1), 1), 1)))
				return (NULL);
			// printf("test1\n");
			while (str[0][i] && ft_isupper(str[0][i]))
				i++;
		}
		else if (str[0][i] == '~'
			&& (((str[0][i - 1] && str[0][i - 1] == ' ') || i == 0) &&
			((str[0][i + 1] && str[0][i + 1] == ' ') || str[0][i + 1] == '\0')))
		{
			// printf("lol ~\n");
			// printf("%s\n", get_env_var(envp, "HOME", 0));
			if (!(new = ft_straddstr(new, get_env_var(mns->envp, "HOME", 0), 0)))
				return (NULL);
		}
		else
		{
			if (!(new = ft_straddchar(new, str[0][i])))
				return (NULL);
		}
		// printf("new : [%s]\n", new);
	}
	free(*str);
	// printf("$ new input [%s]\n", new);
	return (new);
}
