/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:25:02 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/27 16:08:27 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
/*
 * So_long uses my library LIBXKIT, based on the graphics library MiniLibX.
 * This smallfree_map_dir game engine handles 2D collecting top-view games.
 * LIBXKIT, though, can be used for various types of projects.
 */

int	launcher(t_state *state, t_data *data, char fpath[256], t_map_dir *map_dir)
{
	pass_rgb_colors(state->c_rgb, map_dir->c_rgb);
	pass_rgb_colors(state->f_rgb, map_dir->f_rgb);
	init_data(state, data, 1);
	if ((init_map(state, fpath, ".cub") != 0)
		|| copy_tilemap(state->map->tilemap, map_dir->tilemap,
			map_dir, state) != 0
		|| (map_parser(state) != 0)
		|| (set_state(state) != 0))
	{
		free_map_dir(map_dir);
		sl_memfree(state);
		return (1);
	}
	if (load_wall_textures(state->settings, map_dir, state->env->mlx))
		return (1);
	display_start_screen();
	free_map_dir(map_dir);
	init_data(state, state->data, 2);
	return (0);
}

int	check_requirements(t_state *state, char **tilemap, size_t nb_lines,
		t_count_req *c)
{
	int	i;
	int	player_count;

	check_count(tilemap, nb_lines, "01NSEW \n", c);
	player_count = c->count[2] + c->count[3] + c->count[4] + c->count[5];
	if (player_count != 1)
	{
		ft_printf("Error: Map must have only one start (S/W/E/N)\n");
		return (1);
	}
	if (check_chars(tilemap, nb_lines, "01NSEW \t\n") != 0)
		return (1);
	if (flood_check_enclosure(tilemap, state->hero->pos->y,
			state->hero->pos->x))
	{
		ft_printf("Error: Map is not surrounded by walls\n");
		return (1);
	}
	i = 0;
	while (i < 6)
	{
		state->map->tile_count[i] = c->count[i];
		i++;
	}
	return (0);
}

void	set_minimap(t_state *state)
{
	state->settings = malloc(sizeof(t_settings));
	if (!state->settings)
		return ;
	init_mlx_rgb(&state->settings->hero_color, 255, 255, 0);
	state->settings->hero_dot.radius = 5;
	init_mlx_rgb(&state->settings->ray_color, 0, 255, 0);
	init_mlx_rgb(&state->settings->grid_color, 55, 55, 55);
	init_mlx_rgb(&state->settings->wall_color, 255, 0, 0);
	init_mlx_rgb(&state->settings->wall_color_shaded, 255 * 0.5, 0, 0);
	init_mlx_rgb(&state->settings->floor_color, state->f_rgb[0],
		state->f_rgb[1], state->f_rgb[2]);
	init_mlx_rgb(&state->settings->ceiling_color, state->c_rgb[0],
		state->c_rgb[1], state->c_rgb[2]);
}

void	set_ui(t_settings *settings)
{
	settings->ui_color.t = 0;
	init_mlx_rgb(&settings->ui_color, 0, 78, 124);
	settings->minimap_screen.origin_x = 0;
	settings->minimap_screen.origin_y = 0;
	settings->minimap_screen.height = WIN_HEIGHT - (RES_PIX * 2);
	settings->minimap_screen.width = HALF_WIN_WIDTH + 10;
	settings->map_screen.origin_x = HALF_WIN_WIDTH + 10;
	settings->map_screen.origin_y = 0;
	settings->map_screen.height = WIN_HEIGHT - (RES_PIX * 2);
	settings->map_screen.width = HALF_WIN_WIDTH - 10;
	settings->ui_screen.origin_x = 0;
	settings->ui_screen.origin_y = WIN_HEIGHT - (RES_PIX * 2);
	settings->ui_screen.height = WIN_HEIGHT - (RES_PIX * 2) - 1;
	settings->ui_screen.width = WIN_WIDTH - 1;
}

int	init_data(t_state *state, t_data *data, int step)
{
	if (step == 1)
	{
		set_minimap(state);
		set_ui(state->settings);
		data->collected = 0;
		data->nb_steps = 0;
		state->data = data;
		state->current_frame = 0;
		state->data->must_clear_window = 1;
	}
	else if (step == 2)
	{
		state->error_code = 5;
		state->hero->frame = 0;
		if (NB_ENEMIES > 0)
			set_enemy_pos(state);
		state->render_event = 3;
	}
	return (0);
}
