/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:33:10 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:16:05 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		fill_size(char *line, int my_size, int *flag)
{
	int size;

	if ((size = ft_atoi(line)) < 1)
		ft_error(4);
	if (size > my_size)
		size = my_size;
	*flag = 1;
	return (size);
}

void	fill_resolution(char *line, t_data *data, t_flags *flags)
{
	int my_width;
	int my_height;

	mlx_get_screen_size(data->mlx, &my_width, &my_height);
	while (*line != '\0')
	{
		if (*line == ' ' || *line == 'R')
			line++;
		else if (ft_isdigit(*line))
		{
			if (!flags->width)
				data->width = fill_size(line, my_width, &(flags->width));
			else if (flags->width && !flags->height)
				data->height = fill_size(line, my_height, &(flags->height));
			else if (flags->width && flags->height)
				ft_error(4);
			while (ft_isdigit(*line))
				line++;
		}
		else
			ft_error(4);
	}
	if (!flags->width || !flags->height)
		ft_error(4);
	flags->resolution = 1;
}

char	is_map_coordinates(t_data *data, float x, float y)
{
	if ((int)x >= 0 && x < data->map_width && y >= 0 && y < data->map_height)
		return (1);
	return (0);
}

float	calc_s_dist(t_data *data, float x, float y)
{
	float dist;

	x = x + 0.5;
	y = y + 0.5;
	dist = sqrt(pow(data->py - y, 2) + pow(x - data->px, 2));
	return (dist);
}

int		get_max_str(t_list *temp)
{
	int len;

	len = 0;
	while (temp != NULL)
	{
		if ((int)ft_strlen(temp->content) > len)
			len = (int)ft_strlen(temp->content);
		temp = temp->next;
	}
	return (len);
}
