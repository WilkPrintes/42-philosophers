/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:26:30 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/31 03:55:21 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	current_time(void)
{
	struct timeval	times;

	gettimeofday(&times, NULL);
	return (times.tv_usec + times.tv_sec * 1000000);
}

time_t	passed_time(t_core *core)
{
	time_t	result;

	result = current_time() - core->t_init;
	result = result / 1000;
	return (result);
}
