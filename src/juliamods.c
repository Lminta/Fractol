/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliamods.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:18:15 by lminta            #+#    #+#             */
/*   Updated: 2019/07/10 17:29:38 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "frac_mods.h"

void		*two_colors_jul(void *snuffbox)
{
	int			i;
	int			j;
	t_move		mv;
	t_complex	c;

	mv = *((t_move *)snuffbox);
	i = (WIN_Y / THREADS) * mv.thread - 1;
	c = g_lastcoord(c_set(0, 0), 0);
	while (++i < (WIN_Y / THREADS) * (mv.thread + 1) && (j = -1))
		while (++j < WIN_X)
		{
			if (julia_test(c_set(j * mv.zoom + mv.rl,
			-i * mv.zoom + mv.ud), c, mv.n, mv.power) == mv.n)
				img_plot(j, i, g_end_c(fill_color(0, 0, 0), 0));
			else
				img_plot(j, i, g_color(fill_color(0, 0, 0), 0));
		}
	return (0);
}

void		*three_colors_jul(void *snuffbox)
{
	int			i;
	int			j;
	t_move		mv;
	t_color		grad;
	t_complex	c;

	mv = *((t_move *)snuffbox);
	i = (WIN_Y / THREADS) * mv.thread - 1;
	grad = fill_color(0, 0, 0);
	grad = gradient(g_color(grad, 0), g_end_c(grad, 0), mv.n);
	c = g_lastcoord(c_set(0, 0), 0);
	while (++i < (WIN_Y / THREADS) * (mv.thread + 1) && (j = -1))
		while (++j < WIN_X)
		{
			if (julia_test(c_set(j * mv.zoom + mv.rl,
			-i * mv.zoom + mv.ud), c, mv.n, mv.power) == mv.n)
				img_plot(j, i, fill_color(0, 0, 0));
			else
				img_plot(j, i, sum_collors(g_color(grad, 0), grad, julia_test(
				c_set(j * mv.zoom + mv.rl, -i * mv.zoom + mv.ud),
				c, mv.n, mv.power)));
		}
	return (0);
}

void		*multi_jul(void *snuffbox)
{
	int			i;
	int			j;
	t_move		mv;
	t_complex	c;

	mv = *((t_move *)snuffbox);
	i = (WIN_Y / THREADS) * mv.thread - 1;
	c = g_lastcoord(c_set(0, 0), 0);
	while (++i < (WIN_Y / THREADS) * (mv.thread + 1) && (j = -1))
		while (++j < WIN_X)
		{
			if (julia_test(c_set(j * mv.zoom + mv.rl,
			-i * mv.zoom + mv.ud), c, mv.n, mv.power) == mv.n)
				img_plot(j, i, fill_color(0, 0, 0));
			else
				img_plot(j, i, n_color(julia_test(
				c_set(j * mv.zoom + mv.rl, -i * mv.zoom + mv.ud),
				c, mv.n, mv.power)));
		}
	return (0);
}
