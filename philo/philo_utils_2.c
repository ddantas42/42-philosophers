/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:40:18 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/25 16:20:33 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int wait(t_data *data, int time_ms)
{
	int	n;

	n = 0;
	while (n < time_ms)
	{
		if (data->status == DIED)
			break ;
		usleep(TIME);
		n++;
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
