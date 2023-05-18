/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:51:28 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/18 16:37:22 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	timesince(struct timeval then, struct timeval now)
{
	unsigned long	start;
	unsigned long	end;

	start = (then.tv_sec * 1000) + round(then.tv_usec / 1000);
	end = (now.tv_sec * 1000) + round(now.tv_usec / 1000);
	return (end - start);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		base;

	i = 0;
	sign = 1;
	base = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] <= ' ' && str[i] != '\e')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		base = 10 * base + (str[i++] - '0');
	if ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		return (-1);
	return (base * sign);
}

void	init_others_others(t_plato **platos, int i)
{
	(*platos)[i].num = (*platos)[0].num;
	(*platos)[i].die = (*platos)[0].die;
	(*platos)[i].eat = (*platos)[0].eat;
	(*platos)[i].nap = (*platos)[0].nap;
	(*platos)[i].goal = (*platos)[0].goal;
}

void	init_others(t_plato **platos, pthread_mutex_t **mx_vidle, int *forks)
{
	int				i;
	int				*alive;
	pthread_mutex_t	*mx_out;

	forks = malloc((*platos)->num * sizeof(int));
	alive = malloc(1 * sizeof(int));
	alive[0] = 1;
	i = 0;
	(*platos)[0].forks = forks;
	(*platos)[0].snacks = 0;
	(*platos)[0].alive = alive;
	(*platos)[0].init_sleep = 1;
	mx_out = malloc(1 * sizeof(pthread_mutex_t));
	(*platos)[0].mx_out = mx_out;
	while (++i < (*platos)[0].num)
	{
		init_others_others(platos, i);
		(*platos)[i].alive = alive;
		(*platos)[i].init_sleep = 1;
		(*platos)[i].snacks = 0;
		(*platos)[i].forks = forks;
		(*platos)[i].mx_vidle = *mx_vidle;
		(*platos)[i].mx_out = mx_out;
		gettimeofday(&(*platos)[i].t_created, NULL);
	}
}

void	init_plato(int ac, char **av, t_plato **platos,
	pthread_mutex_t	**mx_vidle)
{
	static int		*forks;

	if (ac < 5 || ac > 6)
		return (printf("ERROR: Incorect number of arguments\n"), exit(1));
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
		return (printf("ERROR: Invalid argument\n"), exit(2));
	*platos = malloc((ft_atoi(av[1]) * sizeof(t_plato))
			+ ft_atoi(av[1]) * sizeof(int));
	*mx_vidle = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	(*platos)[0].mx_vidle = *mx_vidle;
	(*platos)[0].num = ft_atoi(av[1]);
	(*platos)[0].die = ft_atoi(av[2]);
	(*platos)[0].eat = ft_atoi(av[3]);
	(*platos)[0].nap = ft_atoi(av[4]);
	gettimeofday(&(*platos)[0].t_created, NULL);
	if (ac == 6)
	{
		(*platos)[0].goal = ft_atoi(av[5]);
		if ((*platos)[0].goal < 0)
			return (free(*platos), printf("ERROR: Invalid argument\n"), exit(2));
	}
	else
		(*platos)[0].goal = -1;
	init_others(platos, mx_vidle, forks);
}
