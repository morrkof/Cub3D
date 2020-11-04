/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:12:19 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/30 20:27:28 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_map(t_data *data)
{
	float	x;
	float	y;
	float	map_scale;

	map_scale = 10;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[(int)y][(int)x] == '1')
				my_square(data, x * map_scale, y * map_scale, map_scale);
			if (data->map[(int)y][(int)x] == '2')
				my_square(data, x * map_scale, y * map_scale, map_scale / 2);
			x++;
		}
		y++;
	}
}

void	my_square(t_data *data, float x, float y, int px)
{
	int	ox;
	int	oy;
	int	color;

	if (px == 5)
		color = COLOR_BORDEAU;
	if (px == 10)
		color = COLOR_YELLOW;
	if (px == 6)
		color = COLOR_RASPBERRY;
	oy = 0;
	while (oy != px)
	{
		ox = 0;
		while (ox != px)
		{
			my_mlx_pixel_put(data, x + ox, y + oy, color);
			ox++;
		}
		oy++;
	}
}

void	draw_player(t_data *data)
{
	float	draw_x;
	float	draw_y;
	float	map_scale;
	float	fatness;

	map_scale = 10;
	fatness = 0.6;
	draw_x = data->px * map_scale - (fatness * map_scale) / 2;
	draw_y = data->py * map_scale - (fatness * map_scale) / 2;
	my_square(data, draw_x, draw_y, fatness * map_scale);
}
