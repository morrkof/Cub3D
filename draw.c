/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:29:13 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 22:39:12 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ray(t_data *data, t_ray ray)
{
	t_wall	wal;
	int		ox;
	int		oy;

	wall_init(&wal, data, ray);
	oy = 0;
	while (oy < wal.height * wal.hpart)
	{
		ox = 0;
		while (ox < wal.width)
		{
			wall_pix_put(data, wal, ox, oy);
			ox++;
		}
		oy++;
	}
}

void	draw_sprite(t_data *data, t_ray ray)
{
	int		oy;
	int		ox;
	t_spr	*sprite;
	t_wall	spr;

	sprite = data->fov_spr;
	while (sprite != NULL)
	{
		if (sprite->dist < ray.len)
		{
			if (check_angle(ray.angle, sprite->tang, sprite->bang))
			{
				spr_init(&spr, data, ray, sprite);
				oy = 0;
				while (oy < spr.height)
				{
					ox = 0;
					while (ox < spr.width && spr_pix_put(data, spr, ox, oy))
						ox++;
					oy++;
				}
			}
		}
		sprite = sprite->next;
	}
}

void	draw_walls_and_sprites(t_data *data)
{
	float	angle;
	int		n;
	t_ray	ray;

	data->fov_spr = NULL;
	set_sprites(data);
	n = 0;
	while (n < RAYS)
	{
		angle = norm_ang(data->pa + PI3 / 2 - (PI3 / RAYS) * n);
		ray = cast_ray(data, angle);
		if (ray.part < 0)
			ray.part = 1 - ray.start;
		if (ray.start + ray.part > 1)
			ray.part = 1 - ray.start;
		ray.number = n;
		draw_ray(data, ray);
		draw_sprite(data, ray);
		n++;
	}
	if (data->fov_spr != NULL)
	{
		clear_sprites(&(data->fov_spr));
		data->fov_spr = NULL;
	}
}

void	draw_ceil_and_floor(t_data *data)
{
	float x;
	float y;

	y = 0;
	while (y < data->height / 2)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->ceil_color);
			x++;
		}
		y++;
	}
	y = data->height / 2;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data, x, y, data->floor_color);
			x++;
		}
		y++;
	}
}
