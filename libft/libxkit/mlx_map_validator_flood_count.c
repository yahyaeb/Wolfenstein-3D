/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map_validator_flood_count.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:40:51 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/25 18:58:16 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	flood_check_enclosure(char **map, int y, int x)
{
	int		row_len;
	char	tile;

	if (y < 0 || map[y] == NULL)
		return (1);
	row_len = ft_strlen(map[y]);
	if (x < 0 || x >= row_len)
		return (1);
	tile = map[y][x];
	if (tile == '1' || tile == 'X')
		return (0);
	if (tile == ' ')
		return (1);
	if (!is_walkable(tile))
		return (1);
	map[y][x] = 'X';
	return (flood_check_enclosure(map, y, x + 1)
		|| flood_check_enclosure(map, y, x - 1)
		|| flood_check_enclosure(map, y + 1, x)
		|| flood_check_enclosure(map, y - 1, x)
	);
}
