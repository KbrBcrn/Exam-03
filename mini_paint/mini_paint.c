/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbeceren <kbeceren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:35:14 by kbeceren          #+#    #+#             */
/*   Updated: 2023/03/05 14:35:16 by kbeceren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

void	*create_tab(t_tab *tab)
{
	int	x;

	x = 0;
	tab->tab = malloc(sizeof(char) * (tab->size_x * tab->size_y) + 1);
	if (!tab->tab)
		return (NULL);
	while (x < (tab->size_x * tab->size_y))
	{
		tab->tab[x] = tab->type;
		x++;
	}
	tab->tab[x] = '\0';
	return (tab);
}

void	create_circle(t_tab *tab)
{
	int		i;
	int		cur_x;
	int		cur_y;
	float	math;

	i = 0;
	while (i < tab->size_x * tab->size_y)
	{
		cur_x = i % tab->size_x;
		cur_y = i / tab->size_x;
		math = (powf(tab->x - cur_x, 2) + powf(tab->y - cur_y, 2));
		if (sqrtf(math) <= tab->radius && tab->content == 'C')
			tab->tab[i] = tab->type;
		else if (sqrtf(math) <= tab->radius && sqrtf(math) > tab->radius - 1)
			tab->tab[i] = tab->type;
		i++;
	}	
}

void	print_tab(t_tab *tab)
{
	int	i;

	i = 0;
	while (i < tab->size_x * tab->size_y)
	{
		write (1, &tab->tab[i], 1);
		if ((i + 1) % tab->size_x == 0)
			write (1, "\n", 1);
		i++;
	}
}

int	check_arg(char **argv, t_tab *tab)
{
	FILE	*file;

	file = fopen(argv[1], "r");
	if (!file)
		return (0);
	if (fscanf(file, "%d %d %c\n", &tab->size_x, &tab->size_y, &tab->type) != 3)
		return (0);
	if (!create_tab(tab))
		return (0);
	while (fscanf(file, "%c %f %f %f %c\n", &tab->content, &tab->x,
		&tab->y, &tab->radius, &tab->type) == 5)
	{
		if (tab->content != 'c' && tab->content != 'C')
			return (0);
		create_circle(tab);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_tab	tab;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!check_arg(argv, &tab))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	print_tab(&tab);
	free(tab.tab);
	return (0);
}