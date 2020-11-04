/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_set_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:37:28 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 19:52:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*make_envp_last_line(t_b_export *export_s,
char *old_v)
{
	char *str;

	str = ft_strdup(export_s->cmd);
	if (export_s->has_equal)
	{
		if (export_s->use_join)
		{
			str = ft_strjoin_tf(str, "=", 1);
			str = ft_strjoin_tf(str, old_v, 3);
			str = ft_strjoin_tf(str, export_s->value, 1);
		}
		else
		{
			str = ft_strjoin_tf(str, "=", 1);
			if (export_s->value)
				str = ft_strjoin_tf(str, export_s->value, 1);
			if (old_v)
				free(old_v);
		}
	}
	return (str);
}

static int		add_envp_line(t_mns *mns, t_b_export *export_s)
{
	int last_len;
	int add_len;

	last_len = ft_tablen(mns->envp);
	add_len = ft_strlen(export_s->cmd);
	if (export_s->value)
		add_len += ft_strlen(export_s->value);
	if (!(mns->envp = ft_realloc_tab(mns->envp, ((add_len) + 2), 1, TRUE)))
		return (display_error_tf("Malloc Error", NULL, NULL, -1));
	if (!(mns->envp[last_len] = make_envp_last_line(export_s, NULL)))
		return (-1);
	return (TRUE);
}

static int		set_envp_line(t_mns *mns, t_b_export *export_s)
{
	char	*envp_old_value;

	envp_old_value = get_env_var(mns->envp, export_s->cmd, FALSE);
	free(mns->envp[export_s->already_existing]);
	if (!(mns->envp[export_s->already_existing] = make_envp_last_line(export_s,
		envp_old_value)))
		return (-1);
	return (TRUE);
}

int				export_set_env(t_mns *mns, t_b_export *export_s)
{
	if (export_s->already_existing < 0)
	{
		if (add_envp_line(mns, export_s) == -1)
			return (-1);
	}
	else
	{
		if (set_envp_line(mns, export_s) == -1)
			return (-1);
	}
	return (1);
}
