/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:06:35 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/08 16:46:46 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int		init_termcaps(t_mns *mns)
// {
// 	int		ret;
// 	char	*term_type;

// 	term_type = get_env_var(mns->envp, "TERM", 0);
// 	if (term_type == NULL)
// 	{
// 		ft_putstr("TERM must be set (see 'env').\n");
// 		return (-1);
// 	}
// 	ret = tgetent(NULL, term_type);
// 	if (ret == -1)
// 	{
// 		ft_putstr("Could not access to the termcap database..\n");
// 		return (-1);
// 	}
// 	else if (ret == 0)
// 	{
// 		ft_putstr("Terminal type '");
// 		ft_putstr(term_type);
// 		ft_putstr("' is not defined in termcap database (or have too few informations).\n");
// 		return (-1);
// 	}
// 	free(term_type);
// 	return (0);
// }
