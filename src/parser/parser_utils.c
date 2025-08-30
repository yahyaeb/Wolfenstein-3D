/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:55:51 by yel-bouk          #+#    #+#             */
/*   Updated: 2025/08/26 19:53:51 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	comma_checker(const char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter == 2);
}

void	cpy_dir_path(char **dst, char **src, int *dir_path)
{
	if (*dst)
		free(*dst);
	*dst = *src;
	*src = NULL;
	(*dir_path)++;
}

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*get_next_nonblank_line(int fd)
{
	char	*line;

	line = ft_gnl(fd);
	while (line && is_blank_line(line))
	{
		free(line);
		line = ft_gnl(fd);
	}
	return (line);
}
