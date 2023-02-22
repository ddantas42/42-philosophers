/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:52:04 by ddantas-          #+#    #+#             */
/*   Updated: 2023/02/21 18:12:29 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_everything(t_fork *lst, int error)
{
	t_fork	*temp;

	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp); 
	}
	if (error)
		return (1);
	return (0);
}

long long	timeInMilliseconds(void)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

int	print_action(t_data *data, int philo, int type)
{
	pthread_mutex_lock(&(data->writing));
	printf("%d ", (timeInMilliseconds() - data->init_time));
	printf("%d ", philo);
	if (type == FORK)
		printf("has taken a fork\n");
	else if (type == EATING)	
		printf("is eating\n");
	else if (type == SLEEPING)	
		printf("is sleeping\n");
	else if (type == THINKING)	
		printf("is thinking\n");
	else if (type == DIED)	
		printf("died\n");
	pthread_mutex_unlock(&(data->writing));
	return (0);
}
/*
t_data	*ft_add_alst(t_data **alst, t_data *blst, int atoi)
{
	t_data	*new;
	t_data	*temp;

	temp = *alst;
	while (temp != NULL && temp->next != NULL)
		temp = temp->next;
	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
	{
		free(new);
		//shutdown
	}
	new->data = atoi;
	new->next = NULL;
	if (temp != NULL)
		temp->next = new;
	else
		*alst = new;
	return (0);
}*/
