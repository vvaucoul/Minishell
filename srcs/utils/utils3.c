/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 10:21:00 by root              #+#    #+#             */
/*   Updated: 2020/07/12 10:35:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **move_table(char **tabl, int i)
{
	char **n_tab;
	int tab_len;

	printf("move table\n");

	n_tab = malloc(sizeof(char *) * 1000);

	tab_len = -1;
	while (tabl[++tab_len]);
	//--tab_len;
	printf("tabl len [%d] > [%d]\n", tab_len, i);
	while (tabl[tab_len] && tab_len > i)
	{
		printf("swap [%s] to [%s]\n", tabl[tab_len], tabl[tab_len - 1]);
		tabl[tab_len] = tabl[tab_len - 1];
		-- tab_len;
	}
	tabl[tab_len + 1] = NULL;
	return (tabl);
}

char **add_default_flag(char **tabl)
{
	int i;

	i = 0;

	print_table(tabl, "DefaultFLag Before : ");

	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "ls")) || !(ft_strcmp(tabl[i], "grep")))
		{
			tabl = move_table(tabl, i);
			tabl[i + 1] = ft_strdup("--color");
		}
		++i;
	}
	print_table(tabl, "DefaultFLag After : ");
	return (tabl);
}
