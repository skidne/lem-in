/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:17:55 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 19:29:23 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_command(t_lem lem, char *line)
{
	if (!line)
		ft_err(lem, "empty line");
	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		return (1);
	else if (line[0] == '#')
		return (2);
	return (0);
}

int			check_room(char *line)
{
	char	**w;
	int		ret;

	ret = 0;
	w = ft_strsplit(line, ' ');
	if (count_words(w) == 3 && w[0] && w[1] && w[2] && ft_number(w[1]) &&
		ft_number(w[2]) && w[0][0] != 'L')
		ret = 1;
	free_dbl(w);
	return (ret);
}

int			check_link(char *line, t_lem lem)
{
	char	**w;
	int		ret;

	ret = 0;
	w = ft_strsplit(line, '-');
	if (count_words(w) == 2 && w[0] && w[1] &&
		room_index(lem, w[0]) > -1 && room_index(lem, w[1]) > -1)
		ret = 1;
	else
		ft_err(lem, "links: [room-name1-room_name2]");
	free_dbl(w);
	return (ret);
}

void			create_room(char *line, t_type typ, t_lem *lem)
{
	char		**w;

	w = ft_strsplit(line, ' ');
	if (count_words(w) == 3 && ft_number(w[1]) && ft_number(w[2]) &&
		w[0][0] != 'L')
	{
		lem->rooms[lem->rooms_nr].name = ft_strdup(w[0]);
		lem->rooms[lem->rooms_nr].type = typ;
		lem->rooms[lem->rooms_nr].ants = (typ == start_room)
			? lem->total_ants : 0;
		lem->rooms[lem->rooms_nr].full = 0;
		lem->rooms[lem->rooms_nr].dist = 0;
		if ((typ == start_room && lem->start > -1) ||
			(typ == end_room && lem->end > -1))
			ft_err(*lem, "repeated start or end commands");
		if (typ == start_room)
			lem->start = lem->rooms_nr;
		else if (typ == end_room)
			lem->end = lem->rooms_nr;
		if (lem->rooms_nr++ == MSIZE - 1)
			ft_err(*lem, "too many rooms. exiting...");
	}
	else
		ft_err(*lem, "rooms: [room_name x_coord y_coord]");
	free_dbl(w);
}

void			do_command(char *line, t_lem *lem)
{
	t_type		tp;

	if (!ft_strcmp(line, "##start"))
		tp = start_room;
	else
		tp = end_room;
	while (get_next_line(0, &line) > 0)
	{
		add_line(&lem->lines, line, *lem);
		if (check_command(*lem, line) == 2)
			continue;
		else if (check_room(line))
		{
			create_room(line, tp, lem);
			break ;
		}
		else
			ft_err(*lem, "Invalid line");
	}
	free(line);
}
