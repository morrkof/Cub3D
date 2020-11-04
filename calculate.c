/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:11:55 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 22:15:05 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_ray	cast_ray(t_data *data, float angle)
{
	t_ray vray;
	t_ray hray;

	hray = check_horizontal_walls(data, angle);
	vray = check_vertical_walls(data, angle);
	if (vray.len > hray.len)
		return (hray);
	return (vray);
}

t_ray	check_horizontal_walls(t_data *data, float angle)
{
	t_ray	ray;

	ray_init(&ray, data, angle);
	if (sin(angle) != 0 && sin(ray.next_ang) != 0)
		ray_assign_h(data, &ray);
	return (ray);
}

t_ray	check_vertical_walls(t_data *data, float angle)
{
	t_ray	ray;

	ray_init(&ray, data, angle);
	if (cos(angle) != 0 && cos(ray.next_ang) != 0)
		ray_assign_v(data, &ray);
	return (ray);
}

void	ray_assign_h(t_data *data, t_ray *ray)
{
	float	x;
	int		y;
	int		a;
	int		b;

	b = set_texture(data, &a, ray, 's');
	y = (int)data->py + (1 - a);
	while (is_map_coordinates(data, 0, y - a))
	{
		x = data->px + (data->py - y) * tan(PI / 2 - ray->angle);
		if (!is_map_coordinates(data, x, 0))
			break ;
		if (data->map[y - a][(int)x] == '1')
		{
			ray->len = sqrt(pow(x - data->px, 2) + pow(y - data->py, 2));
			ray->part = b * ray->len * (sin(PI3 / RAYS) / sin(ray->next_ang));
			ray->start = b * (x - (int)x) + (1 - a);
			break ;
		}
		y = y - b;
	}
}

void	ray_assign_v(t_data *data, t_ray *ray)
{
	int		a;
	int		b;
	int		x;
	float	y;

	b = set_texture(data, &a, ray, 'c');
	x = (int)data->px + a;
	while (is_map_coordinates(data, x - 1 + a, 0))
	{
		y = data->py - (x - data->px) * tan(ray->angle);
		if (!is_map_coordinates(data, 0, y))
			break ;
		if (data->map[(int)y][x - 1 + a] == '1')
		{
			ray->len = sqrt(pow(x - data->px, 2) + pow(y - data->py, 2));
			ray->part = b * ray->len * (sin(PI3 / RAYS) / cos(ray->next_ang));
			ray->start = b * (y - (int)y) + (1 - a);
			break ;
		}
		x = x + b;
	}
}
