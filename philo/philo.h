/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:39:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/10 09:23:57 by ddantas-         ###   ########.fr       */
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
	int				ate;
	long long		last_ate;
	long long		init_time;
	struct phil_lst	*next;
}				t_philo;

typedef struct philo_data {
	int				philosophers;
	int				thread;
	int				dead_philo;
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
int			print_action(t_data *data, t_philo *phil, int philo, int type);
void		seek_fork_2(t_data *data, int philo, t_philo *phil);
void		seek_fork(t_data *data, int philo, t_philo *phil);
void		put_fork_back(t_data *data, int philo);

/*			philo_utils.c		*/
int			free_everything(t_data *data, int error);
long long	timeinmilliseconds(void);
t_philo		*init_lst(t_philo *lst, int philo);
int			init_table(t_data *data, int ac, char **av);
int			init_threads(t_data *data, int n);

/*			philo_utils.c		*/
int			last_action(t_data *data, int philo);
long long	meal_handler(t_data *data, int philo, int check);
int			philo_prep(t_data *data, int philo, int type, t_philo *phil);
int			ate_enough(t_data *data, int current_philo, t_philo *phil);

/*			philo.c				*/
void		*death_checker(void *arg);
int			thread_2(t_data *data, int current_philo, t_philo *phil);
void		*thread(void *arg);

#endif