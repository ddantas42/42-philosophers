/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:39:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/20 15:22:51 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef struct fork_lst
{
	int				philosopher;
	int				fork;
	int				pos;
	struct fork_lst	*next;
	struct fork_lst	*prev;
}				t_fork;

typedef struct philo_data {
	int				philosophers;
	int				forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	long long		init_time;
	int				test;
	pthread_mutex_t	writing;
	t_fork			fork_lst;
}				t_data;

/*			atoi.c				*/
int			ft_atoi_while_1(const char *str);
int			ft_atoi_if(const char *str, int *n);
int			ft_atoi(const char *str);

/*			philo_utils.c		*/
int			free_everything(t_fork *lst, int error);
long long	timeInMilliseconds(void);
int			print_action(t_data *data, int philo, int type);


/*			philo.c				*/
void		*thread(void *param);
int			init_table(t_data *data, int ac, char **av);
int			init_threads(t_data *data);

#endif