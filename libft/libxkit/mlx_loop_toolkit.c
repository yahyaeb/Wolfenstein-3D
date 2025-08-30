/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_toolkit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:18:37 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/25 23:29:04 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	update_render(t_state *state)
{
	render_background(state);
	render_map(state);
	render_hero(state);
	if (NB_ENEMIES > 0)
		render_enemy(state);
}

void	split_screen(t_state *state)
{
	t_settings	*settings;
	t_mlx_line	line;

	settings = state->settings;
	draw_mlx_rect(state->env, &settings->minimap_screen, &settings->ui_color);
	draw_mlx_rect(state->env, &settings->map_screen, &settings->ui_color);
	draw_mlx_rect(state->env, &settings->ui_screen, &settings->ui_color);
	line.start_x = state->settings->ui_screen.origin_x;
	line.start_y = state->settings->ui_screen.origin_y;
	line.end_x = line.start_x + WIN_WIDTH;
	line.end_y = line.start_y;
	line.color = state->settings->ui_color;
	while (line.start_y < WIN_HEIGHT)
	{
		draw_mlx_line(state->env, &line, &line.color);
		line.start_y += 1;
		line.end_y += 1;
	}
}

void	set_floor_and_ceiling(t_state *state)
{
	t_mlx_line	line;

	line.start_x = state->settings->map_screen.origin_x;
	line.start_y = state->settings->map_screen.origin_y;
	line.end_x = line.start_x + state->settings->map_screen.width;
	line.end_y = line.start_y;
	line.color = state->settings->ceiling_color;
	while (line.start_y < state->settings->map_screen.height
		/ 2 + HORIZON_OFFSET)
	{
		draw_mlx_line(state->env, &line, &line.color);
		line.start_y += 1;
		line.end_y += 1;
	}
	line.color = state->settings->floor_color;
	while (line.start_y < state->settings->map_screen.height)
	{
		draw_mlx_line(state->env, &line, &line.color);
		line.start_y += 1;
		line.end_y += 1;
	}
}

void	clear_canvas(t_img *img)
{
	int	y;

	if (!img || !img->addr)
		return ;
	y = 0;
	if (img->bpp != 32)
	{
		while (y < img->height)
		{
			ft_memset(img->addr + y * img->l_len, 0, img->l_len);
			y++;
		}
		return ;
	}
	while (y < img->height)
	{
		ft_memset(img->addr + y * img->l_len, 0, img->l_len);
		y++;
	}
}

void	update_render_3d(t_state *state)
{
	clear_canvas(state->env->canvas);
	split_screen(state);
	set_floor_and_ceiling(state);
	render_hero_minimap(state);
	render_minimap(state);
	draw_grid(state);
	mlx_put_image_to_window(state->env->mlx,
		state->env->win,
		state->env->canvas->img,
		0, 0);
}
