/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:20:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/01 18:12:17 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int philo, int type)
{
	pthread_mutex_lock(&(data->writing));
	if (data->status == DIED)
	{
		pthread_mutex_unlock(&(data->writing));
		return (1);
	}
	printf("%lld ", (timeinmilliseconds() - data->init_time));
	data->init_time = data->init_time;
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
	{
		printf("died\n");
		data->status = DIED;
	}
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
	usleep(50);
	if (data->status == DIED || meal_handler(data, philo, 2))
		return ;
	pthread_mutex_lock(&(data->fork[philo - 1]));
	print_action(data, philo, FORK);
	if (philo == data->philosophers)
		pthread_mutex_lock(&(data->fork[0]));
	else
		pthread_mutex_lock(&(data->fork[philo]));
	print_action(data, philo, FORK);
	if (meal_handler(data, philo, 1))
		put_fork_back(data, philo);
}

void	put_fork_back(t_data *data, int philo)
{
	pthread_mutex_unlock(&(data->fork[philo - 1]));
	if (philo == data->philosophers)
		pthread_mutex_unlock(&(data->fork[0]));
	else
		pthread_mutex_unlock(&(data->fork[philo]));
}
