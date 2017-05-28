/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:15:52 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 18:35:41 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			next_room(int *parent, int u, int start)
{
	if (parent[u] == start)
		return (u);
	return (next_room(parent, parent[u], start));
}

int			min_dist(int *visited, t_lem *lem)
{
	int		i;
	int		min;
	int		min_index;

	i = -1;
	min_index = -1;
	min = INF;
	while (++i < lem->rooms_nr)
		if (!visited[i] && lem->rooms[i].dist < min)
		{
			min = lem->rooms[i].dist;
			min_index = i;
		}
	return (min_index);
}

int			dijkstra2(t_lem *lem, int start, int *visited, int *parent)
{
	int		v;
	int		u;

	u = start;
	while (!is_full(u, lem) && gotta_visit(visited, lem))
	{
		u = min_dist(visited, lem);
		if (lem->rooms[u].type == end_room)
			return (next_room(parent, u, start));
		v = -1;
		while (++v < lem->rooms_nr)
			if (lem->map[v][u] &&
				!(lem->rooms[v].full && u == start && v != lem->end) &&
				lem->rooms[u].dist + 1 < lem->rooms[v].dist)
			{
				lem->rooms[v].dist = lem->rooms[u].dist + 1;
				parent[v] = u;
			}
		visited[u] = 1;
	}
	return (-1);
}

int			dijkstra(t_lem *lem, int start)
{
	int		visited[lem->rooms_nr];
	int		parent[lem->rooms_nr];
	int		i;

	i = -1;
	if (start == lem->end)
		return (i);
	lem->rooms[start].dist = 0;
	while (++i < lem->rooms_nr)
	{
		parent[i] = 0;
		visited[i] = 0;
	}
	return (dijkstra2(lem, start, visited, parent));
}
