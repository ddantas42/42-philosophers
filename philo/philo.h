/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:39:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/24 00:00:36 by ddantas-         ###   ########.fr       */
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
# define ALIVE 6

typedef struct phil_lst
{
	int				philo;
	int				fork;
	struct phil_lst	*next;
}				t_philo;

typedef struct philo_data {
	int				philosophers;
	int				thread;
	int				status;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	long long		init_time;
	int				test;
	pthread_t		*id;
	pthread_mutex_t	writing;
	pthread_mutex_t	fork[32767];
	t_philo			*philo_lst;
}				t_data;

/*			atoi.c				*/
int			ft_atoi_while_1(const char *str);
int			ft_atoi_if(const char *str, int *n);
int			ft_atoi(const char *str);

/*			philo_action.c		*/
int			print_action(t_data *data, int philo, int type);
void		seek_fork(t_data *data, int philo);

/*			philo_utils.c		*/
int			free_everything(t_data *data, int error);
long long	timeinmilliseconds(void);
t_philo		*init_lst(t_philo *lst, int philo);
int			init_table(t_data *data, int ac, char **av);
int			init_threads(t_data *data);

/*			philo.c				*/
void		*thread(void *arg);

#endif