/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_camera_toolkit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:37:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/24 17:21:41 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

int	set_cam(t_state *state)
{
	state->cam = malloc(sizeof(t_cam));
	if (!state->cam)
		return (ft_err(1, "Error\nmalloc cam fail ❌\n"));
	state->cam->pos.x = 0;
	state->cam->pos.y = 0;
	state->cam->pos.fx = 0;
	state->cam->pos.fy = 0;
	state->cam->max.fx = (state->map->tm_cols * RES_PIX)
		- MINIMAP_MAX_DISPLAYABLE_WIDTH - RES_PIX;
	if (state->cam->max.fx < 0)
		state->cam->max.fx = 0;
	state->cam->max.fy = (state->map->tm_rows * RES_PIX)
		- MINIMAP_MAX_DISPLAYABLE_HEIGHT;
	if (state->cam->max.fy < 0)
		state->cam->max.fy = 0;
	state->cam->max.x = (int)state->cam->max.fx;
	state->cam->max.y = (int)state->cam->max.fy;
	center_cam_on_hero(state->cam, state->hero->pos, state->env);
	return (0);
}

void	center_cam_on_hero(t_cam *cam, t_pos *hero_pos, t_env *env)
{
	int	minimap_screen_width;
	int	minimap_screen_height;

	(void)env;
	minimap_screen_width = WIN_WIDTH / 2 + 5;
	minimap_screen_height = WIN_HEIGHT - RES_PIX * 2;
	cam->pos.fx = hero_pos->fx * RES_PIX - (minimap_screen_width * 0.5f);
	cam->pos.fy = hero_pos->fy * RES_PIX - (minimap_screen_height * 0.5f);
	cam->pos.x = (int)floorf(cam->pos.fx);
	cam->pos.y = (int)floorf(cam->pos.fy);
	check_cam_bounds(cam, env);
}

void	check_cam_bounds(t_cam *cam, t_env *env)
{
	env++;
	env--;
	if (cam->pos.x < 0)
		cam->pos.x = 0;
	if (cam->pos.y < 0)
		cam->pos.y = 0;
	if (cam->pos.x > cam->max.x)
		cam->pos.x = cam->max.x;
	if (cam->pos.y > cam->max.y)
		cam->pos.y = cam->max.y;
	if (cam->pos.fx < 0)
		cam->pos.fx = 0;
	if (cam->pos.fy < 0)
		cam->pos.fy = 0;
	if (cam->pos.fx > cam->max.fx)
		cam->pos.fx = cam->max.fx;
	if (cam->pos.fy > cam->max.fy)
		cam->pos.fy = cam->max.fy;
}

void	update_cam_pos_f(t_cam *cam, float y_move, float x_move, t_env *env)
{
	if (y_move != 0)
		cam->pos.fy += y_move * RES_PIX;
	if (x_move != 0)
		cam->pos.fx += x_move * RES_PIX;
	check_cam_bounds(cam, env);
}

void	update_cam_pos(t_cam *cam, int y_move, int x_move, t_env *env)
{
	if (y_move != 0)
		cam->pos.y += y_move * RES_PIX;
	if (x_move != 0)
		cam->pos.x += x_move * RES_PIX;
	check_cam_bounds(cam, env);
}
