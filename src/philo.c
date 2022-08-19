/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/19 15:29:17 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t current_time(void);
void create_philo(t_philo *philo, t_geral *geral);
void init_geral(t_geral *geral, char **argv);
void *philo_func(void *parameter);
void *alive_func(void *parameter);
void all_philos(int c_philos, t_philo *philos, t_geral *geral);

int main(int argc, char **argv)
{
	t_philo *philos;
	t_geral geral;
	
	if (argc >= 5 )
	{
		init_geral(&geral, argv);
		philos = (t_philo *) malloc (sizeof (t_philo) * ft_atoi(argv[1]));
		all_philos(ft_atoi(argv[1]), philos, &geral);
		pthread_create(&geral.alive, NULL, alive_func, &geral);
		pthread_join(geral.alive, NULL);	
		pthread_mutex_destroy(&geral.lock);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
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
			printf("philosopher %d take a fork in %lu\n", philo->id, current_time());
			printf("philosopher %d is eating in %lu\n", philo->id, current_time());
			usleep(philo->geral->t_eat);
			pthread_mutex_lock(&philo->geral->lock);
			philo->geral->forks += 2;
			pthread_mutex_unlock(&philo->geral->lock);
			philo->last_eat = current_time();
			printf("philosopher %d is sleeping in %lu\n", philo->id, current_time());
			usleep(philo->geral->t_sleep);
			printf("philosopher %d is thinking in %lu\n", philo->id, current_time());
			usleep(500);
		}
	}
	printf("philosopher %d is dead in %lu\n", philo->id, current_time());
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

void init_geral(t_geral *geral, char **argv)
{
	geral->forks = ft_atoi(argv[1]);
	geral->death = 0;
	geral->t_die = ft_atoi(argv[2]) * 1000;
	geral->t_eat = ft_atoi(argv[3]) * 1000;
	geral->t_sleep = ft_atoi(argv[4]) * 1000;
	geral->t_init = current_time();
	pthread_mutex_init(&geral->lock, NULL);
}

void create_philo(t_philo *philo, t_geral *geral)
{
	philo->eat = 0;
	philo->geral = geral;
	philo->last_eat = geral->t_init = current_time();
}