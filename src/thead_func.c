/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:28:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/27 12:19:36 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void show_info(t_philo *philo, char *type);

void *alive_func(void *parameter)
{
	t_geral *geral;

	geral = (t_geral *) parameter;
	while (1)
	{
		if (geral->death != 0)
			break ;
		usleep(1000);
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
	while ((current_time() - philo->last_eat) < philo->geral->t_die && philo->geral->death == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		if (philo->fork_right != NULL)
		{
			pthread_mutex_lock(philo->fork_right);
			show_info(philo, "take");
			show_info(philo, "eat");
			philo->last_eat = current_time();
			usleep(philo->geral->t_eat);
		}
		pthread_mutex_unlock(philo->fork_left);
		if (philo->fork_right != NULL)
		{
			pthread_mutex_unlock(philo->fork_right);
			philo->eat++;
			if (philo->geral->m_eat != -1 && philo->geral->m_eat == philo->eat)
				return (philo->geral->death = 1, NULL);
			show_info(philo, "sleep");
			usleep(philo->geral->t_sleep);
			show_info(philo, "think");
			usleep(1500);
		}
		else
			usleep(philo->geral->t_die);
	}
	if (philo->geral->death != 1)
	{
		philo->geral->death++;
		show_info(philo, "dead");
	}
	return (NULL);
}

void show_info(t_philo *philo, char *type)
{
	if (ft_strncmp(type, "take", 4) == 0 && philo->geral->death != 1)
	{
		pthread_mutex_lock(&philo->geral->lock);
		printf("%lu philosopher %d take a fork\n", passed_time(philo->geral), philo->id);
		pthread_mutex_unlock(&philo->geral->lock);
	}
	if (ft_strncmp(type, "eat", 3) == 0 && philo->geral->death != 1)
	{
		pthread_mutex_lock(&philo->geral->lock);
		printf("%lu philosopher %d is eating\n", passed_time(philo->geral), philo->id);
		pthread_mutex_unlock(&philo->geral->lock);
	}
	if (ft_strncmp(type, "sleep", 5) == 0 && philo->geral->death != 1)
	{
		pthread_mutex_lock(&philo->geral->lock);
		printf("%lu philosopher %d is sleeping\n", passed_time(philo->geral), philo->id);
		pthread_mutex_unlock(&philo->geral->lock);
	}
	if (ft_strncmp(type, "think", 5) == 0 && philo->geral->death != 1)
	{
		pthread_mutex_lock(&philo->geral->lock);
		printf("%lu philosopher %d is thinking\n", passed_time(philo->geral), philo->id);
		pthread_mutex_unlock(&philo->geral->lock);
	}
	if (ft_strncmp(type, "dead", 4) == 0)
	{
		pthread_mutex_lock(&philo->geral->lock);
		printf("%lu philosopher %d is dead\n", passed_time(philo->geral), philo->id);
		pthread_mutex_unlock(&philo->geral->lock);
	}
}