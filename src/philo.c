/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:55:28 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/16 17:05:05 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *rotina_f1(void *parameters)
{
	struct timeval test;
	time_t start;
	time_t final;
	
	parameters = NULL;
	gettimeofday(&test, NULL);
	start = test.tv_usec + test.tv_sec * 1000000;
	printf("philosopher %lu eating\n", pthread_self());
	usleep(1000000);
	printf("philosopher %lu sleeping\n", pthread_self());
	usleep(1000000);
	printf("philosopher %lu thinking\n", pthread_self());
	usleep(1000000);
	gettimeofday(&test, NULL);
	final = test.tv_usec + test.tv_sec * 1000000;
	printf("time passed of philo %lu: %ld\n", pthread_self(), final - start);
	pthread_exit(0);
}

int main(void)
{
	pthread_t philo1;
	pthread_t philo2;
	int exit_code;

	pthread_create(&philo1, NULL, rotina_f1, NULL);
	pthread_create(&philo2, NULL, rotina_f1, NULL);
	exit_code = (int)pthread_join(philo1, NULL);
	exit_code = (int)pthread_join(philo2, NULL);
	printf("finalizado com code: %d\n", exit_code);
}
