/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:20:20 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/25 19:32:42 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	parse_color(char *next_line, t_map_dir *map)
{
	char	*color_value;

	if ((next_line[0] != 'F' && next_line[0] != 'C')
		|| (next_line[1] != ' '))
		return (0);
	color_value = ft_strdup(&next_line[2]);
	if (!color_value)
		return (0);
	if (!comma_checker(color_value))
	{
		free(color_value);
		return (0);
	}
	if (next_line[0] == 'F')
	{
		free_color(map->f);
		map->f = color_value;
	}
	else
	{
		free_color(map->c);
		map->c = color_value;
	}
	return (1);
}

int	fill_color_loop(char **tokens, char *trimmed, int value)
{
	if (!trimmed || ft_strlen(trimmed) == 0 || !is_only_digits(trimmed))
	{
		free(trimmed);
		free_split(tokens);
		return (0);
	}
	value = ft_atoi(trimmed);
	free(trimmed);
	if (value < 0 || value > 255)
	{
		free_split(tokens);
		return (0);
	}
	return (1);
}

int	fill_color_array(char *color_str, int color_arr[3])
{
	char	**tokens;
	int		i;
	int		value;
	char	*trimmed;

	tokens = ft_split(color_str, ',');
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		free_split(tokens);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(tokens[i], " \t\r\n");
		value = ft_atoi(trimmed);
		if (fill_color_loop(tokens, trimmed, value) != 1)
			return (0);
		color_arr[i] = value;
		i++;
	}
	free_split(tokens);
	return (1);
}
