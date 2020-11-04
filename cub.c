/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:07:30 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/31 23:02:31 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < data->width && y < data->height)
	{
		dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void	ft_error(int error)
{
	static	char *message[8] = {"     :wrong arguments (0)",
	"     :can't open the file (1)", "     :failed to create window (2)",
	"     :invalid map (3)", "     :invalid resolution (4)",
	"     :invalid color (5)", "     :invalid texture (6)",
	"     :memory allocation error (7)"};

	write(2, "Error\n", 6);
	write(2, message[error], ft_strlen(message[error]));
	write(2, "\n", 1);
	exit(0);
}

void	clear_sprites(t_spr **lst)
{
	t_spr *nxt;
	t_spr *cur;

	cur = *lst;
	while (cur != NULL)
	{
		nxt = cur->next;
		free(cur);
		cur = nxt;
	}
	*lst = NULL;
}

int		main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (!(data.mlx = mlx_init()))
		ft_error(2);
	if (argc < 2 || argc > 3)
		ft_error(0);
	check_ext(argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(1);
	fill_parameters(fd, &data);
	open_textures(&data);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 6)) == 0)
		create_screenshot(&data);
	else if (argc == 3)
		ft_error(0);
	if (!(data.win = mlx_new_window(data.mlx, data.width, data.height, "cub")))
		ft_error(2);
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_len, &data.end);
	mlx_hook(data.win, 17, 1Lu << 17u, ft_exit, NULL);
	mlx_hook(data.win, 2, 1L << 0, ft_keys_walk, &data);
	mlx_key_hook(data.win, esc_key, &data);
	refresh(&data);
	mlx_loop(data.mlx);
}
