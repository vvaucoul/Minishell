/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:27:53 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 19:51:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Init exit struct
** When called, ask to shell to quit at the end (to free all things)
*/

int				init_exit_struct(t_mns *mns, char **tabl)
{
	int i;

	if (mns->exit.exit_shell)
		return (1);
	i = 0;
	mns->exit.exit_shell = TRUE;
	if (!(mns->exit.s_args = malloc(sizeof(char *) * (ft_full_tablen(tabl)))))
		return (-1);
	while (tabl[i])
	{
		mns->exit.s_args[i] = ft_strdup(tabl[i]);
		++i;
	}
	mns->exit.s_args[i] = NULL;
	mns->exit.ret = get_last_return(mns);
	return (1);
}

/*
** Exit Final shell
** Ctrl D & exit cmd
*/

static int		final_exit(int ex, t_mns *mns)
{
	ft_freetab(mns->exit.s_args);
	free_envp(mns);
	free(mns);
	if (BONUS)
		termios_reset_term();
	exit(ex);
}

/*
** Builtin Exit
*/

static	void	b_exit_write(t_mns *mns, t_bool write_exit)
{
	if (write_exit)
		ft_putstr_fd("exit\n", 2);
	if (mns->exit.s_args)
	{
		if (mns->exit.s_args[1])
		{
			mns->last_return = ((ft_stris_digit(mns->exit.s_args[1])) ?
			(unsigned int)ft_atoi(mns->exit.s_args[1]) : mns->exit.ret);
			final_exit((ft_stris_digit(mns->exit.s_args[1])) ?
			(unsigned int)ft_atoi(mns->exit.s_args[1]) : mns->exit.ret, mns);
		}
		else
			final_exit(mns->exit.ret, mns);
	}
	else
		final_exit(mns->exit.ret, mns);
}

int				b_exit(t_mns *mns, t_bool write_exit)
{
	if (mns->exit.s_args)
	{
		if (mns->exit.s_args[1])
		{
			if (!ft_stris_digit(mns->exit.s_args[1]) ||
			ft_strlen(mns->exit.s_args[1]) >= 19)
			{
				ft_putstr_fd("exit\n", 2);
				display_error_tf("exit: ", mns->exit.s_args[1],
				": numeric argument requiered", 0);
				final_exit(MNS_ERROR, mns);
			}
		}
		if (ft_tablen(mns->exit.s_args) > 2)
		{
			ft_freetab(mns->exit.s_args);
			display_error_tf("exit: ", NULL, "too many arguments", FALSE);
			init_exit(mns);
			return (mns->last_return = 1);
		}
	}
	b_exit_write(mns, write_exit);
	ft_freetab(mns->exit.s_args);
	init_exit(mns);
	return (1);
}
