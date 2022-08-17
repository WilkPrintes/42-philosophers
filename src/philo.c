/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/17 23:31:43 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t current_time(void);
void create_philo(t_philo *philo, t_geral *geral);
void init_geral(t_geral *geral);
void *philo_func(void *parameter);

int main(void)
{
	t_philo philo1;
	t_philo philo2;
	t_geral geral;
	
	init_geral(&geral);
	create_philo(&philo1, &geral);
	create_philo(&philo2, &geral);
	philo1.id = 1;
	philo2.id = 2;
	pthread_create(&philo1.thread, NULL, philo_func, &philo1);	
	pthread_create(&philo2.thread, NULL, philo_func, &philo2);
	while(geral.death == 0)
		;
	pthread_mutex_destroy(&geral.lock);
}

void *philo_func(void *parameter)
{
	t_philo *philo;
	int ok;

	philo = (t_philo *) parameter;
	ok = 0;
	while ((current_time() - philo->last_eat) < philo->geral->t_die)
	{
		pthread_mutex_lock(&philo->geral->lock);
		if (philo->geral->forks >= 2)
		{
			philo->geral->forks -= 2;
			ok = 1;
		}
		pthread_mutex_unlock(&philo->geral->lock);
		if (ok == 1)
		{
			printf("philosopher %d take a fork\n", philo->id);
			printf("philosopher %d is eating\n", philo->id);
			usleep(philo->geral->t_eat);
			pthread_mutex_lock(&philo->geral->lock);
			philo->geral->forks += 2;
			pthread_mutex_unlock(&philo->geral->lock);
			philo->last_eat = current_time();
			printf("philosopher %d is sleeping\n", philo->id);
			usleep(philo->geral->t_sleep);
			printf("philosopher %d is thinking\n", philo->id);
			usleep(500);
		}
	}
	printf("philosopher %d is dead\n", philo->id);
	philo->geral->death = 1;
	pthread_detach(philo->thread);
	return (NULL);
}

time_t current_time(void)
{
	struct timeval times;

	gettimeofday(&times, NULL);
	return (times.tv_usec + times.tv_sec * 1000000);
}

void init_geral(t_geral *geral)
{
	geral->forks = 2;
	geral->death = 0;
	geral->t_eat = 1000 * 1000;
	geral->t_sleep = 1000 * 1000;
	geral->t_die = 1001000;
	geral->t_init = current_time();
	pthread_mutex_init(&geral->lock, NULL);
}

void create_philo(t_philo *philo, t_geral *geral)
{
	philo->eat = 0;
	philo->geral = geral;
	philo->last_eat = geral->t_init = current_time();
}