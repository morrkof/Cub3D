/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:59:34 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 22:18:50 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	open_textures(t_data *data)
{
	t_tex	*north;
	t_tex	*south;
	t_tex	*east;
	t_tex	*west;
	t_tex	*sprite;

	north = &(data->north);
	south = &(data->south);
	east = &(data->east);
	west = &(data->west);
	sprite = &(data->sprite);
	north->img = get_xpm(data, north);
	north->addr = get_addr(north->img, data);
	south->img = get_xpm(data, south);
	south->addr = get_addr(south->img, data);
	east->img = get_xpm(data, east);
	east->addr = get_addr(east->img, data);
	west->img = get_xpm(data, west);
	west->addr = get_addr(west->img, data);
	sprite->img = get_xpm(data, sprite);
	sprite->addr = get_addr(sprite->img, data);
}

int		*get_addr(void *img, t_data *data)
{
	int *addr;
	int *bpp;
	int *len;
	int *end;

	bpp = &(data->bpp);
	len = &(data->l_len);
	end = &(data->end);
	addr = (int *)mlx_get_data_addr(img, bpp, len, end);
	return (addr);
}

void	*get_xpm(t_data *data, t_tex *side)
{
	void *img;

	img = mlx_xpm_file_to_image(data->mlx, side->path, &(side->w), &(side->h));
	free(side->path);
	return (img);
}

void	fill_file_path(char *line, t_tex *side, int *flag)
{
	int		fd;
	char	*trim;
	char	*tmp;

	trim = ft_strtrim(line, " ");
	tmp = trim;
	trim = trim + 2;
	side->path = ft_strtrim(trim, " ");
	*flag = 1;
	free(tmp);
	if ((fd = open(side->path, O_RDONLY)) == -1)
		ft_error(6);
	close(fd);
}

int		set_texture(t_data *data, int *a, t_ray *ray, char c)
{
	*a = 0;
	if (c == 's')
	{
		ray->texture = &(data->north);
		if (sin(ray->angle) > 0)
		{
			*a = 1;
			ray->texture = &(data->south);
		}
	}
	else if (c == 'c')
	{
		ray->texture = &(data->east);
		if (cos(ray->angle) > 0)
		{
			*a = 1;
			ray->texture = &(data->west);
		}
	}
	return (*a * (*a + 1) - 1);
}
