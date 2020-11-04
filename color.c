/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:52:47 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:15:51 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rgb_init(t_flags *flags)
{
	flags->r_color = 0;
	flags->g_color = 0;
	flags->b_color = 0;
}

int		fill_color_part(char *line, int *flag)
{
	int	color;

	color = ft_atoi(line);
	if (color > 255 || color < 0)
		ft_error(5);
	*flag = 1;
	return (color);
}

void	sort_color(char *line, t_flags *flags, t_color *col)
{
	if (!flags->r_color)
		col->r = fill_color_part(line, &(flags->r_color));
	else if (flags->r_color && !flags->g_color && !flags->b_color)
		col->g = fill_color_part(line, &(flags->g_color));
	else if (flags->r_color && flags->g_color && !flags->b_color)
		col->b = fill_color_part(line, &(flags->b_color));
	else if (flags->r_color && flags->g_color && flags->b_color)
		ft_error(5);
}

int		fill_color(char *line, t_flags *flags, int *flag)
{
	t_color	col;

	rgb_init(flags);
	while (*line != '\0')
	{
		if (*line == ' ' || *line == ',' || *line == 'F' || *line == 'C')
			line++;
		else if (ft_isdigit(*line))
		{
			sort_color(line, flags, &col);
			while (ft_isdigit(*line))
				line++;
		}
		else
			ft_error(5);
	}
	if (!flags->r_color || !flags->g_color || !flags->b_color)
		ft_error(5);
	*flag = 1;
	return (65536 * col.r + 256 * col.g + col.b);
}

void	check_ext(char *line)
{
	int len;

	len = (int)ft_strlen(line);
	if (line[len - 1] != 'b' || line[len - 2] != 'u')
		ft_error(1);
	if (line[len - 3] != 'c' || line[len - 4] != '.')
		ft_error(1);
}
