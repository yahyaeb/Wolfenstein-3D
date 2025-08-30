/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libxkit_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:09:11 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 16:17:12 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBXKIT_STRUCTS_H
# define LIBXKIT_STRUCTS_H

/* */

/* Coloring struct */
typedef struct s_mlx_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}		t_mlx_color;

/* Drawing structs */
typedef struct s_mlx_line
{
	t_mlx_color	color;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}			t_mlx_line;

typedef struct s_bres_data
{
	t_mlx_color	color;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
}			t_bres_data;

typedef struct s_mlx_circle
{
	t_mlx_color	color;
	int			center_x;
	int			center_y;
	int			radius;
}			t_mlx_circle;

typedef struct s_mlx_rect
{
	int	origin_x;
	int	origin_y;
	int	height;
	int	width;
}		t_mlx_rect;

/* Game env structs */
typedef struct s_pos
{
	int			x;
	int			y;
	float		fx;
	float		fy;
}		t_pos;

typedef struct s_size
{
	int		width;
	int		height;
}		t_size;

typedef struct s_img
{
	void	*img;
	char	*addr;
	char	*path;
	int		bpp;
	int		l_len;
	int		endian;
	int		width;
	int		height;
}		t_img;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	t_img		*canvas;
	t_img		*bkgd_img;
	char		*bkgd_path;
	int			canvas_width;
	int			canvas_height;
}		t_env;

typedef struct s_data
{
	int	must_clear_window;
	int	is_running;
	int	nb_steps;
	int	collected;
	int	to_be_collected;
}		t_data;

typedef struct s_cam
{
	t_pos	pos;
	t_pos	max;
	float	ang;
	float	dir_x;
	float	dir_y;
	float	plane_scale;
	float	plane_x;
	float	plane_y;
}		t_cam;

typedef struct s_tile
{
	t_img		*img;
	t_pos		*pos;
	char		*path;
	int			width;
	int			height;
}		t_tile;

typedef struct s_map
{
	char	*fpath;
	char	**tilemap;
	t_tile	*wall;
	t_tile	*coll;
	t_tile	*exit;
	int		*tile_count;
	int		width;
	int		height;
	int		tm_rows;
	int		tm_cols;
	int		cell_width;
	int		cell_height;
	int		cell_size;
}		t_map;

// A counter and a requirement counter for checking tiles count.
typedef struct s_count_req
{
	int		count[6];
	int		req[6];
}		t_count_req;

typedef struct s_enemy
{
	t_img		*current_sprite;
	t_img		*to_up;
	t_img		*to_down;
	t_img		*to_left;
	t_img		*to_right;
	char		*to_up_path;
	char		*to_down_path;
	char		*to_left_path;
	char		*to_right_path;
	t_pos		*pos;
	int			frame;
	int			amplitude;
	char		direction;
	char		padding[7];
}		t_enemy;

typedef struct s_hero
{
	t_img		*img;
	t_img		*to_up;
	t_img		*to_down;
	t_img		*to_left;
	t_img		*to_right;
	char		*img_path;
	char		*to_up_path;
	char		*to_down_path;
	char		*to_left_path;
	char		*to_right_path;
	t_pos		*pos;
	int			frame;
	float		ang;
	float		dx;
	float		dy;
	float		pdx;
	float		pdy;	
}		t_hero;

typedef struct s_settings
{
	void			*north_img;
	void			*south_img;
	void			*west_img;
	void			*east_img;
	t_img			*north_tex;
	t_img			*south_tex;
	t_img			*west_tex;
	t_img			*east_tex;
	int				tex_width;
	int				tex_height;
	int				offset_x;
	int				offset_y;
	float			fov;
	int				nb_rays_cast;
	double			wall_x;
	int				tex_x;
	int				line_height;
	t_mlx_color		hero_color;
	t_mlx_circle	hero_dot;
	t_mlx_line		hero_line;
	t_mlx_color		ray_color;
	t_pos			hero_center;
	t_mlx_color		grid_color;
	t_mlx_color		ui_color;
	t_mlx_rect		minimap_screen;
	t_mlx_rect		map_screen;
	t_mlx_rect		ui_screen;
	t_mlx_color		wall_color;
	t_mlx_color		wall_color_shaded;
	t_mlx_color		floor_color;
	t_mlx_color		ceiling_color;
}		t_settings;

typedef struct s_ray
{
	t_mlx_color	color;
	t_mlx_line	line;
	t_pos		origin;		
	t_pos		pos;
	t_pos		start;
	t_pos		end;
	float		angle;
	float		dir_x;
	float		dir_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	float		perp_dist;
	float		raw_dist;
	int			step_x;
	int			step_y;
	int			side;
}		t_ray;

typedef struct s_line_cast
{
	t_mlx_line	mlx_line;
	int			height;
}		t_line_cast;

typedef struct s_map_dir
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
	int		f_count;
	int		c_count;
	int		map_height;
	char	*next_line;
	char	**tilemap;
	int		f_rgb[3];
	int		c_rgb[3];
}	t_map_dir;

typedef struct s_state
{
	t_env		*env;
	t_data		*data;
	t_map		*map;
	t_settings	*settings;
	t_cam		*cam;
	t_hero		*hero;
	t_enemy		**enemies;
	int			render_event;
	int			error_code;
	int			current_frame;
	char		padding[4];
	int			f_rgb[3];
	int			c_rgb[3];
}		t_state;

#endif
