/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:32 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/18 14:40:35 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *param)
{
	t_data	*data;

	data = ((t_data *) param);
	
	pthread_mutex_lock(&(data->lock));
	printf("stuck?\n");
	int	n = 1000000;
	while (n--)
	{
		data->test++;
	}

	pthread_mutex_unlock(&(data->lock));
	return (0);
}

int	init_table(t_data *data, int ac, char **av)
{
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
	return (0);
}

int init_threads(t_data *data)
{
	pthread_t	id1;
	pthread_t	id2;

	if (pthread_mutex_init(&(data->lock), NULL) != 0)
		return (1);
	if (pthread_create(&id1, NULL, &thread, data) != 0)
		return (1);
	if (pthread_create(&id2, NULL, &thread, data) != 0)
		return (1);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	return (0);
}	

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6))
		return (0);
	
	printf("Thread testing starting\n");
	data.test = 0;
	if (init_table(&data, ac, av) || init_threads(&data))
		return (1);
	
	printf("data.test = %d\n", data.test);
	//pthread_mutex_destroy(&(data.lock));
	return (0);
}