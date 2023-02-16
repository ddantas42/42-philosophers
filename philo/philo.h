/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:39:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/15 16:24:56 by ddantas-         ###   ########.fr       */
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

typedef struct philo_data {
	int		philosophers;
	int		forks;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		must_eat;
}				t_data;

/*			atoi.c			*/
int	ft_atoi_while_1(const char *str);
int	ft_atoi_if(const char *str, int *n);
int	ft_atoi(const char *str);


/*			philo.c			*/

#endif