/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:24:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:07:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				export_start_oldpwd(t_mns *mns)
{
	char	actu_dir[MAX_CHAR_IN_PROMPT];
	char	*export_path[3];

	if (!(getcwd(actu_dir, sizeof(actu_dir))))
		return (display_error_tf(E_SSI, NULL, NULL, -1));
	export_path[0] = ft_strdup("export");
	export_path[1] = ft_strjoin("OLD_PWD=", actu_dir);
	export_path[2] = NULL;
	b_export(mns, export_path);
	free(export_path[0]);
	free(export_path[1]);
	return (0);
}

int				init_exit(t_mns *mns)
{
	mns->exit.exit_shell = FALSE;
	mns->exit.s_args = NULL;
	mns->exit.ret = 0;
	return (0);
}

static int		init_envp(t_mns *mns, char **envp)
{
	int i;

	if (!(mns->envp = malloc(sizeof(char *) * (ft_full_tablen(envp) + 1))))
		return (FALSE);
	i = 0;
	while (envp[i])
	{
		if (!(mns->envp[i] = ft_strdup(envp[i])))
			return (FALSE);
		++i;
	}
	mns->envp[i] = NULL;
	return (TRUE);
}

int				start_minishell(t_mns *mns, char **envp)
{
	char	*tabl[3];
	char	*tmp;
	char	*sh_lv_str;
	int		ac_shlvl;

	if (!(init_envp(mns, envp)))
		return (-1);
	init_exit(mns);
	tabl[0] = "export";
	sh_lv_str = get_env_var(mns->envp, "SHLVL", FALSE);
	ac_shlvl = ft_atoi(sh_lv_str);
	tmp = ft_itoa(ac_shlvl + 1);
	tabl[1] = ft_strjoin("SHLVL=", tmp);
	tabl[2] = NULL;
	b_export(mns, tabl);
	multi_free(NULL, sh_lv_str, tmp, tabl[1]);
	export_start_oldpwd(mns);
	return (0);
}
