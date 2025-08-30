/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:15:22 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/26 21:54:37 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_color(char *color)
{
	if (color)
		free(color);
}

void	free_map_dir(t_map_dir *map)
{
	int	i;

	i = 0;
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->we_path)
		free(map->we_path);
	if (map->temp)
		free(map->temp);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->tilemap)
	{
		while (map->tilemap[i])
			free(map->tilemap[i++]);
		free(map->tilemap);
		map->tilemap = NULL;
	}
}

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
