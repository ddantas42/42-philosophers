/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:32 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/19 17:44:37 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *param)
{
	t_data	*data;
	int		philo;

	data = ((t_data *) param);

	int	n = 5;
	pthread_mutex_lock(&(data->writing));
	philo = data->forks++;
	pthread_mutex_unlock(&(data->writing));

	while (n--)
	{
		print_action(*data, philo, EATING);
		usleep(data->t_eat * 1000);
		print_action(*data, philo, SLEEPING);
		usleep(data->t_sleep * 1000);
		print_action(*data, philo, THINKING);
		usleep(1000 * 1000);

	}
	print_action(*data, philo, DIED);
	return (0);
}

int	init_table(t_data *data, int ac, char **av)
{
	struct timeval	ct;

	data->philosophers = ft_atoi(av[1]);
	if (data->philosophers < 1)
		return (1);
	data->forks = data->philosophers;
	data->t_die = ft_atoi(av[2]);
	if (data->t_die < 1)
		return (1);
	data->t_eat = ft_atoi(av[3]);
	if (data->t_eat < 1)
		return (1);
	data->t_sleep = ft_atoi(av[4]);
	if (data->t_sleep < 1)
		return (1);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 1)
			return (1);
	}
	if (gettimeofday(&ct, NULL) != 0)
		return (1);
	data->init_time = 1000 * ct.tv_usec + ct.tv_usec / 1000;
	return (0);
}

int init_threads(t_data *data)
{
	pthread_t	id[data->philosophers];
	int			n;

	n = 0;
	data->init_time = timeInMilliseconds();
	if (pthread_mutex_init(&(data->writing), NULL) != 0)
		return (1);
	while (n < data->philosophers)
	{
		if (pthread_create(&id[n++], NULL, &thread, data) != 0)
			return (1);
	}
	n = 0;
	data->forks = 1;
	while (n < data->philosophers)
		pthread_join(id[n++], NULL);
	return (0);
}	

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6))
		return (0);
	
	printf("Thread testing starting\n");
	if (init_table(&data, ac, av) || init_threads(&data))
		return (1);
	pthread_mutex_destroy(&(data.writing));
	return (0);
}