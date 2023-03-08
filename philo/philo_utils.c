/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:52:04 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/08 15:52:47 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_everything(t_data *data, int error)
{
	t_philo	*temp;
	int		n;

	while (data->philo_lst != NULL)
	{
		temp = data->philo_lst;
		data->philo_lst = data->philo_lst->next;
		free(temp);
	}
	n = 0;
	while (n <= data->thread - 1)
		pthread_mutex_destroy(&(data->fork)[n++]);
	pthread_mutex_destroy(&(data->writing));
	if (data->id != NULL)
		free(data->id);
	if (error)
		return (1);
	return (0);
}

long long	timeinmilliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

t_philo	*init_lst(t_philo *lst, int philo)
{
	int		n;
	t_philo	*new;
	t_philo	*temp;

	n = 0;
	while (n++ < philo)
	{
		temp = lst;
		while (temp != NULL && temp->next != NULL)
			temp = temp->next;
		new = (t_philo *)malloc(sizeof(t_philo));
		if (!new)
			return ((t_philo *)1);
		new->ate = 0;
		new->last_ate = 0;
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
	else
		data->must_eat = -1;
	data->status = ALIVE;
	data->dead_philo = 0;
	return (0);
}

int	init_threads(t_data *data, int n)
{
	if (pthread_mutex_init(&(data->writing), NULL) != 0)
		return (1);
	data->id = (pthread_t *)malloc(sizeof(pthread_t) * data->philosophers + 1);
	if (!(data->id))
		return (1);
	while (n < data->philosophers)
	{
		data->thread = n + 1;
		data->init_time = timeinmilliseconds();
		if (pthread_mutex_init(&(data->fork[n]), NULL) != 0)
			return (1);
		if (pthread_create(&(data->id)[n++], NULL, &thread, data) != 0)
			return (1);
		usleep(100);
	}
	if (pthread_create(&(data->id)[n], NULL, &death_checker, data) != 0)
		return (1);
	n = 0;
	while (n < data->philosophers + 1)
	{
		usleep(50);
		pthread_join((data->id)[n++], NULL);
	}
	free(data->id);
	data->id = NULL;
	return (0);
}
