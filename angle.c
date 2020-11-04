/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:28:17 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 21:51:40 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	norm_ang(float angle)
{
	if (angle < 0)
		return (angle + 2 * PI);
	else if (angle > 2 * PI)
		return (angle - 2 * PI);
	return (angle);
}

char	check_angle(float angle, float left_side, float right_side)
{
	angle = norm_ang(angle);
	left_side = norm_ang(left_side);
	right_side = norm_ang(right_side);
	if (left_side > right_side)
	{
		if (angle <= left_side && angle >= right_side)
			return (1);
		else
			return (0);
	}
	else if (left_side < right_side)
	{
		if (angle <= left_side && angle >= 0)
			return (1);
		else if (angle >= right_side && angle <= 2 * PI)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

float	diff_angle(float a1, float a2)
{
	a1 = norm_ang(a1);
	a2 = norm_ang(a2);
	if (a1 >= a2)
		return (norm_ang(a1 - a2));
	else
		return (norm_ang(2 * PI - a2 + a1));
}

t_ang	fill_ang(t_data *data, float x, float y)
{
	t_ang	ang;

	ang.ang = calc_s_ang(data, x, y);
	ang.dist = calc_s_dist(data, x, y);
	ang.rel_ang = norm_ang(atan(1 / (2 * ang.dist)));
	return (ang);
}

float	calc_s_ang(t_data *data, float x, float y)
{
	float angle;

	x = x + 0.5;
	y = y + 0.5;
	angle = norm_ang(atan2(data->py - y, x - data->px));
	return (angle);
}
