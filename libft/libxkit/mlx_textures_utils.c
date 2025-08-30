/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:25:02 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/27 21:35:56 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

void	free_texture(void *mlx, t_img *tex)
{
	if (tex)
	{
		if (tex->img)
			mlx_destroy_image(mlx, tex->img);
		if (tex->path)
			free(tex->path);
		free(tex);
	}
}

void	free_wall_textures(void *mlx, t_settings *settings)
{
	free_texture(mlx, settings->north_tex);
	free_texture(mlx, settings->south_tex);
	free_texture(mlx, settings->east_tex);
	free_texture(mlx, settings->west_tex);
}

t_img	*load_single_texture(void *mlx, const char *path)
{
	t_img	*tex;

	tex = malloc(sizeof(t_img));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx,
			(char *)path, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->l_len, &tex->endian);
	tex->path = ft_strdup(path);
	return (tex);
}

int	load_wall_textures(t_settings *settings, t_map_dir *map_dir, void *mlx)
{
	settings->north_tex = load_single_texture(mlx, map_dir->no_path);
	if (!(settings->north_tex))
		return (1);
	settings->south_tex = load_single_texture(mlx, map_dir->so_path);
	if (!(settings->south_tex))
		return (1);
	settings->east_tex = load_single_texture(mlx, map_dir->ea_path);
	if (!(settings->east_tex))
		return (1);
	settings->west_tex = load_single_texture(mlx, map_dir->we_path);
	if (!(settings->west_tex))
		return (1);
	return (0);
}

int	copy_tilemap(char **dest, char **src, t_map_dir *map_dir, t_state *state)
{
	int	i;

	i = 0;
	while (i < map_dir->map_height)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (--i >= 0)
				free(dest[i]);
			return (1);
		}
		i++;
	}
	dest[map_dir->map_height] = NULL;
	state->map->tm_rows = map_dir->map_height;
	return (0);
}
