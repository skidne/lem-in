/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:16:41 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 16:11:51 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_err(t_lem lem, char *str)
{
	ft_putstr_fd("ERROR: ", 2);
	ft_putendl_fd(str, 2);
	free_all(&lem);
	exit(-1);
}

int		count_words(char **str)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	if (!str || !(*str))
		return (0);
	while (str[++i])
		cnt++;
	return (cnt);
}

int		room_index(t_lem lem, char *name)
{
	int	i;

	i = -1;
	while (++i < lem.rooms_nr)
		if (!ft_strcmp(lem.rooms[i].name, name))
			return (i);
	return (-1);
}

int			is_full(int u, t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->rooms_nr)
		if (!lem->rooms[i].full && lem->map[i][u])
			return (0);
	return (1);
}

int			gotta_visit(int *visited, t_lem *lem)
{
	int		i;

	i = -1;
	while (++i < lem->rooms_nr)
		if (!visited[i])
			return (1);
	return (0);
}
