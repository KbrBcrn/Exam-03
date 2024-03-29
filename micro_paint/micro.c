/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbeceren <kbeceren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:47:14 by kbeceren          #+#    #+#             */
/*   Updated: 2023/03/24 20:47:15 by kbeceren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

int ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int str_error(char const *str, int ret)
{
	write(1, str, ft_strlen(str));
	return (ret);
}

int clear_all(FILE *file, char *drawing)
{
	fclose(file);
	if (drawing)
		free(drawing);
	return (1);
}

char *get_zone(FILE *file, t_zone *zone)
{
	int i;
	char *tmp;

	if ((fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background)) != 3)
		return (0);
	if (zone->width <= 0 || zone->width > 300
			|| zone->height <= 0 || zone->height > 300)
		return (0);
	if (!(tmp = (char*)malloc(sizeof(*tmp) * (zone->width * zone->height))))
		return (NULL);
	i = 0;
	while (i < zone->width * zone->height)
		tmp[i++] = zone->background;
	return (tmp);
}

int in_rectangle(float x, float y, t_shape *shape)
{
	if (((x < shape->x || (shape->x + shape->width < x))
		|| (y < shape->y)) || (shape->y + shape->height < y))
		return (0);
	if (((x - shape->x < 1.00000000) || ((shape->x + shape->width) - x < 1.00000000)) ||
	((y - shape->y < 1.00000000 || ((shape->y + shape->height) - y < 1.00000000))))
		return (2);
	return (1);
}

void draw_shape(char *drawing, t_shape *shape, t_zone *zone)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (i < zone->height)
	{
		j = 0;
		while (j< zone->width)
		{
			ret = in_rectangle(j, i, shape);
			if ((shape->type == 'r' && ret == 2)
				|| (shape->type == 'R' && ret))
				drawing[(i * zone->width) + j] = shape->color;
			j++;
		}
		i++;
	}
}

int draw_shapes(FILE *file, char *drawing, t_zone *zone)
{
	t_shape	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
	{
		if (tmp.width <= 0.00000000 || tmp.height <= 0.00000000
			|| (tmp.type != 'r' && tmp.type != 'R'))
			return (0);
		draw_shape(drawing, &tmp, zone);
	}
	if (ret != -1)
		return (0);
	return (1);
}

void draw_drawing(char *drawing, t_zone *zone)
{
	int	i;

	i = 0;
	while (i < zone->height)
	{
		write(1, drawing + (i * zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_zone	zone;
	char	*drawing;
	FILE	*file;

	memset(&zone, 0, sizeof(t_zone));
	drawing = NULL;
	if (argc != 2)
		return (str_error("Error: argument\n", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n", 1));
	if (!(drawing = get_zone(file, &zone)))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n", 1));
	if (!draw_shapes(file, drawing, &zone))
		return (clear_all(file, drawing) && str_error("Error: Operation file corrupted\n", 1));
	draw_drawing(drawing, &zone);
	clear_all(file, drawing);
	return (0);
}
