/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alldigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:10:27 by pgore             #+#    #+#             */
/*   Updated: 2017/05/12 17:25:32 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_alldigit(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(str);
	while (i < n)
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
