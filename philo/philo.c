/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:32 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/22 12:30:38 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread(void *param)
{
	t_data	*data;
	int		current_philo;

	data = ((t_data *) param);
	data->init_time = timeInMilliseconds();
	current_philo = data->philo_thread;

	print_action(data, current_philo, FORK);
	print_action(data, current_philo, FORK);
	print_action(data, current_philo, EATING);
	usleep(data->t_eat * 1000);
	print_action(data, current_philo, SLEEPING);
	usleep(data->t_sleep * 1000);
	print_action(data, current_philo, THINKING);
	usleep(data->t_die  * 1000);
	print_action(data, current_philo, DIED);

	return (0);
}

t_fork	*init_lst(t_fork *lst, int philo)
{
	int		n;
	t_fork	*new;
	t_fork	*temp;

	n = 0;
	while (n++ < philo)
	{
		temp = lst;
		while (temp != NULL && temp->next != NULL)
			temp = temp->next;
		new = (t_fork *)malloc(sizeof(t_fork));
		if (!new)
		{
			free(new);
			free_everything(lst, 1);
			return ((t_fork *)1);
		}
		new->fork = n;
		new->philo = n;
		new->next = NULL;
		if (temp != NULL)
			temp->next = new;
		else
			lst = new;
	}
	return (lst);
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
	pthread_t	id[data->philosophers];
	int			n;

	n = 0;
	if (pthread_mutex_init(&(data->writing), NULL) != 0)
		return (1);
	while (n < data->philosophers)
	{
		data->philo_thread = n + 1;
		if (pthread_create(&id[n++], NULL, &thread, data) != 0)
			return (1);
		usleep(100);
	}
	n = 0;
	while (n < data->philosophers)
	{
		pthread_join(id[n++], NULL);
		usleep(50);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;

	if ((ac != 5 && ac != 6))
		return (0);
	
	if (init_table(&data, ac, av))
		return (1);
	data.fork_lst = 0;
	data.fork_lst = init_lst(data.fork_lst, data.philosophers);

	if (data.fork_lst == (t_fork *)1)
		return (1);
		
	printf("Thread testing starting\n");
	if (init_threads(&data))
		return (free_everything(data.fork_lst, 1));

	pthread_mutex_destroy(&(data.writing));
	
	return (free_everything(data.fork_lst, 0));
}