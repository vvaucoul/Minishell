/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:18:07 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/09 15:58:25 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char *line, t_mns *mns)
{
	char		**command;
	int			did_something;
	struct stat	stat;

	if (!(command = quotesplit(line, ' ')))
		return (-1);



	int i = 0;
	while (command[i])
	{
		printf("~ command[%d] : [%s]\n", i, command[i]);
		i++;
	}
	// printf("test???????????\n");


	if ((did_something = exec_builtins(command, mns)) != 1)
		return (did_something);
	if ((did_something = exec_system(command, mns)) != 1)
		return (did_something);
	if (lstat(command[0], &stat) != -1)
	{
		if (stat.st_mode & S_IFDIR)
		{
			// printf("return (b_cd(command, mns) == -1);\n"); //todo rm
			return (b_cd(mns, command[0]) == -1); // check return
		}
		else if (stat.st_mode & S_IXUSR)
		{
			// printf("return (todo run fonction vv);\n"); //todo rm
			return (run(mns, command[0], command, mns->envp)); // check return
		}
	}
	ft_putstr("minishell: command not found: ");
	ft_putstr(command[0]);
	write(1, "\n", 1);
	ft_freetab(command);
	return (0);
}

int			exec_input(char **commands, t_mns *mns)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (commands[i])
	{
		ret = exec_command(commands[i], mns);
		if (ret == -1)
			break ;
		i++;
	}
	return (ret);
}

char		*check_homedollar(char **str, t_mns *mns)
{
	int		i;
	char	*new;

	if (!(new = ft_strnew(1)))
		return (NULL);
	i = -1;
	// printf("$ input [%s]\n", *str);
	while (str[0][++i])
	{
		// printf("input [%s]\n", *str);
		// printf("i : %d, new char : '%c'\n", i, str[0][i]);
		if (str[0][i] == '$')
		{
			// printf("lol $\n");
			if (str[0][i + 1] == '?')
			{
				if (!(new = ft_straddstr(new, ft_itoa(mns->last_return), 1)))
					return (NULL);
				i++;
				continue ;
			}
			if (!(new = ft_straddstr(new, get_env_var(mns->envp,
				get_env_name(*str, i + 1), 1), 1)))
				return (NULL);
			// printf("test1\n");
			while (str[0][i] && ft_isupper(str[0][i]))
				i++;
		}
		else if (str[0][i] == '~'
			&& (((str[0][i - 1] && str[0][i - 1] == ' ') || i == 0) &&
			((str[0][i + 1] && str[0][i + 1] == ' ') || str[0][i + 1] == '\0')))
		{
			// printf("lol ~\n");
			// printf("%s\n", get_env_var(envp, "HOME", 0));
			if (!(new = ft_straddstr(new, get_env_var(mns->envp, "HOME", 0), 0)))
				return (NULL);
		}
		else
		{
			if (!(new = ft_straddchar(new, str[0][i])))
				return (NULL);
		}
		// printf("new : [%s]\n", new);
	}
	free(*str);
	// printf("$ new input [%s]\n", new);
	return (new);
}

int			main(int argc, char const *argv[], char **envp)
{
	t_mns	mns;
	char	*input;
	char	**commands;

	init_mns(&mns, envp, argc, argv);
	while (1)
	{
		write(1, "test --> ", 10);
		//signal ctrl c d /
		if ((get_input(&input, &mns)) == -1)
			return (-1);
		if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}
		commands = quotesplit(input, ';');
		free(input); //todo free in split :)
		if ((exec_input(commands, &mns)) == -1)
			return (-1);
		ft_freetab(commands);
	}
	return (0);
}
