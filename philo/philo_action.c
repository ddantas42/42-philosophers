/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:20:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/23 23:24:43 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int philo, int type)
{
	pthread_mutex_lock(&(data->writing));
	printf("%lld ", (timeinmilliseconds() - data->init_time));
	printf("%d ", philo);
	if (type == FORK)
		printf("has taken a fork\n");
	else if (type == EATING)
		printf("is eating\n");
	else if (type == SLEEPING)
		printf("is sleeping\n");
	else if (type == THINKING)
		printf("is thinking\n");
	else if (type == DIED)
		printf("died\n");
	pthread_mutex_unlock(&(data->writing));
	return (0);
}

void	seek_fork(t_data *data, int philo)
{
	if (data->philosophers == 1)
	{
		print_action(data, philo, FORK);
		usleep(data->t_die * 1000);
		print_action(data, philo, DIED);
		data->status = DIED;
		return ;
	}
	pthread_mutex_lock(&(data->fork[philo - 1]));
}
