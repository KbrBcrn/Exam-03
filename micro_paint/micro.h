/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbeceren <kbeceren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:35:08 by kbeceren          #+#    #+#             */
/*   Updated: 2023/03/23 07:08:25 by kbeceren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_H
# define MICRO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_zone
{
	int		width;
	int		height;
	char	background;
} 				t_zone;

typedef struct	s_shape
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}				t_shape;

#endif
