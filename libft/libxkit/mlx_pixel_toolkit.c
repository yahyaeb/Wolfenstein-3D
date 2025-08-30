/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_toolkit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:25:02 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 10:20:21 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	mlx_fast_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pix;

	if ((x >= 0 && x < img->width) && (y >= 0 && y < img->height))
	{
		pix = img->addr + (y * img->l_len) + (x * (img->bpp / 8));
		*(unsigned int *)pix = color;
	}
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	*pixels;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	pixels = (int *)img->addr;
	pixels[y * img->width + x] = color;
}
