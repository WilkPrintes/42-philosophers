/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:24:19 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/23 18:38:29 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_geral(t_geral *geral, char **argv)
{
	geral->forks = ft_calloc (sizeof(int), ft_atoi(argv[1]));
    geral->total_fork = ft_atoi(argv[1]);
	geral->death = 0;
	geral->t_die = ft_atoi(argv[2]) * 1000;
	geral->t_eat = ft_atoi(argv[3]) * 1000;
	geral->t_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		geral->m_eat = ft_atoi(argv[5]);
	else
		geral->m_eat = -1;
	geral->t_init = current_time();
	pthread_mutex_init(&geral->lock, NULL);
}

void create_philo(t_philo *philo, t_geral *geral)
{
	philo->eat = 0;
	philo->geral = geral;
	philo->last_eat = geral->t_init = current_time();
}

void all_philos(int c_philos, t_philo *philos, t_geral *geral)
{
	int i;

	i = 0;
	while (i < c_philos)
	{
		create_philo(&philos[i], geral);
		philos[i].id = i;
		pthread_create(&philos[i].thread, NULL, philo_func, &philos[i]);	
		i++;
	}
}