/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 00:05:15 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:02:43 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_spr	*new_spr(float x, float y, float dist, float angle)
{
	t_spr *newspr;
	float width;
	float ra;

	width = 1;
	ra = atan(width / (2 * dist));
	newspr = (t_spr *)malloc(sizeof(t_spr));
	if (newspr == NULL)
		ft_error(7);
	newspr->x = x + 0.5;
	newspr->y = y + 0.5;
	newspr->dist = dist;
	newspr->width = width;
	newspr->rel_ang = ra;
	newspr->angle = angle;
	newspr->tang = norm_ang(angle + ra);
	newspr->bang = norm_ang(angle - ra);
	newspr->next = NULL;
	return (newspr);
}

int		get_sprite_count(t_spr *lst)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_spr	*get_sprite_w_smaller_dist(t_spr *lst, float dist)
{
	int		i;
	t_spr	*last;
	t_spr	*sprite;

	i = get_sprite_count(lst);
	sprite = lst;
	last = NULL;
	while (i > 0)
	{
		if (sprite->dist > dist)
			last = sprite;
		sprite = sprite->next;
		i--;
	}
	return (last);
}

void	add_spr(t_spr **lst, t_spr *new)
{
	t_spr	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = get_sprite_w_smaller_dist(*lst, new->dist);
		if (last == NULL)
		{
			new->next = *lst;
			*lst = new;
		}
		else
		{
			new->next = last->next;
			last->next = new;
		}
	}
}

void	set_sprites(t_data *data)
{
	int		x;
	int		y;
	float	a1;
	t_ang	ang;

	a1 = norm_ang(data->pa + PI / 6);
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '2')
			{
				ang = fill_ang(data, x, y);
				if (check_angle(ang.ang + ang.rel_ang, a1, a1 - PI3))
					add_spr(&(data->fov_spr), new_spr(x, y, ang.dist, ang.ang));
				if (check_angle(ang.ang - ang.rel_ang, a1, a1 - PI3))
					add_spr(&(data->fov_spr), new_spr(x, y, ang.dist, ang.ang));
			}
			x++;
		}
		y++;
	}
}
