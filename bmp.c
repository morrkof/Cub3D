/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:45:24 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:54:27 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_bmp_data(t_bmpfile *file, t_bmpinf *img, t_data *data)
{
	file->file_type[0] = 'B';
	file->file_type[1] = 'M';
	file->file_size = 54 + (data->width) * (data->height) * 4;
	file->reserved1 = 0;
	file->reserved2 = 0;
	file->pixel_data_offset = 54;
	img->header_size = 40;
	img->image_width = data->width;
	img->image_height = -data->height;
	img->planes = 0;
	img->bpp = data->bpp;
	img->compression = 0;
	img->image_size = 0;
	img->x_ppm = 0;
	img->y_ppm = 0;
	img->total_colors = 0;
	img->important_colors = 0;
}

void	create_screenshot(t_data *data)
{
	t_bmpfile	file;
	t_bmpinf	img;
	int			fd;
	int			end;
	int			len;

	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp), &len, &end);
	data->end = end;
	data->l_len = len;
	draw_ceil_and_floor(data);
	draw_walls_and_sprites(data);
	init_bmp_data(&file, &img, data);
	fd = open("screenshot.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		ft_error(1);
	write(fd, &file, 14);
	write(fd, &img, 40);
	write(fd, data->addr, data->width * data->height * 4);
	close(fd);
	exit(0);
}
