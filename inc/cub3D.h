/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:25:30 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 23:42:41 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1620
# define WIN_HEIGHT 780

# define PROG_NAME "cub3D"

/* Standard libraries */
# include <unistd.h> // open, close, read, write
# include <stdlib.h> // malloc, free, exit
# include <stdio.h> // printf, perror
# include <string.h> // strerror
# include <errno.h> // error codes
# include <sys/time.h> // gettimeofday
# include <math.h> // any function

/* MiniLibx and dependencies */
# include "../libft/libxkit/.minilibx/mlx.h" // any function
# include <X11/X.h>
# include <X11/keysym.h>

/* Custom headers and libraries */
# include "../ass/assets.h"

# include "../libft/libft.h"
# include "../libft/libxkit/libxkit.h"

/*typedef struct s_map_dir
{
	int		no;
	int		so;
	int		ea;
	int		we;
	char	*temp;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*f;
	char	*c;
	int		map_height;
	char	*next_line;
	char	**tilemap;
	int		f_rgb[3];
	int		c_rgb[3];
}	t_map_dir;
*/

// Initer
int		launcher(t_state *state, t_data *data, char fpath[256],
			t_map_dir *map_dir);
int		check_requirements(t_state *state, char **tilemap, size_t nb_lines,
			t_count_req *counter);
void	set_minimap(t_state *state);
void	set_ui(t_settings *settings);
int		init_data(t_state *state, t_data *data, int step);

int		map_parser(t_state *state);
int		init_state(t_state **state);
int		init_data(t_state *state, t_data *data, int step);
int		render_3d(t_state *state);
void	on_events(t_state *state);
void	set_counter_req(t_count_req *counter);

// Events
int		on_coll_tile(t_state *state, t_pos *pos);
void	on_exit_tile(t_state *state);
void	on_enemy_tile(t_state *state);
int		ls_bonus_check(char **argv);

// Screens
void	display_start_screen(void);
void	display_victory_screen(void);
void	display_defeat_screen(void);

// Levels
int		change_level(t_state *state);

// Config file parser

void	free_map_dir(t_map_dir *map);
void	free_color(char *color);
int		is_a_dot(char *str, t_map_dir *map, int i);
int		comma_checker(const char *str);
void	cpy_dir_path(char **src, char **dst, int *dir_path);
int		direction(char *str, t_map_dir *map);
int		dir_count(int *i);
int		is_only_digits(char *str);
int		is_blank_line(char *line);
int		parse_color(char *next_line, t_map_dir *map);
void	free_split(char **tokens);
int		fill_color_array(char *color_str, int color_arr[3]);
char	*get_next_nonblank_line(int fd);
int		handle_config_line(char *line, int counter, t_map_dir *map_dir);
int		copy_map_to_file(int fd, char *first_map_line, const char *dest);
int		parse_config_file(const char *file_path, t_map_dir *map_dir);
void	free_wall_textures(void *mlx, t_settings *settings);
int		handle_color_line(char *line, t_map_dir *map_dir);
int		handle_texture_line(char *line, t_map_dir *map_dir);
int		parse_config_lines(int fd, t_map_dir *map_dir, char **first_map_line);
int		handle_map_content(int fd, char *first_map_line, t_map_dir *map_dir);
int		parse_config_file(const char *file_path, t_map_dir *map_dir);
char	*skip_whitespace(char *line);

#endif
