/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:32 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/10 09:23:15 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *arg)
{
	t_data	*data;
	t_philo	*temp;

	data = (t_data *)arg;
	temp = data->philo_lst;
	while (data->status == ALIVE)
	{
		if (!temp)
			temp = data->philo_lst;
		if (meal_handler(data, temp->philo, 0))
			put_fork_back(data, temp->philo);
		temp = temp->next;
	}
	return (0);
}

int	thread_2(t_data *data, int current_philo, t_philo *philo)
{
	if (print_action(data, philo, current_philo, SLEEPING))
		return (1);
	if (philo_prep(data, current_philo, SLEEPING, philo))
		return (1);
	usleep(data->t_sleep * 1000);
	if (print_action(data, philo, current_philo, THINKING))
		return (1);
	return (0);
}

void	*thread(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		current_philo;

	data = ((t_data *) arg);
	current_philo = data->thread;
	philo = data->philo_lst;
	while (philo && philo->philo != current_philo)
		philo = philo->next;
	while (data->status == ALIVE)
	{
		seek_fork(data, current_philo, philo);
		if (print_action(data, philo, current_philo, EATING))
			return (0);
		if (philo_prep(data, current_philo, EATING, philo))
			return (0);
		usleep(data->t_eat * 1000);
		put_fork_back(data, current_philo);
		if (ate_enough(data, current_philo, philo))
			return (0);
		if (thread_2(data, current_philo, philo))
			return (0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			n;

	if ((ac != 5 && ac != 6))
	{
		printf("Usage: ./phile [philosophers] [time to die] [time to eat] [time to sleep] [opt: Stops after X meals]\n");
		return (1);
	}
	if (init_table(&data, ac, av))
		return (1);
	data.philo_lst = 0;
	n = 0;
	data.philo_lst = init_lst(data.philo_lst, data.philosophers);
	if (data.philo_lst == (t_philo *)1)
		return (free_everything(&data, 1));
	if (init_threads(&data, n))
		return (free_everything(&data, 1));
	return (free_everything(&data, 0));
}
