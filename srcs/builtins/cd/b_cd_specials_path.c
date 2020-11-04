/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_specials_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:47:45 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 22:35:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_check_specials_paths(char *path)
{
	char		buff[MAX_CHAR_IN_PROMPT];

	if (!(ft_strcmp(path, ".")))
	{
		if (!(getcwd(buff, sizeof(buff))))
			return (display_error_tf("cd: ", path,
			": No such file or directory", -1));
	}
	return (0);
}

int		cd_use_multiple_args(char **tabl, int i_path)
{
	int		i;
	t_bool	found_arg;

	found_arg = FALSE;
	if (ft_tablen(tabl) >= 1 && i_path < ft_tablen(tabl))
	{
		i = 0;
		while (tabl[i_path][i])
		{
			if (tabl[i_path][i] == '-' && found_arg)
				return (FALSE);
			if (tabl[i_path][i] == '-')
				found_arg = TRUE;
			++i;
		}
	}
	else
		return (1);
	return (1);
}

int		cd_start_with_path(t_mns *mns, char **tabl)
{
	struct stat sb;

	stat(tabl[0], &sb);
	if (S_ISDIR(sb.st_mode))
	{
		update_last_return(mns, 126);
		return (display_error_tf("cd: ", tabl[0], ": is a directory", -1));
	}
	return (0);
}
