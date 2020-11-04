/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:43 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 16:49:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			free_str(char *s1, char *s2, int to_free)
{
	if (to_free == 1)
		free(s1);
	if (to_free == 2)
		free(s2);
	if (to_free == 3)
	{
		free(s1);
		free(s2);
	}
}

char				*ft_strjoin_tf(char *s1, char *s2, int to_free)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	new[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		new[j + i] = s2[i];
	free_str(s1, s2, to_free);
	return (new);
}
