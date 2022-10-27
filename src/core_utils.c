/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:44:49 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/27 22:17:35 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (philo->fork_right != NULL)
	{
		pthread_mutex_lock(philo->fork_right);
		show_info(philo, "take");
		show_info(philo, "take");
		show_info(philo, "eat");
		philo->last_eat = current_time();
		usleep(philo->geral->t_eat);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
		show_info(philo, "take");
	pthread_mutex_unlock(philo->fork_left);
}

void	sleep_think(t_philo *philo)
{
	show_info(philo, "sleep");
	usleep(philo->geral->t_sleep);
	show_info(philo, "think");
	usleep(1500);
}

void	show_info(t_philo *philo, char *type)
{
	pthread_mutex_lock(&philo->geral->lock);
	if (philo->geral->death != 1)
		printf("%lu philosopher", passed_time(philo->geral));
	if (ft_strncmp(type, "take", 4) == 0 && philo->geral->death != 1)
		printf(" %d has taken a fork\n", philo->id);
	if (ft_strncmp(type, "eat", 3) == 0 && philo->geral->death != 1)
		printf(" %d is eating\n", philo->id);
	if (ft_strncmp(type, "sleep", 5) == 0 && philo->geral->death != 1)
		printf(" %d is sleeping\n", philo->id);
	if (ft_strncmp(type, "think", 5) == 0 && philo->geral->death != 1)
		printf(" %d is thinking\n", philo->id);
	if (ft_strncmp(type, "dead", 4) == 0)
	{
		printf("%lu philosopher", passed_time(philo->geral));
		printf(" %d is died\n", philo->id);
	}
	pthread_mutex_unlock(&philo->geral->lock);
}
