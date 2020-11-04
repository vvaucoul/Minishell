/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:34:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/01 23:24:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_pwd(t_mns *mns, t_bool using_nl)
{
	char	actu_dir[MAX_CHAR_IN_PROMPT];

	if (!(getcwd(actu_dir, sizeof(actu_dir))))
	{
		if (using_nl)
			return (display_error_tf("pwd: ", "erreur de détermination du \
			répertoire actuel : getcwd : ne peut accéder aux répertoires \
			parents : Aucun fichier ou dossier de ce type", NULL, 1));
		else
		{
			ft_putstr_fd(MNS_COLOR_RED, 2);
			ft_putstr_fd("PWD ERROR", 2);
			ft_putstr_fd(MNS_COLOR_NOC, 2);
		}
		return (1);
	}
	ft_putstr_fd(actu_dir, using_nl ? 1 : 2);
	if (using_nl)
		ft_putstr_fd("\n", 2);
	if (mns && using_nl)
		update_last_return(mns, 0);
	return (1);
}
