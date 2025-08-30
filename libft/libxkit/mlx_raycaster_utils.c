/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_raycaster_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:46:52 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 15:27:49 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

#include <math.h>

void	set_ray(t_ray *ray, t_pos *origin, float angle, t_mlx_color color)
{
	ray->angle = angle;
	ray->color = color;
	ray->dir_x = cosf(angle);
	ray->dir_y = sinf(angle);
	ray->pos.x = (int)floorf(origin->fx);
	ray->pos.y = (int)floorf(origin->fy);
	ray->delta_dist_x = fabsf(1.0f / ray->dir_x);
	ray->delta_dist_y = fabsf(1.0f / ray->dir_y);
}

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	calc_step(t_ray *ray, t_pos *origin, t_pos *pos)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (origin->fx - pos->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = +1;
		ray->side_dist_x = (pos->x + 1.0f - origin->fx) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (origin->fy - pos->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = +1;
		ray->side_dist_y = (pos->y + 1.0f - origin->fy) * ray->delta_dist_y;
	}
}

// side = 0 : vertical wall | side = 1 : horizontal wall
void	dda_algorithm(t_ray *ray, t_pos *pos, t_map *map)
{
	int	has_reached_wall;

	has_reached_wall = 0;
	while (!has_reached_wall)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			pos->x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			pos->y += ray->step_y;
			ray->side = 1;
		}
		if (pos->x < 0 || pos->x >= map->tm_cols
			|| pos->y < 0 || pos->y >= map->tm_rows
			|| map->tilemap[pos->y][pos->x] == '1')
			has_reached_wall = 1;
	}
}

t_img	*set_texture(t_state *state, t_ray *ray)
{
	t_img	*tex;

	if (ray->side == 0)
	{
		if ((ray->dir_x > 0))
			tex = state->settings->east_tex;
		else
			tex = state->settings->west_tex;
	}
	else if ((ray->dir_y > 0))
		tex = state->settings->south_tex;
	else
		tex = state->settings->north_tex;
	if (ray->side == 0)
		state->settings->wall_x = ray->origin.fy + ray->raw_dist * ray->dir_y;
	else
		state->settings->wall_x = ray->origin.fx + ray->raw_dist * ray->dir_x;
	state->settings->wall_x -= floor(state->settings->wall_x);
	state->settings->tex_x = (int)(state->settings->wall_x
			* (double)(tex->width));
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		state->settings->tex_x = tex->width
			- state->settings->tex_x - 1;
	return (tex);
}
