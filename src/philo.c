/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/29 16:44:15 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		valid_arguments(int argc, char **argv);
void	join_philos(t_philo *philo);
void	clean_mutexs(t_core *core);
void	free_philos(t_philo *philo);

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_core	core;

	if (valid_arguments(argc, argv) == 0)
	{
		init_core(&core, argv);
		philos = (t_philo *) malloc (sizeof (t_philo) * ft_atoi(argv[1]));
		all_philos(ft_atoi(argv[1]), philos, &core);
		pthread_create(&core.alive, NULL, alive_func, philos);
		pthread_join(core.alive, NULL);
		join_philos(philos);
		clean_mutexs(&core);
		free(philos);
		free(core.forks);
	}
	return (1);
}

void	join_philos(t_philo *philo)
{
	int	i;

	i = philo->core->total_fork;
	i--;
	while (i >= 0)
	{
		pthread_join(philo[i].thread, NULL);
		i--;
	}
}

void	clean_mutexs(t_core *core)
{
	int	i;

	i = core->total_fork;
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&core->forks[i]);
		i--;
	}
	pthread_mutex_destroy(&core->lock);
}

void	free_philos(t_philo *philo)
{
	int	i;

	i = philo->core->total_fork;
	i--;
	while (i >= 0)
	{
		free(&philo[i]);
		i--;
	}
}

int	valid_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
	{
		printf("please insert: \033[0;31m");
		if (argc <= 1)
			printf("number_of_philosophers, ");
		if (argc <= 2)
			printf("time_to_die, ");
		if (argc <= 3)
			printf("time_to_eat, ");
		if (argc <= 4)
			printf("time_to_sleep");
		printf(".\033[0m\n");
		return (1);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[1]) == 0 || ft_isdigit(argv[i]) == 1)
			return (printf("Invalid type of arguments\n"));
		i++;
	}
	return (0);
}
