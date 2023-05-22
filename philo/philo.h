/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:52:18 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/22 13:36:38 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_plato
{
	pthread_mutex_t	*mx_vidle;
	pthread_mutex_t	*mx_out;
	int				id;
	int				eat;
	int				die;
	int				nap;
	int				goal;
	int				num;
	int				snacks;
	int				*alive;
	int				init_sleep;
	int				*forks;
	struct timeval	t_created;
	struct timeval	t_lastmeal;
	pthread_t		thread;
}				t_plato;

/* TIMER */
void				start_action(int duration);

/* UTILS */
unsigned long		timesince(struct timeval then, struct timeval now);
int					ft_atoi(const char *str);
void				init_plato(int ac, char **av, t_plato **platos,
						pthread_mutex_t	**mx_vidle);

/* DO */
void				do_sleep(t_plato **plato);
int					do_eat(t_plato **plato);

/* MAIN */
int					is_alive(t_plato **plato);

#endif