/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgore <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:56:31 by pgore             #+#    #+#             */
/*   Updated: 2017/05/28 19:54:57 by pgore            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

# define ENDL ft_putchar('\n')
# define KDS "\x1B[1m\033[33m"
# define KDS2 "\x1B[1m\033[32m"
# define KMAG "\x1B[0m\033[32m"
# define KWHT "\033[37m"
# define KNRM "\x1B[0m"
# define STDIN 0
# define STDERR 2
# define INF INT_MAX
# define MSIZE 10000

#define LNEXT(lst) ((lst) = (lst->next))

typedef enum	e_type
{
	reg_room,
	start_room,
	end_room,
}				t_type;

typedef struct	s_rm
{
	char		*name;
	t_type		type;
	int			ants;
	int			full;
	int			dist;
}				t_rm;

typedef struct	s_ln
{
	char		*line;
	struct s_ln	*next;
}				t_ln;

typedef struct	s_lem
{
	int			**map;
	t_rm		rooms[MSIZE];
	int			rooms_nr;
	int			total_ants;
	int			i;
	int			flag;
	int			start;
	int			end;
	t_ln		*lines;
}				t_lem;

/*
**				read.c
*/

void			take_ants(t_lem *lem);
void			init_map(t_lem *lem);
void			take_link(char *line, t_lem *lem);
void			link_all(char *line, t_lem *lem);
t_lem			read_lemin(void);

/*
**				check.c
*/

int				check_command(t_lem lem, char *line);
int				check_room(char *line);
int				check_link(char *line, t_lem lem);
void			create_room(char *line, t_type typ, t_lem *lem);
void			do_command(char *line, t_lem *lem);

/*
**				utils.c
*/

void			ft_err(t_lem lem, char *str);
int				count_words(char **str);
int				room_index(t_lem lem, char *name);
int				is_full(int u, t_lem *lem);
int				gotta_visit(int *visited, t_lem *lem);

/*
**				dijkstra.c
*/

int				next_room(int *parent, int u, int start);
int				min_dist(int *visited, t_lem *lem);
int				dijkstra2(t_lem *lem, int start, int *visited, int *parent);
int				dijkstra(t_lem *lem, int start);

/*
**				print_subject.c
*/

t_ln			*create_line(char *line, t_lem lem);
void			add_line(t_ln **lst, char *line, t_lem lem);
void			print_lines(t_ln *lst);

/*
**				move.c
*/

void			dist_init(t_lem *lem);
void			init_ants(t_lem lem, int *arr);
void			print_sol(t_lem *lem, int room, int *ant_arr);
void			move_ants(t_lem lem);

/*
**				free.c
*/

void			free_dbl(char **str);
void			free_lst(t_ln **lst);
void			free_all(t_lem *lem);

#endif
