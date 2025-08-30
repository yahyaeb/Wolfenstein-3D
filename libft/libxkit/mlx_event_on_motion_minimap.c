/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event_on_motion_minimap.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:19:01 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 15:05:50 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	on_motion_up(t_state *state)
{
	t_pos	*hero_pos;
	char	**tilemap;

	tilemap = state->map->tilemap;
	hero_pos = state->hero->pos;
	if ((int)(hero_pos->fy - 0.1) == hero_pos->y - 1)
	{
		if (tilemap[hero_pos->y - 1][hero_pos->x] == '1')
			return ;
		else
			hero_pos->y -= 1;
	}
	hero_pos->fy -= 0.1;
	(state->data->nb_steps)++;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 1;
	state->data->must_clear_window = 1;
}

void	on_motion_down(t_state *state)
{
	char	**tilemap;
	t_pos	*hero_pos;

	tilemap = state->map->tilemap;
	hero_pos = state->hero->pos;
	if ((int)(hero_pos->fy + 0.1) == hero_pos->y + 1)
	{
		if (tilemap[hero_pos->y + 1][hero_pos->x] == '1')
			return ;
		else
			hero_pos->y += 1;
	}
	hero_pos->fy += 0.1;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 2;
	state->data->must_clear_window = 1;
}

void	on_motion_left(t_state *state)
{
	char	**tilemap;
	t_pos	*hero_pos;

	tilemap = state->map->tilemap;
	hero_pos = state->hero->pos;
	if ((int)(hero_pos->fx - 0.1) == hero_pos->x - 1)
	{
		if (tilemap[hero_pos->y][hero_pos->x - 1] == '1')
			return ;
		else
			hero_pos->x -= 1;
	}
	hero_pos->fx -= 0.1;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 3;
	state->data->must_clear_window = 1;
}

void	on_motion_right(t_state *state)
{
	char	**tilemap;
	t_pos	*hero_pos;

	tilemap = state->map->tilemap;
	hero_pos = state->hero->pos;
	if ((int)(hero_pos->fx + 0.1) == hero_pos->x + 1)
	{
		if (tilemap[hero_pos->y][hero_pos->x + 1] == '1')
			return ;
		else
			hero_pos->x += 1;
	}
	hero_pos->fx += 0.1;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 4;
	state->data->must_clear_window = 1;
}

/*void	on_motion_up(t_state *state)
{
	state->hero->pos->y -= 1;
	(state->data->nb_steps)++;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 1;
}

void	on_motion_down(t_state *state)
{
	state->hero->pos->y += 1;
	(state->data->nb_steps)++;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 2;
}

void	on_motion_left(t_state *state)
{
	state->hero->pos->x -= 1;
	(state->data->nb_steps)++;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 3;
}

void	on_motion_right(t_state *state)
{
	state->hero->pos->x += 1;
	(state->data->nb_steps)++;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	state->render_event = 3;
	state->hero->frame = 4;
}*/
