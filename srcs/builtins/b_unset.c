/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:30:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/08 19:42:49 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	T_BOOL is_valid_parameter(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
// 		|| (str[i] >= '0' && str[i] <= '9'))
// 		++i;
// 		else
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

/*
**	Tab envp functions
*/

static int		get_envp_line(char *line, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(line, envp[i], ft_strlen(line))))
		return (i);
		++i;
	}
	return (-1);
}

int		unset_remove(char *line, char **envp)
{
	int envp_line;

	envp_line = get_envp_line(line, envp);
	printf(COLOR_CYAN); printf("Unset | Line = %d |\n", envp_line);


	envp[envp_line] = NULL;


	return (0);
}

int		b_unset(char **tab, char **envp)
{
	int i;

	i = 0;
	printf(COLOR_CYAN); printf("UNSET");
	while (tab[i])
	{

		// desactivation temporaire des tests si c est une bonne ligne de commande

		// if (!(is_valid_parameter(tab[i])))
		// {
		// 	ft_putstr_fd("unset: ", 1);
		// 	ft_putstr_fd(tab[i], 1);
		// 	ft_putstr_fd(": invalid parameter name\n", 1);
		// 	return (-1);
		// }
		// else
		// {
			unset_remove(tab[i], envp);
		// }
		++i;
	}
	return (0);
}
