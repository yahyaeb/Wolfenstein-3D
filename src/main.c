/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:08:00 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/27 15:56:23 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
/*
 * So_long uses my library LIBXKIT, based on the graphics library MiniLibX.
 * This small game engine handles 2D collecting top-view games.
 * LIBXKIT, though, can be used for various types of projects.
 */

int	main(int argc, char **argv)
{
	t_state		*state;
	t_data		data;
	char		fpath[256];
	t_map_dir	map_dir;

	if (argc != 2)
		return (ft_err(1, "Error\n[main] Invalid input! ❌\n"));
	if (init_state(&state) != 0)
		return (1);
	ft_strlcpy(fpath, argv[1], ft_strlen(argv[1]) + 1);
	if (parse_config_file(argv[1], &map_dir) != 0)
	{
		ft_gnl(-1);
		free_map_dir(&map_dir);
		sl_memfree(state);
		return (1);
	}
	if (launcher(state, &data, fpath, &map_dir) != 0)
		return (1);
	mlx_loop_hook(state->env->mlx, &render_3d, state);
	mlx_loop(state->env->mlx);
	free_wall_textures(state->env->mlx, state->settings);
	return (0);
}

int	map_parser(t_state *state)
{
	char		**tilemap;
	t_count_req	counter;
	size_t		nb_lines;

	state->error_code = 2;
	set_counter_req(&counter);
	tilemap = state->map->tilemap;
	nb_lines = state->map->tm_rows;
	if (init_hero(state) != 0)
		return (1);
	if (check_requirements(state, tilemap, nb_lines, &counter) != 0)
		return (1);
	return (0);
}

void	set_counter_req(t_count_req *counter)
{
	int	count[6];
	int	req_count[6];
	int	i;

	req_count[0] = 0;
	req_count[1] = 0;
	req_count[2] = -1;
	req_count[3] = -1;
	req_count[4] = -1;
	req_count[5] = -1;
	ft_memset(count, 0, sizeof(count));
	i = 0;
	while (i < 6)
	{
		counter->count[i] = count[i];
		counter->req[i] = req_count[i];
		i++;
	}
	return ;
}

int	render_3d(t_state *state)
{
	t_pos	*pos;

	if (state->current_frame == FRAME_RATE)
	{
		pos = state->hero->pos;
		if (state->data->must_clear_window == 1)
		{
			state->data->must_clear_window = 0;
			update_render_3d(state);
		}
		if (state->map->tilemap[pos->y][pos->x] == 'C')
		{
			if (on_coll_tile(state, pos))
				return (1);
		}
		else if (state->map->tilemap[pos->y][pos->x] == 'E')
			on_exit_tile(state);
		state->render_event = 0;
		state->current_frame = 0;
	}
	else
		(state->current_frame)++;
	return (0);
}
