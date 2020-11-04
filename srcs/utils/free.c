/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:15:22 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 17:47:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_envp(t_mns *mns)
{
	int i;

	i = 0;
	while (mns->envp[i])
	{
		free(mns->envp[i]);
		++i;
	}
	free(mns->envp);
}

void		multi_free(void *ptr, void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr)
		free(ptr);
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
}

void		free_tab(void **ptr)
{
	int i;

	while (ptr[i])
	{
		free(ptr[i]);
		++i;
	}
	free(ptr);
}
