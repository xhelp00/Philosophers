/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:19:39 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/19 15:56:06 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_sleep(t_plato **plato)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock((*plato)->mx_out);
	if ((*plato)->alive[0])
		printf("%-8lu %-3d  \033[30m\033[45mis sleeping\033[0m\n",
			timesince((*plato)->t_created, now), (*plato)->id + 1);
	pthread_mutex_unlock((*plato)->mx_out);
	start_action((*plato)->nap);
	gettimeofday(&now, NULL);
	pthread_mutex_lock((*plato)->mx_out);
	if ((*plato)->alive[0])
		printf("%-8lu %-3d  \033[30m\033[46mis thinking\033[0m\n",
			timesince((*plato)->t_created, now), (*plato)->id + 1);
	pthread_mutex_unlock((*plato)->mx_out);
}

void	taken(t_plato **plato)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock((*plato)->mx_out);
	if ((*plato)->alive[0])
		printf("%-8lu %-3d \033[0;33m took a fork\033[0m\n",
			timesince((*plato)->t_created, now), (*plato)->id + 1);
	pthread_mutex_unlock((*plato)->mx_out);
}

void	take_forks(t_plato **plato)
{
	pthread_mutex_lock(&(*plato)->mx_vidle[(*plato)->id]);
	(*plato)->forks[(*plato)->id] = 0;
	taken(plato);
	if ((*plato)->id == (*plato)->num - 1)
	{
		pthread_mutex_lock(&(*plato)->mx_vidle[0]);
		(*plato)->forks[0] = 0;
		taken(plato);
	}
	else
	{
		pthread_mutex_lock(&(*plato)->mx_vidle[(*plato)->id + 1]);
		(*plato)->forks[(*plato)->id + 1] = 0;
		taken(plato);
	}
}

void	put_forks(t_plato **plato)
{
	pthread_mutex_unlock(&(*plato)->mx_vidle[(*plato)->id]);
	(*plato)->forks[(*plato)->id] = 1;
	if ((*plato)->id == (*plato)->num - 1)
	{
		pthread_mutex_unlock(&(*plato)->mx_vidle[0]);
		(*plato)->forks[0] = 1;
	}
	else
	{
		pthread_mutex_unlock(&(*plato)->mx_vidle[(*plato)->id + 1]);
		(*plato)->forks[(*plato)->id + 1] = 1;
	}
}

int	do_eat(t_plato **plato)
{
	struct timeval	now;

	take_forks(plato);
	if (!is_alive(plato))
		return (put_forks(plato), 0);
	gettimeofday(&(*plato)->t_lastmeal, NULL);
	gettimeofday(&now, NULL);
	pthread_mutex_lock((*plato)->mx_out);
	if ((*plato)->alive[0])
		printf("%-8lu %-3d  \033[30m\033[42mis eating his spaghetti code\033[0m\n",
			timesince((*plato)->t_created, now), (*plato)->id + 1);
	pthread_mutex_unlock((*plato)->mx_out);
	start_action((*plato)->eat);
	put_forks(plato);
	(*plato)->snacks++;
	return (1);
}
