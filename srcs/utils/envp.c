/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:34:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 16:56:45 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_var(char **envp, char *to_find, int free_to_find)
{
	char	*ret;
	int		i;

	// printf("test\n");
	ret = ft_strdup("");
	i = 0;
	while(envp && envp[i])
	{
		if (ft_strstartswith(envp[i], ft_strjoin(to_find, "="), 0, 0))
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
	// printf("ret : %s\n", ret);
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


static	T_BOOL	strdelcmnp(char *s1, char *s2, char del)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
	{
		if (s1[i] == del || s2[i] == del)
			return (0);
		++i;
	}
	return (s1[i] - s2[i]);
}

static char		*get_cmd_line(char *str)
{
	char *line;
	int i;
	int si;

	i = 0;
	while (str[i] != ENV_DELIMITEUR)
	++i;
	si = ++i;
	while (str[i])
	++i;
	if (!(line = malloc(sizeof(char) * (i + 1))))
	return (NULL);
	i = 0;
	while (str[i])
	{
		line[i] = str[si];
		++i;
		++si;
	}
	line[i] = '\0';
	return (line);
}

char			*get_env_value(char *value, char **envp)
{
	int j;

	j = 0;
	if (!value)
	return (NULL);

	while (envp[j])
	{
		if (!(strdelcmnp(envp[j], ft_strcat(value, "="), ENV_DELIMITEUR)))
			return (get_cmd_line(envp[j]));
		++j;
	}
	return (NULL);
}
