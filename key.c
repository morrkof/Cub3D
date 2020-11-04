/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:15:35 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/04 18:16:11 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		esc_key(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int		ft_exit(void)
{
	exit(0);
}

int		ft_keys_walk(int keycode, t_data *data)
{
	float	x;
	float	y;
	float	a;

	x = data->px;
	y = data->py;
	a = data->pa;
	if (keycode == KEY_W)
		move_player(data, data->pa);
	if (keycode == KEY_S)
		move_player(data, norm_ang(data->pa + PI));
	if (keycode == KEY_A)
		move_player(data, norm_ang(data->pa + PI / 2));
	if (keycode == KEY_D)
		move_player(data, norm_ang(data->pa - PI / 2));
	if (keycode == KEY_L_ARR)
		data->pa = norm_ang(data->pa + TURN_SPD);
	if (keycode == KEY_R_ARR)
		data->pa = norm_ang(data->pa - TURN_SPD);
	if (x == data->px && y == data->py && a == data->pa)
		return (0);
	refresh(data);
	return (0);
}

void	move_player(t_data *data, float angle)
{
	float	x;
	float	y;
	float	d;
	t_ray	ray;

	d = 0.2;
	y = data->py - SPD * sin(angle);
	x = data->px + SPD * cos(angle);
	ray = cast_ray(data, angle);
	if (ray.len > SPD)
	{
		if (data->map[(int)y][(int)(x - d)] == '1')
			x = (int)x + d;
		if (data->map[(int)y][(int)(x + d)] == '1')
			x = (int)x + (1 - d);
		if (data->map[(int)(y - d)][(int)x] == '1')
			y = (int)y + d;
		if (data->map[(int)(y + d)][(int)x] == '1')
			y = (int)y + (1 - d);
		data->py = y;
		data->px = x;
	}
}

int		refresh(t_data *data)
{
	draw_ceil_and_floor(data);
	draw_walls_and_sprites(data);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_do_sync(data->mlx);
	return (0);
}
