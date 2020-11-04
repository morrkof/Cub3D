/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:54:45 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:16:18 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_map(t_data *data)
{
	int		i;
	t_list	*temp;

	temp = data->map_list;
	data->map_height = ft_lstsize(data->map_list);
	data->map_width = 0;
	i = 0;
	data->map_width = get_max_str(temp);
	if (!(data->map = malloc(sizeof(char *) * data->map_height)))
		ft_error(7);
	temp = data->map_list;
	while (temp != NULL)
	{
		if (!(data->map[i] = malloc(data->map_width)))
			ft_error(7);
		ft_memset(data->map[i], ' ', data->map_width);
		ft_strcpy(data->map[i], temp->content);
		i++;
		temp = temp->next;
	}
	ft_lstclear(&(data->map_list), free);
}

void	validate_map(t_data *data)
{
	char	**map;
	char	*set;
	char	*inner;
	int		x;
	int		y;

	map = data->map;
	set = " 012NSWE";
	inner = "02NSWE";
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!(ft_memchr(set, map[y][x], 8)))
				ft_error(3);
			if (ft_memchr(inner, map[y][x], 6))
			{
				check_cell(data, x, y);
			}
			x++;
		}
		y++;
	}
}

void	check_cell(t_data *data, int x, int y)
{
	int ox;
	int oy;

	ox = x - 1;
	oy = y - 1;
	while (oy <= (y + 1))
	{
		ox = x - 1;
		while (ox <= (x + 1))
		{
			if (!(is_map_coordinates(data, ox, oy)))
				ft_error(3);
			if (data->map[oy][ox] == ' ')
				ft_error(3);
			ox++;
		}
		oy++;
	}
}

void	check_player_angle(t_data *data, int x, int y)
{
	char **tmp;

	tmp = data->map;
	if (tmp[y][x] == 'N')
		data->pa = PI / 2;
	else if (tmp[y][x] == 'S')
		data->pa = 3 * PI / 2;
	else if (tmp[y][x] == 'W')
		data->pa = PI;
	else if (tmp[y][x] == 'E')
		data->pa = 0;
	else
		ft_error(3);
}

void	check_player(t_data *data, t_flags *flags)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (ft_isalpha(data->map[y][x]) && flags->player)
				ft_error(3);
			if (ft_isalpha(data->map[y][x]) && !flags->player)
			{
				data->px = x;
				data->py = y;
				flags->player = 1;
				check_player_angle(data, x, y);
			}
			x++;
		}
		y++;
	}
}
