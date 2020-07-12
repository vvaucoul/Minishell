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

static char **move_table(char **tab, int i)
{
	char **n_tab;
	int tab_len;

	printf("move table\n");

	n_tab = malloc(sizeof(char *) * 1000);

	tab_len = -1;
	while (tab[++tab_len]);
	//--tab_len;
	printf("tab len [%d] > [%d]\n", tab_len, i);
	while (tab[tab_len] && tab_len > i)
	{
		printf("swap [%s] to [%s]\n", tab[tab_len], tab[tab_len - 1]);
		tab[tab_len] = tab[tab_len - 1];
		-- tab_len;
	}
	tab[tab_len + 1] = NULL;
	return (tab);
}

char **add_default_flag(char **tab)
{
	int i;

	i = 0;

	print_table(tab, "DefaultFLag Before : ");

	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], "ls")) || !(ft_strcmp(tab[i], "grep")))
		{
			tab = move_table(tab, i);
			tab[i + 1] = ft_strdup("--color");
		}
		++i;
	}
	print_table(tab, "DefaultFLag After : ");
	return (tab);
}
