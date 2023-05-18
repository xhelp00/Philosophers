/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:52:18 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/17 12:47:03 by phelebra         ###   ########.fr       */
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
	pthread_mutex_t	*mx_vidle;
	pthread_mutex_t	*mx_out;
}				t_plato;

#endif