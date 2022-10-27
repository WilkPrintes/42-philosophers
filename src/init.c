/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:24:19 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/27 11:52:15 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutex(t_geral *geral);

void init_geral(t_geral *geral, char **argv)
{
    geral->total_fork = ft_atoi(argv[1]);
	geral->forks = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t) * geral->total_fork);
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
	init_mutex(geral);
}

void init_mutex(t_geral *geral)
{
	int i;

	i = 0;
	while(i < geral->total_fork)
	{
		pthread_mutex_init(&geral->forks[i], NULL);
		i++;
	}
}

void create_philo(t_philo *philo, t_geral *geral)
{
	philo->eat = 0;
	philo->geral = geral;
	philo->last_eat = current_time();
}

void all_philos(int c_philos, t_philo *philos, t_geral *geral)
{
	int i;

	i = 0;
	while (i < c_philos)
	{
		create_philo(&philos[i], geral);
		philos[i].id = i;
		philos[i].fork_left = &geral->forks[i];
		if (c_philos > 1)
		{
			if (i + 1 == c_philos)
				philos[i].fork_right = &geral->forks[0];
			else
				philos[i].fork_right = &geral->forks[i + 1];
		}
		else
			philos[i].fork_right = NULL;
		pthread_create(&philos[i].thread, NULL, philo_func, &philos[i]);	
		i++;
	}
}