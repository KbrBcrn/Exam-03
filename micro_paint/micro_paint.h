/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbeceren <kbeceren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:35:08 by kbeceren          #+#    #+#             */
/*   Updated: 2023/03/05 14:35:11 by kbeceren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct t_tab {
	int		size_x;
	int		size_y;
	float	x;
	float	y;
	char	type;
	char	content;
	float	width;
	float	height;
	char	*tab;
}	t_tab;

#endif