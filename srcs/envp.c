/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:24:32 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/09 16:10:38 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_cmd_line(char *str)
{
	char *line;
	int i;
	int si;

	i = 0;
	while (str[i] != '=')
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

static	T_BOOL	strdelcmnp(char *s1, char *s2, char del)
{
	int	i;

	i = 0;
	//printf("compare : %s with %s\n", s1, s2);
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
	{
		if (s1[i] == del || s2[i] == del)
			return (0);
		++i;
	}
	return (s1[i] - s2[i]);
}

char			*get_env_value(char *value, char **envp)
{
	int j;

	j = 0;
	if (!value)
	return (NULL);
	while (envp[j])
	{
		if (!(strdelcmnp(envp[j], ft_strcat(value, "="), '=')))
			return (get_cmd_line(envp[j]));
		++j;
	}
	return (NULL);
}

char		*get_env_var(char **envp, char *to_find, int free_to_find)
{
	int		i;
	char	*ret;

	// printf("get env var\n");
	i = 0;
	while(envp && envp[i])
	{
		// printf("env : [%s]\n", envp[i]);
		// printf("to find : [%s]\n", ft_strjoin(to_find, "="));
		if (ft_strstartswith(envp[i], ft_strjoin(to_find, "="), 0, 1))
		{
			// printf("I'm in boys\n");
			if (!(ret = ft_strcut(envp[i], '=')))
				return (NULL);
			return (ret);
		}
		i++;
	}
	if (free_to_find)
		free(to_find);
	return (NULL);
}

char		*get_env_name(char *str, int i)
{
	char *name;

	if (!(name = ft_strnew(1)))
		return (NULL);
	name[0] = '\0';
	while (str[i] && ft_isupper(str[i]))
	{
		if (!(name = ft_straddchar(name, str[i])))
			return (NULL);
		i++;
	}
	return (name);
}
