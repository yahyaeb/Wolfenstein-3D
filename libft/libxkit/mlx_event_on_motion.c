/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_on_motion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:19:01 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/27 14:37:24 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

#define MOVE_SPEED 0.09
#define ROTATE_SPEED 0.09

void	on_motion_up(t_state *state)
{
	double	nx;
	double	ny;
	t_hero	*hero;
	char	**tilemap;

	hero = state->hero;
	tilemap = state->map->tilemap;
	nx = hero->pos->fx + hero->dx * MOVE_SPEED;
	ny = hero->pos->fy + hero->dy * MOVE_SPEED;
	if (tilemap[(int)hero->pos->fy][(int)nx] != '1')
		hero->pos->fx = nx;
	if (tilemap[(int)ny][(int)hero->pos->fx] != '1')
		hero->pos->fy = ny;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 1;
	state->data->must_clear_window = 1;
}

void	on_motion_down(t_state *state)
{
	double	nx;
	double	ny;
	t_hero	*hero;
	char	**tilemap;

	hero = state->hero;
	tilemap = state->map->tilemap;
	nx = hero->pos->fx - hero->dx * MOVE_SPEED;
	ny = hero->pos->fy - hero->dy * MOVE_SPEED;
	if (tilemap[(int)hero->pos->fy][(int)nx] != '1')
		hero->pos->fx = nx;
	if (tilemap[(int)ny][(int)hero->pos->fx] != '1')
		hero->pos->fy = ny;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 1;
	state->data->must_clear_window = 1;
}

void	on_motion_left(t_state *state)
{
	double	nx;
	double	ny;
	t_hero	*hero;
	char	**tilemap;

	tilemap = state->map->tilemap;
	hero = state->hero;
	nx = hero->pos->fx - hero->pdx * MOVE_SPEED;
	ny = hero->pos->fy - hero->pdy * MOVE_SPEED;
	if (tilemap[(int)hero->pos->fy][(int)nx] != '1')
		hero->pos->fx = nx;
	if (tilemap[(int)ny][(int)hero->pos->fx] != '1')
		hero->pos->fy = ny;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 3;
	state->data->must_clear_window = 1;
}

void	on_motion_right(t_state *state)
{
	double	nx;
	double	ny;
	t_hero	*hero;
	char	**tilemap;

	tilemap = state->map->tilemap;
	hero = state->hero;
	nx = hero->pos->fx + hero->pdx * MOVE_SPEED;
	ny = hero->pos->fy + hero->pdy * MOVE_SPEED;
	if (tilemap[(int)hero->pos->fy][(int)nx] != '1')
		hero->pos->fx = nx;
	if (tilemap[(int)ny][(int)hero->pos->fx] != '1')
		hero->pos->fy = ny;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 4;
	state->data->must_clear_window = 1;
}
