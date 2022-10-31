/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:24:19 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/31 03:55:18 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_core *core);

void	init_core(t_core *core, char **argv)
{
	core->total_fork = ft_atoi(argv[1]);
	core->forks = (pthread_mutex_t *)malloc
		(sizeof (pthread_mutex_t) * core->total_fork);
	core->death = 0;
	core->t_die = ft_atoi(argv[2]) * 1000;
	core->t_eat = ft_atoi(argv[3]) * 1000;
	core->t_sleep = ft_atoi(argv[4]) * 1000;
	core->all_full = 0;
	if (argv[5])
		core->m_eat = ft_atoi(argv[5]);
	else
		core->m_eat = -1;
	core->t_init = current_time();
	pthread_mutex_init(&core->lock, NULL);
	init_mutex(core);
}

void	init_mutex(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->total_fork)
	{
		pthread_mutex_init(&core->forks[i], NULL);
		i++;
	}
}

void	create_philo(t_philo *philo, t_core *core)
{
	philo->eat = 0;
	philo->core = core;
	philo->last_eat = current_time();
}

void	all_philos(int c_philos, t_philo *philos, t_core *core)
{
	int	i;

	i = 0;
	while (i < c_philos)
	{
		create_philo(&philos[i], core);
		philos[i].id = i + 1;
		philos[i].fork_left = &core->forks[i];
		if (c_philos > 1)
		{
			if (i + 1 == c_philos)
				philos[i].fork_right = &core->forks[0];
			else
				philos[i].fork_right = &core->forks[i + 1];
		}
		else
			philos[i].fork_right = NULL;
		pthread_create(&philos[i].thread, NULL, philo_core, &philos[i]);
		i++;
	}
}
