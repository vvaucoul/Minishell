/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:34:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/20 17:47:42 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_var(char **envp, char *to_find, int free_to_find)
{
	char		*ret;
	int			i;

	ret = ft_strdup("");
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strstartswith(envp[i], ft_strjoin(to_find, "="), 0, 1))
		{
			free(ret);
			if (!(ret = ft_strcut(envp[i], ENV_DELIMITEUR)))
				return (NULL);
			break ;
		}
		i++;
	}
	if (free_to_find)
		free(to_find);
	return (ret);
}

char		*get_env_name(char *str, int i)
{
	char *name;

	if (!(name = ft_strnew(1)))
		return (NULL);
	name[0] = '\0';
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i]) ||
		ft_isdigit(str[i])))
	{
		if (!(name = ft_straddchar(name, str[i])))
			return (NULL);
		i++;
	}
	return (name);
}
