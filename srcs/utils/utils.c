/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:22:26 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/21 17:07:57 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_in_quotes(char *str, int pos)
{
	int	quote;
	int	i;
	int	add_quotes;

	add_quotes = 0;
	quote = 0;
	i = 0;
	while (i <= pos)
	{
		if (add_quotes)
		{
			quote = add_quotes;
			add_quotes = 0;
		}
		if ((str[i] == '\'' && quote == 1) || (str[i] == '"' && quote == 2))
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			add_quotes = 1;
		else if (str[i] == '"' && quote == 0)
			add_quotes = 2;
		i++;
	}
	return (quote);
}

char			*rm_quotes(char *str)
{
	char	*new_str;
	int		i;

	if (!(new_str = malloc(sizeof(char))))
		return (NULL);
	new_str[0] = '\0';
	i = 0;
	while (str[i])
	{
		if (is_in_quotes(str, i)
		|| (!is_in_quotes(str, i) && (str[i] != '\'' && str[i] != '"')))
			new_str = ft_straddchar(new_str, str[i]);
		i++;
	}
	return (new_str);
}

char			*get_cmd_in_path(char *path)
{
	char	*cmd;
	int		i;
	int		j;
	int		k;

	i = ft_strlen(path);
	j = i;
	k = 0;
	while (path[i] != 47 && i > 0)
		--i;
	++i;
	if (!(cmd = malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		cmd[k] = path[i];
		++i;
		++k;
	}
	cmd[k] = '\0';
	return (cmd);
}

t_bool			b_isvalid(char *str)
{
	if (!(ft_strcmp(str, "echo")))
		return (TRUE);
	if (!(ft_strcmp(str, "cd")))
		return (TRUE);
	if (!(ft_strcmp(str, "env")))
		return (TRUE);
	if (!(ft_strcmp(str, "export")))
		return (TRUE);
	if (!(ft_strcmp(str, "unset")))
		return (TRUE);
	if (!(ft_strcmp(str, "pwd")))
		return (TRUE);
	if (!(ft_strcmp(str, "exit")))
		return (TRUE);
	return (FALSE);
}
