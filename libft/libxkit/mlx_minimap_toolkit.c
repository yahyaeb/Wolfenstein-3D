/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minimap_toolkit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:47:31 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 17:09:49 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	render_minimap(t_state *state)
{
	int	row;
	int	col;
	int	map_x;
	int	map_y;

	row = 0;
	while (row <= MINIMAP_MAX_DISPLAYABLE_ROW)
	{
		col = 0;
		while (col <= MINIMAP_MAX_DISPLAYABLE_COL)
		{
			map_x = (state->cam->pos.x / RES_PIX) + col;
			map_y = (state->cam->pos.y / RES_PIX) + row;
			if (map_x < state->map->tm_cols && map_y < state->map->tm_rows)
				rm_put_tiles_minimap(state, map_y, map_x, RES_PIX);
			col++;
		}
		row++;
	}
}

void	enforce_minimap_bounds(t_state *state, int *offset_x, int *offset_y)
{
	if (state->map->tm_cols <= MINIMAP_MAX_DISPLAYABLE_COL)
		*offset_x += (MINIMAP_MAX_DISPLAYABLE_WIDTH
				- (state->map->tm_cols * RES_PIX)) / 2;
	if (state->map->tm_rows <= MINIMAP_MAX_DISPLAYABLE_ROW)
		*offset_y += (MINIMAP_MAX_DISPLAYABLE_HEIGHT
				- (state->map->tm_rows * RES_PIX)) / 2;
}

void	check_next_tile(t_state *state, t_mlx_line *line, int row, int col)
{
	char		tile;
	int			nb_subline;

	if (col >= (int)ft_strlen(state->map->tilemap[row]))
		return ;
	tile = state->map->tilemap[row][col];
	nb_subline = 0;
	if (tile == '1' && state->map->wall && state->map->wall->img)
	{
		while (nb_subline < RES_PIX)
		{
			draw_mlx_line(state->env, line, &state->settings->ui_color);
			nb_subline++;
			line->start_y++;
			line->end_y++;
		}
	}
}

void	rm_put_tiles_minimap(t_state *state, int row, int col, int cell_size)
{
	t_pos		p;
	t_mlx_line	line;

	p.x = ((col) * cell_size) - state->cam->pos.x;
	p.y = ((row) * cell_size) - state->cam->pos.y;
	enforce_minimap_bounds(state, &(p.x), &(p.y));
	line.color = state->settings->wall_color;
	line.start_x = p.x;
	line.start_y = p.y;
	line.end_x = line.start_x + cell_size;
	line.end_y = line.start_y;
	check_next_tile(state, &line, row, col);
}
