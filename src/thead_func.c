/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:28:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/31 03:55:20 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_info(t_philo *philo, char *type);
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);

void	*alive_func(void *parameter)
{
	t_core	*core;
	t_philo	*philo;
	int		i;

	philo = (t_philo *) parameter;
	core = philo->core;
	while (core->death == 0)
	{
		i = core->total_fork - 1;
		while (i >= 0)
		{
			if (current_time() - philo[i].last_eat > core->t_die
				&& philo->core->m_eat != philo->eat)
				show_info(&philo[i], "dead");
			if (core->all_full == core->total_fork)
			{
				core->death = 1;
				break ;
			}
			i--;
		}
		usleep(core->t_die);
	}
	return (NULL);
}

void	*philo_core(void *parameter)
{
	t_philo	*philo;
	time_t	t_init;

	philo = (t_philo *) parameter;
	t_init = philo->core->t_init;
	while (philo->core->death == 0)
	{
		eat(philo);
		if (philo->fork_right != NULL)
		{
			philo->eat++;
			if (philo->core->m_eat != -1 && philo->core->m_eat == philo->eat)
				return (philo->core->all_full++, NULL);
			sleep_think(philo);
		}
		else
			usleep(philo->core->t_die);
	}
	return (NULL);
}
