/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:10:02 by cschoen           #+#    #+#             */
/*   Updated: 2019/09/21 23:25:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_edge(t_frac *ftl)
{
	double	step;

	ftl->min = set_complex((-2.0 / ftl->zoom), (-2.0 / ftl->zoom));
	ftl->max = set_complex((2.0 / ftl->zoom), (2.0 / ftl->zoom));
	step = 4.0 / ftl->zoom / (ftl->size - 1);
	ftl->step = set_complex(step, step);
}

static void	draw_side(t_frac *ftl)
{
	int	i;

	i = -1;
	ftl->min = set_complex(-2.0, -2.0);
	ftl->max = set_complex(2.0, 2.0);
	ftl->step = set_complex(4.0 / (100 - 1), 4.0 / (100 - 1));
	while (++i < 5)
		if (ftl->side_imgs[i].type == JULIA)
			julia(ftl, &ftl->side_imgs[i]);
		else if (ftl->side_imgs[i].type == BURNING_SHIP)
			burning_ship(ftl, &ftl->side_imgs[i]);
		else if (ftl->side_imgs[i].type == MANDELBAR)
			mandelbar(ftl, &ftl->side_imgs[i]);
		else if (ftl->side_imgs[i].type == CELTIC)
			celtic(ftl, &ftl->side_imgs[i]);
		else if (ftl->side_imgs[i].type == NEWTON)
			newton(ftl, &ftl->side_imgs[i]);
		else
			mandelbrot(ftl, &ftl->side_imgs[i]);
	i = -1;
	while (++i < 5)
		mlx_put_image_to_window(ftl->mlx_ptr, ftl->win_ptr,
			ftl->side_imgs[i].img_ptr, ftl->side_imgs[i].pos.x,
				ftl->side_imgs[i].pos.y);
}

static void	draw_lines(t_frac *ftl)
{
	int	x;
	int	y;

	x = 499;
	y = -1;
	while (++y <= 600)
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, y, 0x0000FF00);
	y = 500;
	while (++x <= 1000)
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, y, 0x0000FF00);
	x = 600;
	while (++y <= 600 && ftl->mem.side)
	{
			mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, 600, y, 0x0000FF00);
			mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, 700, y, 0x0000FF00);
			mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, 800, y, 0x0000FF00);
			mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, 900, y, 0x0000FF00);
	}
}

static void	draw_border(t_frac *ftl)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	x = ftl->img->pos.x - 1;
	y = ftl->img->pos.y - 1;
	end_x = x + ftl->size + 1;
	end_y = y + ftl->size + 1;
	mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, y, 0x0000FF00);
	while (++x <= end_x)
	{
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, y, 0x0000FF00);
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, end_y, 0x0000FF00);
	}
	x = ftl->img->pos.x - 1;
	while (++y <= end_y)
	{
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, x, y, 0x0000FF00);
		mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr, end_x, y, 0x0000FF00);
	}
}

void		draw(t_frac *ftl, int key)
{
	ftl->mem.side && key != TAB ? draw_side(ftl) : 0;
	if (!ftl->mem.side && key == M_KEY)
		mlx_put_image_to_window(ftl->mlx_ptr, ftl->win_ptr,
								ftl->black_img->img_ptr, 500, 500);
	draw_lines(ftl);
	init_edge(ftl);
	if (key != TAB)
	{
		ftl->type == MANDELBROT ? mandelbrot(ftl, ftl->img) : 0;
		ftl->type == JULIA ? julia(ftl, ftl->img) : 0;
		ftl->type == BURNING_SHIP ? burning_ship(ftl, ftl->img) : 0;
		ftl->type == MANDELBAR ? mandelbar(ftl, ftl->img) : 0;
		ftl->type == CELTIC ? celtic(ftl, ftl->img) : 0;
		ftl->type == NEWTON ? newton(ftl, ftl->img) : 0;
	}
	key == INC_IMG || key == DEC_IMG ? mlx_put_image_to_window(ftl->mlx_ptr,
		ftl->win_ptr, ftl->black_img->img_ptr, 500, 0) : 0;
	mlx_put_image_to_window(ftl->mlx_ptr, ftl->win_ptr, ftl->img->img_ptr,
							ftl->img->pos.x, ftl->img->pos.y);
	if (ftl->size < 500 && (key == M_KEY || key == INC_IMG || key == DEC_IMG))
		draw_border(ftl);
	ftl->mem.center ? mlx_pixel_put(ftl->mlx_ptr, ftl->win_ptr,
		(double)ftl->size / 2 + SCREEN, (double)ftl->size / 2, 0x00FF0000) : 0;
	draw_ui(ftl);
}
