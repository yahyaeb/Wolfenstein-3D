/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:10:01 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 15:16:36 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	render_hero_raycast(t_state *state, t_cam *cam, t_mlx_line *hero_line)
{
	t_ray	ray;
	int		off_x;
	int		off_y;

	off_x = 0;
	off_y = 0;
	enforce_minimap_bounds(state, &off_x, &off_y);
	ray.origin.fx = state->hero->pos->fx;
	ray.origin.fy = state->hero->pos->fy;
	hero_line->start_x = (int)(off_x + (state->hero->pos->fx * RES_PIX)
			- cam->pos.fx);
	hero_line->start_y = (int)(off_y + (state->hero->pos->fy * RES_PIX)
			- cam->pos.fy);
	state->settings->hero_line.start_x = hero_line->start_x;
	state->settings->hero_line.start_y = hero_line->start_y;
	cam->ang = state->hero->ang;
	cam->dir_x = cosf(cam->ang);
	cam->dir_y = sinf(cam->ang);
	cam->plane_scale = tanf(FOV * 0.5f);
	cam->plane_x = -cam->dir_y * cam->plane_scale;
	cam->plane_y = cam->dir_x * cam->plane_scale;
	cast_all_rays(state, cam, &ray, 0);
}

void	cast_all_rays(t_state *state, t_cam *cam, t_ray *ray, int start_col)
{
	float	cam_x;
	float	rdx;
	float	rdy;
	float	ray_angle;

	while (start_col < NB_RAYS_CAST)
	{
		cam_x = 2.0f * (float)start_col / (float)NB_RAYS_CAST - 1.0f;
		rdx = cam->dir_x + cam->plane_x * cam_x;
		rdy = cam->dir_y + cam->plane_y * cam_x;
		ray_angle = atan2f(rdy, rdx);
		set_ray(ray, &ray->origin, ray_angle, state->settings->ray_color);
		calc_step(ray, &ray->origin, &ray->pos);
		dda_algorithm(ray, &ray->pos, state->map);
		draw_ray(state, ray, start_col);
		start_col++;
	}
}

void	draw_ray(t_state *state, t_ray *ray, int col)
{
	float	raw_t;
	float	angle_diff;

	if (ray->side == 0)
		raw_t = (ray->pos.x - ray->origin.fx
				+ (1 - ray->step_x) * 0.5f) / ray->dir_x;
	else
		raw_t = (ray->pos.y - ray->origin.fy
				+ (1 - ray->step_y) * 0.5f) / ray->dir_y;
	angle_diff = ray->angle - state->hero->ang;
	ray->perp_dist = raw_t * cosf(angle_diff);
	if (ray->perp_dist < 0.05f)
		ray->perp_dist = 0.05f;
	ray->raw_dist = raw_t;
	ray->line.start_x = state->settings->hero_line.start_x;
	ray->line.start_y = state->settings->hero_line.start_y;
	ray->line.end_x = ray->line.start_x + ray->dir_x * raw_t * RES_PIX;
	ray->line.end_y = ray->line.start_y + ray->dir_y * raw_t * RES_PIX;
	cast_3d_line(state, ray, col);
	if (ray->line.end_x > MINIMAP_MAX_DISPLAYABLE_WIDTH)
		ray->line.end_x = MINIMAP_MAX_DISPLAYABLE_WIDTH;
	if (ray->line.end_y > MINIMAP_MAX_DISPLAYABLE_HEIGHT)
		ray->line.end_y = MINIMAP_MAX_DISPLAYABLE_HEIGHT;
	draw_mlx_line(state->env, &ray->line, &ray->color);
}

void	draw_texture(t_state *state, t_img *tex, int col, int start_y)
{
	int	end_y;
	int	d;
	int	tex_y;
	int	color;

	end_y = start_y + state->settings->line_height;
	if (end_y > (WIN_HEIGHT - UI_HEIGHT))
		end_y = (WIN_HEIGHT - UI_HEIGHT);
	while (start_y < end_y)
	{
		d = start_y * 256 - WIN_HEIGHT * 128
			+ state->settings->line_height * 128;
		tex_y = ((d * tex->height) / state->settings->line_height) / 256;
		if (tex_y < 0 || tex_y >= tex->height)
		{
			start_y++;
			continue ;
		}
		color = ((int *)tex->addr)[tex_y
			* tex->width + state->settings->tex_x];
		my_pixel_put(state->env->canvas,
			col + state->settings->offset_x, start_y, color);
		start_y++;
	}
}

void	cast_3d_line(t_state *state, t_ray *ray, int col)
{
	float	dist;
	t_img	*tex;
	int		start_y;

	state->settings->offset_x = (WIN_WIDTH / 2) + 10;
	state->settings->offset_y = 20;
	dist = fabsf(ray->perp_dist);
	if (dist < 1e-6f)
		dist = 1e-6f;
	state->settings->line_height = (int)(WIN_HEIGHT / dist);
	tex = set_texture(state, ray);
	start_y = (WIN_HEIGHT - state->settings->line_height) / 2;
	if (start_y < 0)
		start_y = 0;
	draw_texture(state, tex, col, start_y);
}
