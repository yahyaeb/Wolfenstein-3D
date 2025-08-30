/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_input_toolkit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:58:37 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/26 21:59:19 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"
#define PLANE_SIZE 0.5

void	on_motion_rotate_minimap(t_state *state, char *dir)
{
	if (ft_strncmp(dir, "left", 4) == 0)
	{
		state->hero->ang -= 0.1;
		if (state->hero->ang < 0)
			state->hero->ang += 2 * M_PI;
	}
	else if (ft_strncmp(dir, "right", 5) == 0)
	{
		state->hero->ang += 0.1;
		if (state->hero->ang > 2 * M_PI)
			state->hero->ang -= 2 * M_PI;
	}
	else
		return ;
	state->hero->dx = cos(state->hero->ang);
	state->hero->dy = sin(state->hero->ang);
	state->hero->pdx = -state->hero->dy * PLANE_SIZE;
	state->hero->pdy = state->hero->dx * PLANE_SIZE;
	state->data->must_clear_window = 1;
}

void	kp_rotate(int keysym, t_state *state)
{
	if (keysym == XK_Left)
		on_motion_rotate_minimap(state, "left");
	else if (keysym == XK_Right)
		on_motion_rotate_minimap(state, "right");
}

int	on_keypress(int keysym, t_state *state)
{
	if (keysym == XK_Escape)
	{
		ft_printf("🧊 [ESC] Leaving already? So long! 👋\n");
		sl_memfree(state);
		exit(0);
	}
	else if (keysym == XK_w || keysym == XK_a
		|| keysym == XK_s || keysym == XK_d)
	{
		kp_motion(keysym, state);
	}
	else if (keysym == XK_Left || keysym == XK_Right)
		kp_rotate(keysym, state);
	return (0);
}

void	kp_motion(int keysym, t_state *state)
{
	if (keysym == XK_w)
	{
		on_motion_up(state);
	}
	else if (keysym == XK_a)
	{
		on_motion_left(state);
	}
	else if (keysym == XK_s)
	{
		on_motion_down(state);
	}
	else if (keysym == XK_d)
	{
		on_motion_right(state);
	}
}

int	on_destroy(t_state *state)
{
	ft_printf("[on_destroy] Free all! 🧹\n");
	sl_memfree(state);
	exit(0);
	return (0);
}
