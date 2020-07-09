/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:19:59 by root              #+#    #+#             */
/*   Updated: 2020/07/08 16:57:08 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static T_BOOL has_builtin(char *str)
{
    char    **tab;
    int     i;

    i = 0;
    tab = ft_split(str, ' ');
    while (tab[i])
    {
        if ((b_isvalid(tab[i])))
        return (TRUE);
        ++i;
    }
    free(tab);
    return (FALSE);
}

static T_BOOL has_redirection(char *str)
{
    char    **tab;
    int     i;

    i = 0;
    tab = ft_split(str, ' ');
    while (tab[i])
    {
        if (r_is_redirection(tab[i]))
            return (TRUE);
        ++i;
    }
    free(tab);
    return (FALSE);
}

static T_BOOL has_pipe(char *str)
{
    char    **tab;
    int     i;

    i = 0;
    tab = ft_split(str, ' ');
    while (tab[i])
    {
        if (!(ft_strcmp(tab[i], "|")))
        return (TRUE);
        ++i;
    }
    free(tab);
    return (FALSE);
}

static int  *init_tabint()
{
    int   *i;

    i = malloc(sizeof(int) * 4);
    i[0] = FALSE;
    i[1] = FALSE;
    i[2] = FALSE;
    i[3] = FALSE;
    return (i);
}

int   *parse_arguments(char **args)
{
    int     *i;
    int     y;

    i = init_tabint();
    y = 0;
    while (args[y])
    {
        if (has_builtin(args[y]))
        i[0] = TRUE;
        if (has_redirection(args[y]))
        i[1] = TRUE;
        if (has_pipe(args[y]))
        i[2] = TRUE;
        ++y;
    }
    return (i);
}
