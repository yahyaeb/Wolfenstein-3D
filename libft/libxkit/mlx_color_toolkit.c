/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color_toolkit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:05:10 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 16:06:49 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	init_mlx_rgb(t_mlx_color *color, int r, int g, int b)
{
	color->t = 0;
	color->r = r;
	color->g = g;
	color->b = b;
}

int	set_color(t_mlx_color *color)
{
	return (color->t << 24 | color->r << 16 | color->g << 8 | color->b);
}

int	get_color(t_mlx_color *color, char param)
{
	if (param == 't')
		return ((color->t >> 24) & 0xFF);
	else if (param == 'r')
		return ((color->r >> 16) & 0xFF);
	else if (param == 'g')
		return ((color->g >> 8) & 0xFF);
	else if (param == 'b')
		return (color->b & 0xFF);
	else
		return (1);
}

int	rev_color(t_mlx_color *color)
{
	color->r = ~(color->r);
	color->g = ~(color->g);
	color->b = ~(color->b);
	return (color->t << 24 | color->r << 16 | color->g << 8 | color->b);
}

void	pass_rgb_colors(int *dst, int *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
}
