/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:40:18 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/04 14:30:52 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	meal_handler(t_data *data, int philo, int check)
{
	long long	time;
	t_philo		*temp;

	temp = data->philo_lst;
	while (temp && temp->philo != philo)
		temp = temp->next;
	if (data->status == ALIVE && check > 0)
	{
		time = (timeinmilliseconds() - data->init_time) - temp->last_ate;
		if (temp->last_ate > 0 && time > data->t_die)
		{
			usleep(data->t_die * 1000);
			print_action(data, philo, DIED);
			return (1);
		}
		return (0);
	}
	if (data->status == ALIVE && (long long)(TIME - temp->last_ate) >= data->t_die)
	{
		printf("philo %d last ate = %lld\n", philo, temp->last_ate);
		print_action(data, philo, DIED);
		return (1);
	}
	return (0);
}

int	philo_prep(t_data *data, int philo, int type)
{
	t_philo	*temp;

	temp = data->philo_lst;
	while (temp && temp->philo != philo)
		temp = temp->next;
	if (type == EATING)
		temp->last_ate = TIME;
	if (type == EATING && data->status == ALIVE && data->t_die < data->t_eat)
	{
		usleep(data->t_die * 1000);
		put_fork_back(data, temp->philo);
		print_action(data, philo, DIED);
		return (1);
	}
	else if (type == SLEEPING && data->status == ALIVE)
	{
		if (data->t_die >= data->t_eat + data->t_sleep)
			return (0);
		if (data->t_die - data->t_eat > 0)
			usleep((data->t_die - data->t_eat) * 1000);
		print_action(data, philo, DIED);
		return (1);
	}
	if (type == SLEEPING && philo == 2)
		printf("time = %lld\n", TIME);
	return (0);
}

int	ate_enough(t_data *data, int current_philo)
{
	t_philo	*temp;

	if (data->status == DIED)
		return (1);
	if (data->must_eat < 0)
		return (0);
	temp = data->philo_lst;
	while (current_philo > temp->philo)
		temp = temp->next;
	temp->ate++;
	temp = data->philo_lst;
	while (temp)
	{
		if (temp->ate < data->must_eat)
			return (0);
		temp = temp->next;
	}
	put_fork_back(data, current_philo);
	data->status = DIED;
	return (1);
}
