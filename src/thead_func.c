/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:28:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/26 17:14:11 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_philo *philo);
void leave_fork(t_philo *philo);

void *alive_func(void *parameter)
{
	t_geral *geral;

	geral = (t_geral *) parameter;
	while (1)
	{
		pthread_mutex_lock(&geral->lock);
		if (geral->death != 0)
			break ;
		pthread_mutex_unlock(&geral->lock);
	}
	pthread_detach(geral->alive);
	return (NULL);
}

void *philo_func(void *parameter)
{
	t_philo *philo;
	time_t t_init;
	int ok;

	philo = (t_philo *) parameter;
	ok = 0;
	t_init = philo->geral->t_init;
	while ((current_time() - philo->last_eat) < philo->geral->t_die)
	{
		pthread_mutex_lock(&philo->geral->lock);
		if (take_fork(philo) == 0)
			ok = 1;
		pthread_mutex_unlock(&philo->geral->lock);
		if (ok == 1)
		{
			printf("%lu philosopher %d take a fork\n", passed_time(philo->geral), philo->id);
			printf("%lu philosopher %d is eating\n", passed_time(philo->geral), philo->id);
			usleep(philo->geral->t_eat);
			pthread_mutex_lock(&philo->geral->lock);
			leave_fork(philo);
			pthread_mutex_unlock(&philo->geral->lock);
			philo->last_eat = current_time();
			philo->eat++;
			if (philo->geral->m_eat != -1 && philo->geral->m_eat == philo->eat)
			{
				philo->geral->death = 1;
				return(NULL);
			}
			printf("%lu philosopher %d is sleeping\n", passed_time(philo->geral), philo->id);
			usleep(philo->geral->t_sleep);
			printf("%lu philosopher %d is thinking\n", passed_time(philo->geral), philo->id);
			usleep(500);
		}
	}
	printf("%lu philosopher %d is dead\n", passed_time(philo->geral), philo->id);
	philo->geral->death = 1;
	pthread_detach(philo->thread);
	return (NULL);
}

int take_fork(t_philo *philo)
{
	int i;

	i = 0;
	if (philo->id == 0)
	{
		i = philo->geral->total_fork - 1;
	}	
	if (philo->geral->forks[i] == 0)
	{
		philo->geral->forks[i] = 1;
		i = philo->id;
		if (philo->geral->forks[i] == 0)
		{
			philo->geral->forks[i] = 1;
			return (0);
		}
		philo->geral->forks[i] = 0;
	}
	return (1);
}

void leave_fork(t_philo *philo)
{
	int i;

	i = philo->id - 1;
	if (philo->id == 0)
		i = philo->geral->total_fork - 1;
	philo->geral->forks[i] = 0;
	philo->geral->forks[philo->id] = 0;
}