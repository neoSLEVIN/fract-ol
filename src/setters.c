/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:51:38 by cschoen           #+#    #+#             */
/*   Updated: 2019/08/31 21:45:27 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_point		set_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_dpoint	set_dpoint(double x, double y)
{
	t_dpoint	dpoint;

	dpoint.x = x;
	dpoint.y = y;
	return (dpoint);
}

t_rgb		set_rgb(int red, int green, int blue)
{
	t_rgb	color;

	color.r = red;
	color.g = green;
	color.b = blue;
	return (color);
}

t_complex	set_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}