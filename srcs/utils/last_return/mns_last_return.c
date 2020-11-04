/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_last_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:34:17 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 17:38:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_last_return(t_mns *mns, int last_return)
{
	mns->last_return = last_return;
	return (mns->last_return);
}

int		get_last_return(t_mns *mns)
{
	return (mns->last_return);
}
