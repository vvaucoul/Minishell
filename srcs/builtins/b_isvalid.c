/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_isvalid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:50:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 17:22:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	the string is a builtins ?
*/

T_BOOL		b_isvalid(char *str)
{
	if (!(ft_strcmp(str, "echo")))
		return (1);
	if (!(ft_strcmp(str, "cd")))
		return (1);
	if (!(ft_strcmp(str, "env")))
		return (1);
	if (!(ft_strcmp(str, "export")))
		return (1);
	if (!(ft_strcmp(str, "unset")))
		return (1);
	if (!(ft_strcmp(str, "pwd")))
		return (1);
	if (!(ft_strcmp(str, "exit")))
		return (1);
	return (0);
}
