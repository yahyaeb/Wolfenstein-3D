/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:00:06 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/26 17:46:53 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	parse_config_lines(int fd, t_map_dir *map_dir, char **first_map_line)
{
	int		counter;
	int		result;
	char	*next_line;

	result = 0;
	counter = 0;
	next_line = get_next_nonblank_line(fd);
	while (next_line && counter < 6)
	{
		counter++;
		result = handle_config_line(next_line, counter, map_dir);
		free(next_line);
		if (result != 2)
			return (result);
		next_line = get_next_nonblank_line(fd);
	}
	*first_map_line = next_line;
	return (0);
}

void	tab_to_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

int	append_map_line(char ***tilemap, int *count, int *capacity, char *line)
{
	char	**new_tilemap;
	int		i;

	i = 0;
	if (*count >= *capacity)
	{
		*capacity *= 2;
		new_tilemap = realloc(*tilemap, sizeof(char *) * (*capacity));
		if (!new_tilemap)
		{
			while (i < *count)
				free((*tilemap)[i++]);
			free(*tilemap);
			return (-1);
		}
		*tilemap = new_tilemap;
	}
	tab_to_spaces(line);
	(*tilemap)[(*count)++] = line;
	return (0);
}

int	handle_map_content(int fd, char *first_map_line, t_map_dir *map_dir)
{
	int		capacity;
	int		count;
	char	**tilemap;
	char	*line;

	capacity = 16;
	count = 0;
	line = first_map_line;
	tilemap = malloc(sizeof(char *) * capacity);
	if (!tilemap)
		return (-1);
	while (line)
	{
		if (append_map_line(&tilemap, &count, &capacity, line) != 0)
			return (-1);
		line = ft_gnl(fd);
	}
	tilemap = realloc(tilemap, sizeof(char *) * (count + 1));
	tilemap[count] = NULL;
	map_dir->tilemap = tilemap;
	map_dir->map_height = count;
	return (0);
}

int	parse_config_file(const char *file_path, t_map_dir *map_dir)
{
	int		fd;
	int		result;
	char	*first_map_line;

	first_map_line = NULL;
	fd = open(file_path, O_RDONLY);
	ft_memset(map_dir, 0, sizeof(t_map_dir));
	if (fd < 0)
	{
		perror("failed to open file");
		return (-1);
	}
	result = parse_config_lines(fd, map_dir, &first_map_line);
	if (result != 0)
	{
		close(fd);
		return (result);
	}
	if (first_map_line)
		handle_map_content(fd, first_map_line, map_dir);
	close(fd);
	return (0);
}
