/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:47:33 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 20:37:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Main Operator split func
*/

char	**operatorsplit(t_mns *mns, char **tabl)
{
	char	**new_tab;

	reset_mns_operators(mns);
	if (!(new_tab = operator_newtab(tabl)))
		return (NULL);
	if (!(new_tab = assign_op_tab(new_tab, tabl)))
		return (NULL);
	ft_freetab(tabl);
	assign_operators(mns, new_tab);
	if (!(new_tab = clean_operatortab(new_tab)))
		return (NULL);
	return (new_tab);
}
