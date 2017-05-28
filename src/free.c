/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 14:54:55 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 15:16:30 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_dbl(char **str)
{
	int		i;

	if (str)
	{
		i = 0;
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void		free_lst(t_ln **lst)
{
	t_ln	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->line);
		ft_memdel((void**)lst);
		*lst = tmp;
	}
}

void		free_all(t_lem *lem)
{
	int		i;

	i = -1;
	if (lem->map)
	{
		while (++i < lem->rooms_nr)
			if (lem->map[i])
				free(lem->map[i]);
		free(lem->map);
	}
	if (lem->lines)
		free_lst(&lem->lines);
	i = -1;
	while (++i < lem->rooms_nr)
		if (lem->rooms[i].name)
			free(lem->rooms[i].name);
}
