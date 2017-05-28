/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:56:42 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 18:16:24 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		take_ants(t_lem *lem)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		add_line(&lem->lines, line, *lem);
		if (check_command(*lem, line) == 2)
			continue ;
		else if (ft_number(line))
			break ;
		else
			ft_err(*lem, "ants: [integer > 0]");
	}
	lem->total_ants = ft_atoi(line);
	if (lem->total_ants < 1)
		ft_err(*lem, "ants: [integer > 0]");
	lem->rooms_nr = 0;
	lem->i = 0;
	lem->start = -1;
	lem->end = -1;
	free(line);
}

void	init_map(t_lem *lem)
{
	int	i;
	int	j;

	i = 0;
	if (!(lem->map = (int**)malloc(sizeof(int*) * lem->rooms_nr)))
		ft_err(*lem, "mem. alloc failed");
	while (i < lem->rooms_nr)
	{
		if (!(lem->map[i] = (int*)malloc(sizeof(int) * lem->rooms_nr)))
			ft_err(*lem, "mem. alloc failed");
		j = 0;
		while (j < lem->rooms_nr)
			lem->map[i][j++] = 0;
		i++;
	}
}

void		take_link(char *line, t_lem *lem)
{
	char	**w;
	int		room1;
	int		room2;

	w = ft_strsplit(line, '-');
	room1 = room_index(*lem, w[0]);
	room2 = room_index(*lem, w[1]);
	lem->map[room1][room2] = 1;
	lem->map[room2][room1] = 1;
	free_dbl(w);
}

void		link_all(char *line, t_lem *lem)
{
	init_map(lem);
	take_link(line, lem);
	while (get_next_line(0, &line) > 0)
	{
		add_line(&lem->lines, line, *lem);
		if (check_command(*lem, line) == 2)
			continue ;
		else if (check_link(line, *lem))
			take_link(line, lem);
	}
	free(line);
}

t_lem		read_lemin(void)
{
	char	*line;
	t_lem	lem;

	lem.lines = NULL;
	take_ants(&lem);
	while (get_next_line(0, &line) > 0)
	{
		add_line(&lem.lines, line, lem);
		if (check_command(lem, line) > 0)
		{
			if (check_command(lem, line) == 1)
				do_command(line, &lem);
		}
		else if (check_room(line))
			create_room(line, reg_room, &lem);
		else if (check_link(line, lem))
			break ;
	}
	if (check_link(line, lem))
		link_all(line, &lem);
	free(line);
	return (lem);
}
