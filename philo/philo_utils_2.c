/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:40:18 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/01 16:01:39 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_action(t_data *data, int philo)
{
	print_action(data, philo, EATING);
	usleep(data->t_die * 1000);
	print_action(data, philo, DIED);
	data->status = DIED;
	return (1);
}

long long	meal_handler(t_data *data, int philo, int check)
{
	long long	time;
	t_philo		*temp;
	
	if (check == 2 && data->t_die < data->t_eat)
		return (last_action(data, philo));
	temp = data->philo_lst;
	while (temp && temp->philo != philo)
		temp = temp->next;
	if (check > 0)
	{
		time = timeinmilliseconds() - temp->last_ate;
		if (temp->last_ate > 0 && time > data->t_die)
		{
			print_action(data, philo, DIED);
			data->status = DIED;
			return (1);
		}
		temp->last_ate = timeinmilliseconds() + data->t_eat;
		return (0);
	}
	if (timeinmilliseconds() - temp->last_ate > data->t_die)
	{
		print_action(data, philo, DIED);
		data->status = DIED;
		return (1);
	}	
	return (0);	
}

/*
int wait(t_data *data, int time_ms)
{
	while (time_ms--)
	{
		if (data->status == DIED)
			break ;
		usleep(TIME);
	}
	return (0);
}
*/

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
