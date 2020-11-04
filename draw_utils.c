/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:20:32 by ppipes            #+#    #+#             */
/*   Updated: 2020/11/04 19:05:39 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ray_init(t_ray *ray, t_data *data, float angle)
{
	ray->next_ang = diff_angle(angle, PI3 / RAYS);
	ray->len = data->map_height * data->map_width;
	ray->angle = angle;
}

void	wall_init(t_wall *wal, t_data *data, t_ray ray)
{
	float	const_wall;

	const_wall = data->height * 1.7;
	wal->height = const_wall / (ray.len * cos(diff_angle(data->pa, ray.angle)));
	wal->height = (int)wal->height >> 1 << 1;
	wal->width = (data->width + RAYS - 1) / RAYS;
	wal->hpart = data->height / wal->height;
	if (wal->hpart > 1)
		wal->hpart = 1;
	wal->hstart = (1 - wal->hpart) / 2;
	wal->marg = (data->height - wal->height) / 2;
	if (wal->marg < 0)
		wal->marg = 0;
	wal->texw = ray.texture->w;
	wal->texh = ray.texture->h;
	wal->texa = ray.texture->addr;
	wal->rayn = ray.number;
	wal->wstart = ray.start;
	wal->wpart = ray.part;
}

void	spr_init(t_wall *spr, t_data *data, t_ray ray, t_spr *spt)
{
	spr->height = (data->height * 1.7) / spt->dist;
	spr->width = (data->width + RAYS - 1) / RAYS;
	spr->wstart = diff_angle(spt->tang, ray.angle) / (2 * spt->rel_ang);
	if (spr->wstart < 0 || spr->wstart >= 1)
		spr->wstart = 0;
	spr->wpart = (PI3 / RAYS) / (2 * spt->rel_ang);
	if (spr->wstart + spr->wpart > 1)
		spr->wpart = 1 - spr->wstart;
	spr->marg = (data->height - spr->height) / 2;
	spr->texw = data->sprite.w;
	spr->texh = data->sprite.h;
	spr->texa = data->sprite.addr;
	spr->rayn = ray.number;
}

void	wall_pix_put(t_data *data, t_wall wal, int ox, int oy)
{
	int		x;
	int		y;
	int		color;
	float	h;

	h = wal.height * wal.hpart;
	x = wal.wstart * wal.texw + ox * wal.wpart * wal.texw / wal.width;
	y = wal.hstart * wal.texh + oy * wal.hpart * wal.texh / h;
	color = wal.texa[y * wal.texw + x];
	my_mlx_pixel_put(data, (wal.rayn * wal.width) + ox, wal.marg + oy, color);
}

int		spr_pix_put(t_data *data, t_wall spr, int ox, int oy)
{
	int x;
	int y;
	int color;

	x = spr.wstart * spr.texw + ox * spr.wpart * spr.texw / spr.width;
	y = oy * spr.texh / spr.height;
	color = spr.texa[y * spr.texw + x];
	if (!color)
		return (1);
	my_mlx_pixel_put(data, (spr.rayn * spr.width) + ox, spr.marg + oy, color);
	return (1);
}
