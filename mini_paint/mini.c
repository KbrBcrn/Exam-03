/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbeceren <kbeceren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:35:46 by kbeceren          #+#    #+#             */
/*   Updated: 2023/03/22 14:05:56 by kbeceren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_error(char const *str, int ret)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (ret);
}

int	clear_all(FILE *file, char *drawing)
{
	if (file)
		fclose(file);
	if (drawing)
		free(drawing);
	return (1);
}

char	*get_zone(FILE *file, t_zone *zone)
{
	int		i;
	char	*tmp;

	if (fscanf(file, "%d %d %c\n", &zone->width,
			&zone->height, &zone->background) != 3)
		return (NULL);
	if (zone->width <= 0 || zone->width > 300
		|| zone->height <= 0 || zone->height > 300)
		return (NULL);
	if (!(tmp = (char *)malloc(sizeof(*tmp) * (zone->width * zone->height))))
		return (NULL);
	i = 0;
	while (i < zone->width * zone->height)
		tmp[i++] = zone->background;
	return (tmp);
}

int	in_circle(float x, float y, t_shape *shape)
{
	float	distance;

	distance = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
	if (distance <= shape->radius)
	{
		if ((shape->radius - distance) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_shape(t_zone *zone, char *drawing, t_shape *shape)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (i < zone->height)
	{
		j = 0;
		while (j < zone->width)
		{
			ret = in_circle((float)i, (float)j, shape);
			if ((shape->type == 'c' && ret == 2)
				|| (shape->type == 'C' && ret))
				drawing[(i * zone->width) + j] = shape->color;
			j++;
		}
		i++;
	}
}

int	draw_shapes(FILE *file, t_zone *zone, char *drawing)
{
	t_shape	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x,
				&tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
			return (0);
		draw_shape(zone, drawing, &tmp);
	}	
	if (ret != -1)
		return (0);
	return (1);
}

void	draw_drawing(t_zone *zone, char *drawing)
{
	int	i;

	i = 0;
	while (i < zone->height)
	{
		write(1, drawing + (i *zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	FILE	*file;
	t_zone	zone;
	char	*drawing;

	memset(&zone, 0, sizeof(t_zone));
	drawing = NULL;
	if (argc != 2)
		return (str_error("Error: argument\n", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n", 1));
	if (!(drawing = get_zone(file, &zone)))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n", 1));
	if (!(draw_shapes (file, &zone, drawing)))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n", 1));
	draw_drawing(&zone, drawing);
	clear_all(file, drawing);
}
