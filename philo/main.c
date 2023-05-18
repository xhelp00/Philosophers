/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:51:40 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/18 17:01:33 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alone(t_plato **plato)
{
	start_action((*plato)->die);
	printf("%-8d %-4s %-5s\n", (*plato)->die, "1", "\033[1;31mhas died\033[0m");
	free((*plato)->mx_vidle);
	free((*plato)->mx_out);
	free((*plato)->alive);
	free((*plato)->forks);
	free(*plato);
	exit(0);
}

void	odd_sleep(t_plato **plato)
{
	struct timeval	now;

	if ((*plato)->id % 2 == 0 && (*plato)->init_sleep)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock((*plato)->mx_out);
		if ((*plato)->alive[0])
			printf("%-8lu %-3d  \033[30m\033[45mis sleeping\033[0m\n",
				timesince((*plato)->t_created, now), (*plato)->id + 1);
		pthread_mutex_unlock((*plato)->mx_out);
		start_action((*plato)->nap);
		(*plato)->init_sleep = 0;
		gettimeofday(&now, NULL);
		pthread_mutex_lock((*plato)->mx_out);
		if ((*plato)->alive[0])
			printf("%-8lu %-3d  \033[30m\033[46mis thinking\033[0m\n",
				timesince((*plato)->t_created, now), (*plato)->id + 1);
		pthread_mutex_unlock((*plato)->mx_out);
	}
}

int	is_alive(t_plato **plato)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (!(*plato)->alive[0])
		return (0);
	if (timesince((*plato)->t_lastmeal, now) > (unsigned)(*plato)->die)
	{
		pthread_mutex_lock((*plato)->mx_out);
		if ((*plato)->alive[0])
		{
			(*plato)->alive[0] = 0;
			printf("%-8lu %-3d  \033[1;31mhas died\033[0m\n",
				timesince((*plato)->t_created, now), (*plato)->id + 1);
		}
		pthread_mutex_unlock((*plato)->mx_out);
		return (0);
	}
	return (1);
}

void	*routine(void *data)
{
	struct s_plato	*plato;

	plato = (struct s_plato *) data;
	gettimeofday(&(*plato).t_lastmeal, NULL);
	while (plato->alive[0])
	{
		odd_sleep(&plato);
		if (!do_eat(&plato))
			return (NULL);
		if (plato->snacks == plato->goal)
			return (NULL);
		do_sleep(&plato);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int				n;
	t_plato			*platos;
	pthread_mutex_t	*mx_vidle;

	init_plato(ac, av, &platos, &mx_vidle);
	if (platos[0].num == 1)
		alone(&platos);
	pthread_mutex_init(platos->mx_out, NULL);
	n = -1;
	while (++n < platos[0].num)
	{
		platos[n].id = n;
		platos[n].forks[n] = 1;
		pthread_mutex_init(&mx_vidle[n], NULL);
		pthread_create(&platos[n].thread, NULL, &routine, &platos[n]);
	}
	n = -1;
	while (++n < platos[0].num)
	{
		pthread_join(platos[n].thread, NULL);
		pthread_mutex_destroy(&mx_vidle[n]);
	}
	return (free(mx_vidle), free(platos->forks),
		pthread_mutex_destroy(platos->mx_out),
		free(platos->alive), free(platos->mx_out), free(platos), 0);
}
