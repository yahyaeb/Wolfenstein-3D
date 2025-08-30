/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_grid_toolkit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:47:31 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/25 23:46:29 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	draw_grid(t_state *state)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row <= MINIMAP_MAX_DISPLAYABLE_ROW + 1)
	{
		draw_grid_line_horizontal(state, 0, row);
		row++;
	}
	col = 0;
	while (col <= MINIMAP_MAX_DISPLAYABLE_COL + 1)
	{
		draw_grid_line_vertical(state, col, 0);
		col++;
	}
}

void	draw_grid_line_horizontal(t_state *state, int col, int row)
{
	t_mlx_line	grid_line;
	t_pos		p;

	p.x = ((col) * RES_PIX);
	p.y = ((row) * RES_PIX);
	grid_line.start_x = p.x;
	grid_line.start_y = p.y;
	grid_line.end_x = MINIMAP_MAX_DISPLAYABLE_WIDTH;
	grid_line.end_y = p.y;
	draw_mlx_line(state->env, &grid_line, &state->settings->grid_color);
}

void	draw_grid_line_vertical(t_state *state, int col, int row)
{
	t_mlx_line	grid_line;
	t_pos		p;

	p.x = ((col) * RES_PIX);
	p.y = ((row) * RES_PIX);
	grid_line.start_x = p.x;
	grid_line.start_y = p.y;
	grid_line.end_x = p.x;
	grid_line.end_y = MINIMAP_MAX_DISPLAYABLE_HEIGHT;
	draw_mlx_line(state->env, &grid_line, &state->settings->grid_color);
}
