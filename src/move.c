/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 17:21:57 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 19:54:50 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			dist_init(t_lem *lem)
{
	int			i;

	i = -1;
	while (++i < lem->rooms_nr)
		lem->rooms[i].dist = INF;
}

void			init_ants(t_lem lem, int *arr)
{
	int			i;

	i = 0;
	while (i < lem.total_ants)
		arr[i++] = lem.start;
}

void			print_sol(t_lem *lem, int room, int *ant_arr)
{
	static int	k = 0;

	if (!k++)
		print_lines(lem->lines);
	lem->rooms[room].ants++;
	lem->rooms[room].full = 1;
	lem->rooms[ant_arr[lem->i]].ants--;
	ant_arr[lem->i] = room;
	ft_putchar('L');
	ft_putnbr(lem->i + 1);
	ft_putchar('-');
	ft_putstr(lem->rooms[room].name);
	ft_putchar(' ');
	dist_init(lem);
	lem->flag = 1;
}

void			move_ants(t_lem lem)
{
	int			ant_arr[lem.total_ants];
	int			room;

	init_ants(lem, ant_arr);
	while (lem.rooms[lem.end].ants != lem.total_ants)
	{
		dist_init(&lem);
		lem.i = -1;
		while (++lem.i < lem.rooms_nr)
			lem.rooms[lem.i].full = 0;
		lem.i = -1;
		lem.flag = 0;
		while (++lem.i < lem.total_ants)
		{
			room = dijkstra(&lem, ant_arr[lem.i]);
			if (ant_arr[lem.i] == lem.start && room == lem.end && lem.flag)
				break ;
			if (room == -1 || (lem.rooms[room].full && room != lem.end))
				continue ;
			print_sol(&lem, room, ant_arr);
		}
		if (!lem.flag && lem.i == lem.total_ants)
			ft_err(lem, "No links between start and end");
		ENDL;
	}
}
