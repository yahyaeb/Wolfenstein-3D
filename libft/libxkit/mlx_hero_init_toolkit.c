/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hero_init_toolkit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:52:17 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/27 17:33:44 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

int	init_hero(t_state *state)
{
	t_hero	*hero;
	t_pos	*hero_pos;

	hero = malloc(sizeof(t_hero));	
	if (!hero)
		return (1);
	state->hero = hero;
	hero_pos = malloc(sizeof(t_pos));
	if (!hero_pos)
		return (1);
	state->hero->pos = hero_pos;
	hero->ang = 0;
	set_hero_pos(state);
	hero->dx = cos(hero->ang);
	hero->dy = sin(hero->ang);
	hero->pdx = -hero->dy * 0.5;
	hero->pdy = hero->dx * 0.5;
	return (0);
}

void	set_hero_3d_pos(t_state *state, int row, int col)
{
	state->hero->pos->x = col;
	state->hero->pos->y = row;
	state->hero->pos->fx = (float)col + 0.5;
	state->hero->pos->fy = (float)row + 0.5;
	if (state->map->tilemap[row][col] == 'W')
		state->hero->ang = M_PI;
	else if (state->map->tilemap[row][col] == 'S')
		state->hero->ang = M_PI / 2;
	else if (state->map->tilemap[row][col] == 'E')
		state->hero->ang = 0;
	else if (state->map->tilemap[row][col] == 'N')
		state->hero->ang = 3 * M_PI / 2;
	state->hero->dx = cos(state->hero->ang);
	state->hero->dy = sin(state->hero->ang);
	state->hero->pdx = cos(state->hero->ang) * 5;
	state->hero->pdy = sin(state->hero->ang) * 5;
}

void	set_hero_pos(t_state *state)
{
	int		row;
	int		col;

	row = 0;
	while (row < state->map->tm_rows)
	{
		col = 0;
		while (state->map->tilemap[row][col] != '\0')
		{
			if (state->map->tilemap[row][col] == 'E'
				|| state->map->tilemap[row][col] == 'N'
				|| state->map->tilemap[row][col] == 'S'
				|| state->map->tilemap[row][col] == 'W')
			{
				set_hero_3d_pos(state, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
	return ;
}

int	upload_hero(t_state *state)
{
	int	width;
	int	height;

	state->hero->img = mlx_xpm_file_to_image(state->env->mlx,
			state->hero->img_path, &width, &height);
	if (!state->hero->img)
		return (1);
	state->hero->to_up = mlx_xpm_file_to_image(state->env->mlx,
			state->hero->to_up_path, &width, &height);
	if (!state->hero->to_up)
		return (1);
	state->hero->to_down = mlx_xpm_file_to_image(state->env->mlx,
			state->hero->to_down_path, &width, &height);
	if (!state->hero->to_down)
		return (1);
	state->hero->to_left = mlx_xpm_file_to_image(state->env->mlx,
			state->hero->to_left_path, &width, &height);
	if (!state->hero->to_left)
		return (1);
	state->hero->to_right = mlx_xpm_file_to_image(state->env->mlx,
			state->hero->to_right_path, &width, &height);
	if (!state->hero->to_right)
		return (1);
	return (0);
}
