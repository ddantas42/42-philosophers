/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:20:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/10 12:48:43 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int philo, int type)
{
	t_philo	*temp;

	pthread_mutex_lock(&(data->writing));
	if (data->status == DIED)
	{
		pthread_mutex_unlock(&(data->writing));
		return (1);
	}
	temp = data->philo_lst;
	while (temp && temp->philo != philo)
		temp = temp->next;
	printf("%lld ", (timeinmilliseconds() - temp->init_time));
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
		data->dead_philo = philo;
		data->status = DIED;
	}
	pthread_mutex_unlock(&(data->writing));
	return (0);
}

void	seek_fork_2(t_data *data, int philo)
{
	if (philo == data->philosophers)
	{
		pthread_mutex_lock(&(data->fork[0]));
		if (data->status == DIED)
		{
			put_fork_back(data, philo);
			return ;
		}
	}
	else
	{
		pthread_mutex_lock(&(data->fork[philo]));
		if (data->status == DIED)
		{
			put_fork_back(data, philo);
			return ;
		}
	}
	print_action(data, philo, FORK);
	if (data->status == DIED || meal_handler(data, philo, 1))
		put_fork_back(data, philo);
}

void	seek_fork(t_data *data, int philo)
{
	if (data->status == DIED || meal_handler(data, philo, 2))
		return ;
	usleep(100);
	pthread_mutex_lock(&(data->fork[philo - 1]));
	if (data->status == DIED)
	{
		pthread_mutex_unlock(&(data->fork[philo - 1]));
		return ;
	}
	print_action(data, philo, FORK);
	usleep(100);
	seek_fork_2(data, philo);
}

void	put_fork_back(t_data *data, int philo)
{
	pthread_mutex_unlock(&(data->fork[philo - 1]));
	if (philo == data->philosophers)
		pthread_mutex_unlock(&(data->fork[0]));
	else
		pthread_mutex_unlock(&(data->fork[philo]));
}
