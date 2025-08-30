/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:51:53 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/27 16:05:16 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	handle_texture_line(char *line, t_map_dir *map_dir)
{
	if (direction(line, map_dir) == 0)
	{
		ft_printf("Error: Textures paths invalid\n");
		return (1);
	}
	return (2);
}

int	handle_floor(char *line, t_map_dir *m)
{
	if (line[0] == 'F')
	{
		m->f_count++;
		if (fill_color_array(m->f, m->f_rgb) == 0 || m->f_count > 1)
		{
			ft_printf("Invalid RGB colors\n");
			return (1);
		}
	}
	return (0);
}

int	handle_ceiling(char *line, t_map_dir *m)
{
	if (line[0] == 'C')
	{
		m->c_count++;
		if (fill_color_array(m->c, m->c_rgb) == 0 || m->c_count > 1)
		{
			m->c_count++;
			ft_printf("Invalid RGB colors\n");
			return (1);
		}
	}
	return (0);
}

int	handle_color_line(char *line, t_map_dir *m)
{
	if (parse_color(line, m) == 0)
	{
		ft_printf("Error: RGB colors\n");
		return (1);
	}
	if (handle_floor(line, m) != 0)
		return (1);
	else if (handle_ceiling(line, m) != 0)
		return (1);
	return (2);
}

int	handle_config_line(char *line, int counter, t_map_dir *map_dir)
{
	char	*clean_line;

	clean_line = skip_whitespace(line);
	if (counter <= 4)
		return (handle_texture_line(clean_line, map_dir));
	else if (counter == 5 || counter == 6)
		return (handle_color_line(clean_line, map_dir));
	return (2);
}
