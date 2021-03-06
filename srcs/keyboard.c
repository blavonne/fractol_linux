/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blavonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:27:52 by blavonne          #+#    #+#             */
/*   Updated: 2020/10/32 16:27:54 by blavonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		move_handler(int key, t_fractol *fractol)
{
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key\
			== ARROW_DOWN)
	{
		if (!fractol->type && fractol->a.type < 16)
			move_a(key, fractol);
		if (fractol->type)
			move_g(key, fractol);
	}
	if (key == MAIN_P && !fractol->type && fractol->a.type == 1)
		fractol->a.motion_on = (char)(!fractol->a.motion_on);
}

static void		power_handler(int key, t_fractol *fractol)
{
	if ((key == NUM_MINUS || key == NUM_PLUS) && !fractol->type)
	{
		key == NUM_MINUS && fractol->a.power > 2 ? fractol->a.power-- : 0;
		key == NUM_PLUS && fractol->a.power < 6 ? fractol->a.power++ : 0;
	}
	else if (fractol->type && (key == MAIN_MINUS || key == MAIN_PLUS))
		zoom_g(fractol, key);
}

static void		restore_handler(int key, t_fractol *fractol)
{
	if (key == SPACE)
	{
		if (!fractol->type)
		{
			ft_memset(fractol->mlx.image.img, 255, fractol->a.img_size *\
			fractol->a.img_size * (int)sizeof(int));
			algebaic_init(&fractol->a, fractol->a.type);
		}
		if (fractol->type)
		{
			fractol->g.offset = point_init(0, 0);
			fractol->g.power = 0;
			set_color_schema_g(&fractol->g, fractol->g.type);
			fractol->g.sign = 1;
			fractol->g.scale = 1;
			ft_memset(fractol->mlx.image.img, 255, WIDTH * HEIGHT *\
			(int)sizeof(int));
		}
	}
}

static void		color_handler(int key, t_fractol *fractol)
{
	if (fractol->type)
	{
		if (key == MAIN_B || key == MAIN_R || key == MAIN_G || key == MAIN_T)
			increase_img_color(key, fractol);
		else if (key == NUM_PLUS || key == NUM_MINUS)
			fractol->g.sign = (key == NUM_PLUS) ? 1 : 0;
	}
	if (!fractol->type && key == MAIN_C)
	{
		if (fractol->a.color_schema < 8)
			fractol->a.color_schema++;
		else if (fractol->a.color_schema == 8)
			fractol->a.color_schema = 0;
	}
}

int				key_pressed(int key, t_fractol *fractol)
{
	if (key == ESC)
		clean_exit(fractol);
	move_handler(key, fractol);
	power_handler(key, fractol);
	fractol->type ? type_handler_g(key, fractol) : type_handler_a(&key,\
	fractol);
	restore_handler(key, fractol);
	color_handler(key, fractol);
	help_handler(key, fractol);
	if (fractol->type)
		fractol->g.draw_g[(int)fractol->g.type](fractol);
	else if (!fractol->type && fractol->a.type < 16)
		rendering(fractol);
	else if (!fractol->type && (key == NUM_PLUS || key == NUM_MINUS ||\
	key == NUM_EIGHT || key == NUM_NINE))
		buddha(fractol);
	return (0);
}
