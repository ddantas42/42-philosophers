/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:32 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/01 20:55:05 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *arg)
{
	t_data	*data;
	int		current_philo;

	data = ((t_data *) arg);
	data->init_time = timeinmilliseconds();
	current_philo = data->thread;
	while (data->status == ALIVE)
	{
		seek_fork(data, current_philo);
		if (print_action(data, current_philo, EATING))
			return (0);
		usleep(data->t_eat * 1000);
		//wait(data, data->t_eat);
		if (ate_enough(data, current_philo))
			return (0);
		put_fork_back(data, current_philo);
		if (print_action(data, current_philo, SLEEPING))
			return (0);
		if (philo_sleep(data, current_philo, data->t_sleep));
			return (0);
		usleep(data->t_sleep * 1000);
		//wait(data, data->t_sleep);
		if (meal_handler(data, current_philo, 0))
			return (0);
		if (print_action(data, current_philo, THINKING))
			return (0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			n;

	if ((ac != 5 && ac != 6))
		return (0);
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
