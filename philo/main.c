/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:51:40 by phelebra          #+#    #+#             */
/*   Updated: 2023/05/16 14:19:36 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments.\n"));
	char *v = *av;
	if (*v)
		return 0;

}