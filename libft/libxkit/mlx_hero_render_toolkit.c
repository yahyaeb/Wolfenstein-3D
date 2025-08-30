/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hero_render_toolkit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:03:38 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/25 13:46:48 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

/* If the map is smaller than the window, it will be centered.
 * The hero position is set accordingly.
 */
void	render_hero(t_state *state)
{
	t_env	*env;
	void	*hero_sprite;
	t_pos	hero_pos;

	env = state->env;
	if (state->hero->frame == 0)
		hero_sprite = state->hero->img;
	if (state->hero->frame == 1)
		hero_sprite = state->hero->to_up;
	if (state->hero->frame == 2)
		hero_sprite = state->hero->to_down;
	if (state->hero->frame == 3)
		hero_sprite = state->hero->to_left;
	if (state->hero->frame == 4)
		hero_sprite = state->hero->to_right;
	hero_pos.x = (state->hero->pos->x * RES_PIX) - (state->cam->pos.x);
	hero_pos.y = (state->hero->pos->y * RES_PIX) - (state->cam->pos.y);
	if (state->map->tm_cols * RES_PIX <= WIN_WIDTH)
		hero_pos.x += (WIN_WIDTH - (state->map->tm_cols * RES_PIX)) / 2;
	if (state->map->tm_rows * RES_PIX <= WIN_HEIGHT)
		hero_pos.y += (WIN_HEIGHT - (state->map->tm_rows * RES_PIX)) / 2;
	mlx_put_image_to_window(env->mlx, env->win,
		hero_sprite, hero_pos.x, hero_pos.y);
}

void	render_hero_minimap(t_state *state)
{
	t_mlx_circle	*hero_dot;
	t_mlx_line		*hero_line;
	int				off_x;
	int				off_y;

	hero_dot = &state->settings->hero_dot;
	hero_line = &state->settings->hero_line;
	off_x = 0;
	off_y = 0;
	enforce_minimap_bounds(state, &off_x, &off_y);
	hero_dot->center_x = (int)(off_x + (state->hero->pos->fx * RES_PIX)
			- state->cam->pos.fx);
	hero_dot->center_y = (int)(off_y + (state->hero->pos->fy * RES_PIX)
			- state->cam->pos.fy);
	hero_line->start_x = hero_dot->center_x;
	hero_line->start_y = hero_dot->center_y;
	hero_line->end_x = hero_line->start_x + (5 + 10) * cosf(state->hero->ang);
	hero_line->end_y = hero_line->start_y + (5 + 10) * sinf(state->hero->ang);
	draw_mlx_circle(state->env, hero_dot, &state->settings->hero_color);
	draw_mlx_line(state->env, hero_line, &state->settings->hero_color);
	render_hero_raycast(state, state->cam, hero_line);
}
