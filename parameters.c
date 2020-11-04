/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:05:58 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:25:40 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_parameters(int fd, t_data *data)
{
	t_flags	flags;

	data->map_list = NULL;
	data->width = 0;
	data->height = 0;
	mlx_do_key_autorepeaton(data->mlx);
	flags_init(&flags);
	read_lines(data, fd, &flags);
	fill_map(data);
	check_player(data, &flags);
	validate_map(data);
	check_flags(&flags);
	close(fd);
}

void	flags_init(t_flags *flags)
{
	flags->width = 0;
	flags->height = 0;
	flags->resolution = 0;
	flags->ceil_color = 0;
	flags->floor_color = 0;
	flags->r_color = 0;
	flags->g_color = 0;
	flags->b_color = 0;
	flags->no_texture = 0;
	flags->so_texture = 0;
	flags->ea_texture = 0;
	flags->we_texture = 0;
	flags->sprite_texture = 0;
	flags->map = 0;
	flags->player = 0;
}

void	read_lines(t_data *data, int fd, t_flags *flags)
{
	char	*line;
	int		i;

	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0' && !flags->map)
			i = i;
		else if (ft_isalpha(line[i]))
			sort_line(line, data, flags, i);
		else if (line[i] == '1')
		{
			ft_lstadd_back(&(data->map_list), ft_lstnew(ft_strdup(line)));
			flags->map = 1;
		}
		else
			ft_error(3);
		free(line);
	}
	ft_lstadd_back(&(data->map_list), ft_lstnew(ft_strdup(line)));
	free(line);
}

void	sort_line(char *line, t_data *data, t_flags *flags, int i)
{
	if (line[i] == 'R' && line[i + 1] == ' ' && !flags->resolution)
		fill_resolution(line, data, flags);
	else if (line[i] == 'F' && line[i + 1] == ' ' && !flags->floor_color)
		data->floor_color = fill_color(line, flags, &flags->floor_color);
	else if (line[i] == 'C' && line[i + 1] == ' ' && !flags->ceil_color)
		data->ceil_color = fill_color(line, flags, &flags->ceil_color);
	else if (line[i] == 'N' && line[i + 1] == 'O' && !flags->no_texture)
		fill_file_path(line, &(data->north), &(flags->no_texture));
	else if (line[i] == 'S' && line[i + 1] == 'O' && !flags->so_texture)
		fill_file_path(line, &(data->south), &(flags->so_texture));
	else if (line[i] == 'E' && line[i + 1] == 'A' && !flags->ea_texture)
		fill_file_path(line, &(data->east), &(flags->ea_texture));
	else if (line[i] == 'W' && line[i + 1] == 'E' && !flags->we_texture)
		fill_file_path(line, &(data->west), &(flags->we_texture));
	else if (line[i] == 'S' && !flags->sprite_texture)
		fill_file_path(line, &(data->sprite), &(flags->sprite_texture));
	else
		ft_error(3);
}

void	check_flags(t_flags *flags)
{
	if (!flags->resolution)
		ft_error(4);
	if (!flags->floor_color || !flags->ceil_color)
		ft_error(5);
	if (!flags->no_texture || !flags->so_texture)
		ft_error(6);
	if (!flags->ea_texture || !flags->we_texture || !flags->sprite_texture)
		ft_error(6);
	if (!flags->map || !flags->player)
		ft_error(3);
}
