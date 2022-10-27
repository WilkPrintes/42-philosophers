/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:28:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/27 21:45:09 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_info(t_philo *philo, char *type);
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);

void	*alive_func(void *parameter)
{
	t_geral	*geral;

	geral = (t_geral *) parameter;
	while (1)
	{
		if (geral->death != 0)
			break ;
		if (geral->all_full == geral->total_fork)
			geral->death++;
		usleep(1000);
	}
	pthread_detach(geral->alive);
	return (NULL);
}

void	*philo_core(void *parameter)
{
	t_philo	*philo;
	time_t	t_init;

	philo = (t_philo *) parameter;
	t_init = philo->geral->t_init;
	while ((current_time() - philo->last_eat) < philo->geral->t_die
		&& philo->geral->death == 0)
	{
		eat(philo);
		if (philo->fork_right != NULL)
		{
			philo->eat++;
			if (philo->geral->m_eat != -1 && philo->geral->m_eat == philo->eat)
				return (philo->geral->all_full++, NULL);
			sleep_think(philo);
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
