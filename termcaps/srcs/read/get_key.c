/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:25:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/27 17:49:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
**	Read
*/

// to display key code
// printf("str_buffer [%p]\n", str_buffer[0]);
// printf("str_buffer [%p]\n", str_buffer[1]);
// printf("str_buffer [%p]\n", str_buffer[2]);
// printf("str_buffer [%p]\n", str_buffer[3]);
// printf("str_buffer [%p]\n", str_buffer[4]);
// printf("str_buffer [%p]\n", str_buffer[5]);

int		compare_keys_01(char *str_buffer)
{
	// jump through words (shift left, shift right)
	if (!(memcmp(str_buffer, KEY_CODE_SHIFT_LEFT, ADD_KEY_SHIFT_LEN + ADD_KEY_SHIFT_LEN)))
	return (KEY_SLEFT);
	else if (!(memcmp(str_buffer, KEY_CODE_SHIFT_RIGHT, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	return (KEY_SRIGHT);

	// edition sur plusieurs lignes
	else if (!(memcmp(str_buffer, KEY_CODE_SHIFT_UP, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	return (KEY_SHIFT_UP);
	else if (!(memcmp(str_buffer, KEY_CODE_SHIFT_DOWN, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	return (KEY_SHIFT_DOWN);

	// copy , cut & paste
	else if (!(memcmp(str_buffer, KEY_CODE_INSERT_INDEX, MAX_KEY_LEN)))
	return (KEY_INSERT_INDEX);
	else if (!(memcmp(str_buffer, KEY_CODE_COPY, MAX_KEY_LEN)))
	return (KEY_CCOPY);
	else if (!(memcmp(str_buffer, KEY_CODE_CUT, MAX_KEY_LEN)))
	return (KEY_CUT);
	else if (!(memcmp(str_buffer, KEY_CODE_PASTE, MAX_KEY_LEN)))
	return (KEY_PASTE);
	return (0);
}


int		compare_keys(char *str_buffer)
{
	int tmp;

	// History (with up & down)
	if (!(memcmp(str_buffer, KEY_CODE_UP, MAX_KEY_LEN)))
	return (KEY_UP);
	else if (!(memcmp(str_buffer, KEY_CODE_DO, MAX_KEY_LEN)))
	return (KEY_DOWN);

	// cursor motion (left, right)
	else if (!(memcmp(str_buffer, KEY_CODE_RI, MAX_KEY_LEN)))
	return (KEY_RIGHT);
	else if (!(memcmp(str_buffer, KEY_CODE_LE, MAX_KEY_LEN)))
	return (KEY_LEFT);

	// home | end (start | end line)
	else if (!(memcmp(str_buffer, KEY_CODE_HOME, MAX_KEY_LEN)))
	return (KEY_HOME);
	else if (!(memcmp(str_buffer, KEY_CODE_END, MAX_KEY_LEN)))
	return (KEY_END);

	// compare other keys
	else if ((tmp = compare_keys_01(str_buffer)))
		return (tmp);
	return (str_buffer[0]);
}

int		get_key()
{
	char	*str_buffer;
	int		r_key;

	if (!(str_buffer = ft_newstr(MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
		return (-1);
	read(0, str_buffer, 1);
	if (str_buffer[0] == START_SPECIAL_CHAR)
		read(0, str_buffer + 1, MAX_KEY_LEN - 1);
	if (str_buffer[2] == START_SHIFT_CHAR)
		read(0, str_buffer + 1, ADD_KEY_SHIFT_LEN);
	r_key = compare_keys(str_buffer);
	free(str_buffer);
	return (r_key);
}
