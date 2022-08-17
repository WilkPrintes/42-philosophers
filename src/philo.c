/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/17 20:40:30 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_geral(t_geral *geral);
t_philo *create_philo(t_geral *geral, int count);
time_t current_time(void);
void *philo_comp(void *parameter);

int main(void)
{
	t_geral geral;
	int count;
	t_philo **philos;

	count = 0;
	philos = malloc (sizeof(t_philo *) * 3);
	init_geral(&geral);
	while (count < 3)
	{
		philos[count] = create_philo(&geral, count);
		count++;
	}
	philos[count] = NULL;
	count = 0;
	while (philos[count])
	{
		pthread_create(&philos[count]->thread, NULL, philo_comp, philos[count]);
		count++;
	}
	while (1)
	{
		if (geral.death >= 1)
			break;
	}
}

void init_geral(t_geral *geral)
{
	geral->forks = 2;
	geral->death = 0;
	geral->t_eat = 500 * 1000;
	geral->t_sleep = 1000 * 1000;
	geral->t_die = 2000 * 1000;
	geral->t_init = current_time();
	pthread_mutex_init(&geral->lock, NULL);
}

void *philo_comp(void *parameter)
{
	t_philo *philo;

	philo = (t_philo *)parameter;
	while (1)
	{
		if (philo->geral->forks >= 2)
		{
			if ((current_time() - philo->last_eat) > philo->geral->t_die)
			{
				printf("philo %d died\n", philo->id);
				pthread_mutex_lock (&philo->geral->lock);
				philo->geral->death += 1;
				pthread_mutex_unlock (&philo->geral->lock);
				pthread_detach(philo->thread);
				return (NULL);
			}
			printf("philo %d has taken a fork\n", philo->id);
			pthread_mutex_lock (&philo->geral->lock);
			philo->geral->forks -= 2;
			printf("forks ok: %d\n", philo->geral->forks);
			printf("philo %d is eating\n", philo->id);
			usleep(philo->geral->t_eat);
			philo->geral->forks += 2;
			pthread_mutex_unlock (&philo->geral->lock);
			philo->last_eat = current_time();
			printf("philo %d is sleeping\n", philo->id);
			usleep(philo->geral->t_sleep);
			printf("philo %d is thinking\n", philo->id);
		}else if ((current_time() - philo->last_eat) > philo->geral->t_die)
		{
			printf("philo %d died\n", philo->id);
			pthread_mutex_lock (&philo->geral->lock);
			philo->geral->death += 1;
			pthread_mutex_unlock (&philo->geral->lock);
			pthread_detach(philo->thread);
		}

	}
	return (NULL);
}

time_t current_time(void)
{
	struct timeval times;

	gettimeofday(&times, NULL);
	return (times.tv_usec + times.tv_sec * 1000000);
}

t_philo *create_philo(t_geral *geral, int count)
{
	t_philo	*philo;

	philo = malloc (sizeof (t_philo));
	philo->eat = 0;
	philo->id = count;
	philo->geral = geral;
	philo->last_eat = geral->t_init;
	return (philo);
}