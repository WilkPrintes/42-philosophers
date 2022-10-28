/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:28:38 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/29 01:18:50 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_info(t_philo *philo, char *type);
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);

void	*alive_func(void *parameter)
{
	t_geral	*geral;
	t_philo	*philo;
	int		i;

	philo = (t_philo *) parameter;
	geral = philo->geral;
	while (geral->death == 0)
	{
		i = geral->total_fork - 1;
		while (i >= 0)
		{
			if (current_time() - philo[i].last_eat > geral->t_die
				&& philo->geral->m_eat != philo->eat)
				show_info(&philo[i], "dead");
			if (geral->all_full == geral->total_fork)
			{
				geral->death = 1;
				break ;
			}
			i--;
		}
		usleep(geral->t_die);
	}
	return (NULL);
}

void	*philo_core(void *parameter)
{
	t_philo	*philo;
	time_t	t_init;

	philo = (t_philo *) parameter;
	t_init = philo->geral->t_init;
	while (philo->geral->death == 0)
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
	return (NULL);
}
