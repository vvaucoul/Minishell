#include "termcaps_bonus.h"

void	term_read_line(char **input)
{
	t_line	*line;
	t_bool	use_multilines;
	int		key_pressed;

	line = init_new_line();
	use_multilines = FALSE;
	while (1)
	{
		key_pressed = get_key();
		if (!term_get_multiline(line, &use_multilines, key_pressed))
		{
			if (!(cmp_keys(line, key_pressed)))
				break ;
		}
		else if (use_multilines == 2)
			break ;
	}


	input[0] = ft_strdup(line->cmd);

	// a revoir pour l input de le faou

}