/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_subject.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 14:13:56 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 16:29:52 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ln		*create_line(char *line, t_lem lem)
{
	t_ln	*lst;

	if (!(lst = (t_ln*)malloc(sizeof(t_ln))))
		ft_err(lem, "mem. alloc failed");
	lst->line = ft_strdup(line);
	lst->next = NULL;
	return (lst);
}

void		add_line(t_ln **lst, char *line, t_lem lem)
{
	t_ln	*tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next)
			LNEXT(tmp);
		tmp->next = create_line(line, lem);
	}
	else
		*lst = create_line(line, lem);
}

void		print_lines(t_ln *lst)
{
	t_ln	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_putendl(tmp->line);
		LNEXT(tmp);
	}
	ENDL;
}
