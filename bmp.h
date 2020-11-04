/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 18:32:03 by ppipes            #+#    #+#             */
/*   Updated: 2020/10/26 12:31:12 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# pragma pack(push, 1)

typedef struct			s_bmpfile
{
	char				file_type[2];
	unsigned int		file_size;
	unsigned short int	reserved1;
	unsigned short int	reserved2;
	unsigned int		pixel_data_offset;

}						t_bmpfile;

typedef struct			s_bmpinf
{
	unsigned int		header_size;
	int					image_width;
	int					image_height;
	unsigned short int	planes;
	unsigned short int	bpp;
	unsigned int		compression;
	unsigned int		image_size;
	int					x_ppm;
	int					y_ppm;
	unsigned int		total_colors;
	unsigned int		important_colors;
}						t_bmpinf;

# pragma pack(pop)
#endif
