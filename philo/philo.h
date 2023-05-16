/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:52:18 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/16 13:52:18 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eat;
	int				die;
	int				nap;
	int				to_eat;
	int				n_phil;
	int				n_ate;
	int				*alive;
	int				init_sleep;
	int				*forks;
	struct timeval	t_created;
	struct timeval	t_lastmeal;
	pthread_t		thread;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*megaphone;
}				t_philo;

#endif