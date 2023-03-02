/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:40:18 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/02 15:04:54 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	meal_handler(t_data *data, int philo, int check)
{
	long long	time;
	t_philo		*temp;

	temp = data->philo_lst;
	if (check > 0)
	{
		while (temp && temp->philo != philo)
			temp = temp->next;
		time = (timeinmilliseconds() - data->init_time) - temp->last_ate;
		if (temp->last_ate > 0 && time > data->t_die)
		{
			print_action(data, philo, DIED);
			return (1);
		}
		temp->last_ate = (timeinmilliseconds() - data->init_time);
		return (0);
	}
	if ((long long)(timeinmilliseconds() - data->init_time - temp->last_ate) >= data->t_die)
	{
		print_action(data, philo, DIED);
		return (1);
	}
	return (0);
}

int	philo_prep(t_data *data, int philo, int type)
{
	t_philo	*temp;

	if (type == EATING && data->status == ALIVE && data->t_die < data->t_eat)
	{
		temp = data->philo_lst;
		while (temp && temp->philo != philo)
			temp = temp->next;
		usleep(data->t_die * 1000);
		put_fork_back(data, temp->philo);
		print_action(data, philo, DIED);
		return (1);
	}
	else if (type == SLEEPING && data->status == ALIVE && data->t_die < data->t_sleep + data->t_eat)
	{
		temp = data->philo_lst;
		while (temp && temp->philo != philo)
			temp = temp->next;
		usleep(data->t_die * 1000);
		print_action(data, philo, DIED);
		return (1);
	}
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
