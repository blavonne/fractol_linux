/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blavonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:42:12 by blavonne          #+#    #+#             */
/*   Updated: 2020/10/31 16:43:15 by blavonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			type_handler_g(int key, t_fractol *fractol)
{
	if (fractol->type && (key >= ONE && key <= FOUR))
	{
		if ((key == ONE && !fractol->g.type) ||\
			(key == TWO && fractol->g.type == 1) || (key == THREE &&\
			fractol->g.type == 2) || (key == FOUR && fractol->g.type == 3))
			return ;
		mlx_destroy_image(fractol->mlx.mlx, fractol->mlx.image.ptr);
		fractol->g.offset = point_init(0, 0);
		fractol->mlx.image = create_img(&fractol->mlx, WIDTH, HEIGHT);
		fractol->g.power = 0;
		fractol->g.bough_angle = 0.6;
		if (key == ONE)
			fractol->g.type = 0;
		else if (key == TWO)
			fractol->g.type = 1;
		else if (key == THREE)
			fractol->g.type = 2;
		else
			fractol->g.type = 3;
		set_color_schema_g(&fractol->g, fractol->g.type);
	}
}

static int		set_type2(int key, t_fractol *fractol)
{
	if (key == NUM_TWO && fractol->type != 10)
		return (fractol->a.type = 10);
	else if (key == NUM_THREE && fractol->a.type != 11)
		return (fractol->a.type = 11);
	else if (key == NUM_FOUR && fractol->a.type != 12)
		return (fractol->a.type = 12);
	else if (key == NUM_FIVE && fractol->a.type != 13)
		return (fractol->a.type = 13);
	else if (key == NUM_SIX && fractol->a.type != 14)
		return (fractol->a.type = 14);
	else if (key == NUM_SEVEN && fractol->a.type != 15)
		return (fractol->a.type = 15);
	else if (key == NUM_EIGHT && fractol->a.type != 16)
		return (fractol->a.type = 16);
	else if (key == NUM_NINE && fractol->a.type != 17)
		return (fractol->a.type = 17);
	return (-1);
}

static int		set_type(int key, t_fractol *fractol)
{
	if (key == ONE && fractol->a.type)
		return (fractol->a.type = 0);
	else if (key == TWO && fractol->a.type != 1)
		return (fractol->a.type = 1);
	else if (key == THREE && fractol->a.type != 2)
		return (fractol->a.type = 2);
	else if (key == FOUR && fractol->a.type != 3)
		return (fractol->a.type = 3);
	else if (key == FIVE && fractol->a.type != 4)
		return (fractol->a.type = 4);
	else if (key == SIX && fractol->a.type != 5)
		return (fractol->a.type = 5);
	else if (key == SEVEN && fractol->a.type != 6)
		return (fractol->a.type = 6);
	else if (key == EIGHT && fractol->a.type != 7)
		return (fractol->a.type = 7);
	else if (key == NINE && fractol->a.type != 8)
		return (fractol->a.type = 8);
	else if (key == NUM_ONE && fractol->a.type != 9)
		return (fractol->a.type = 9);
	return (set_type2(key, fractol));
}

void			type_handler_a(int *key, t_fractol *fractol)
{
	int		old_type;

	old_type = (int)fractol->a.type;
	if (!fractol->type)
	{
		if (*key == ONE || *key == TWO || *key == THREE || *key == FOUR ||\
		*key == FIVE || *key == SIX || *key == SEVEN || *key == EIGHT ||\
		*key == NINE || *key == NUM_ONE || *key == NUM_NINE || *key == NUM_TWO\
		|| *key == NUM_THREE || *key == NUM_FOUR || *key == NUM_FIVE\
		|| *key == NUM_SIX || *key == NUM_SEVEN || *key == NUM_EIGHT)
		{
			fractol->a.motion_on = 0;
			if (set_type(*key, fractol) < 0)
				return ;
			if (fractol->a.type != old_type && fractol->a.type < 16)
				*key = SPACE;
		}
	}
}
