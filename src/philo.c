/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/23 19:16:11 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int valid_arguments(int argc, char **argv);

int main(int argc, char **argv)
{
	t_philo *philos;
	t_geral geral;
	
	if (valid_arguments(argc, argv) == 0)
	{
		init_geral(&geral, argv);
		philos = (t_philo *) malloc (sizeof (t_philo) * ft_atoi(argv[1]));
		all_philos(ft_atoi(argv[1]), philos, &geral);
		pthread_create(&geral.alive, NULL, alive_func, &geral);
		pthread_join(geral.alive, NULL);	
		pthread_mutex_destroy(&geral.lock);
	}
	return (1);
}

int	ft_isdigit(char *c)
{
	int i;

	i = 0;
	while(c[i])
	{
		if (c[i] < 48 || c[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int valid_arguments(int argc, char **argv)
{
	int i;
	
	i = 1;
	if (argc < 5)
	{
		printf("please insert ");
		if (argc == 1)
			printf("number_of_philosophers, time_to_die, time_to_eat, time_to_sleep");
		if (argc == 2)
			printf("time_to_die, time_to_eat, time_to_sleep");
		if (argc == 3)
			printf("time_to_eat, time_to_sleep");
		if (argc == 4)
			printf("time_to_sleep");
		printf(".\n");
		return (1);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 1)
			return(printf("Invalid type of arguments\n"));
		i++;
	}
	return (0);
}