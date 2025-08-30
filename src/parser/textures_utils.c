/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:01:16 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/27 16:05:20 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	is_a_dot(char *str, t_map_dir *map, int i)
{
	char	*trimmed_path;
	int		fd;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '.')
	{
		trimmed_path = ft_strtrim(&str[i], " \t\n");
		if (!trimmed_path)
			return (-1);
		fd = open(trimmed_path, O_RDONLY);
		if (fd == -1)
		{
			perror("file error\n");
			close(fd);
			free(trimmed_path);
			return (-1);
		}
		if (map->temp)
			free(map->temp);
		map->temp = trimmed_path;
		return (1);
	}
	return (-1);
}

char	*skip_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	is_dir_match(char *str, char *dir, t_map_dir *map)
{
	return (ft_strncmp(str, dir, 2) == 0
		&& str[2] == ' '
		&& is_a_dot(&str[2], map, 0) == 1);
}

int	direction(char *str, t_map_dir *map)
{
	if (is_dir_match(str, "NO", map))
	{
		cpy_dir_path(&(map->no_path), &(map->temp), &(map->no));
		return (dir_count(&map->no));
	}
	if (is_dir_match(str, "WE", map))
	{
		cpy_dir_path(&(map->we_path), &(map->temp), &(map->we));
		return (dir_count(&map->we));
	}
	if (is_dir_match(str, "EA", map))
	{
		cpy_dir_path(&(map->ea_path), &(map->temp), &(map->ea));
		return (dir_count(&map->ea));
	}
	if (is_dir_match(str, "SO", map))
	{
		cpy_dir_path(&(map->so_path), &(map->temp), &(map->so));
		return (dir_count(&map->so));
	}
	return (0);
}

int	dir_count(int *i)
{
	if (*i != 1)
		return (0);
	return (1);
}
