/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:53:33 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/20 17:58:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	DEBUG !
*/

int		print_table(char **tabl, char *str)
{
	int i;

	i = 0;
	printf("\n");
	printf(MNS_COLOR_GREEN);
	printf("%s :\n", str);
	while (tabl[i])
	{
		printf("\t- [%d] '%s'\n", i, tabl[i]);
		++i;
	}
	printf(MNS_COLOR_NOC);
	printf("\n");
	ft_putstr(MNS_COLOR_NOC);
	return (0);
}

void	print_lst(t_list *lst, char *str)
{
	int i;

	i = 0;
	printf("\n");
	printf(MNS_COLOR_GREEN);
	printf("%s :\n", str);
	while (lst->next)
	{
		printf("\t- [%d] '%s'\n", i, (char *)lst->content);
		lst = lst->next;
		++i;
	}
	printf("\t- [%d] '%s'\n", i, (char *)lst->content);
	printf(MNS_COLOR_NOC);
	printf("\n");
	ft_putstr(MNS_COLOR_NOC);
}

void	test_leaks(void)
{
	system("leaks minishell");
	exit(0);
}
