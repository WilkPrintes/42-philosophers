/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:56:10 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/18 16:46:42 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_geral
{
	pthread_t		alive;
	int		forks;
	int		death;
	int		m_eat;
	int		exit;
	time_t	t_sleep;
	time_t	t_die;
	time_t	t_eat;
	time_t	t_init;
	pthread_mutex_t	lock;
} t_geral;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat;
	t_geral			*geral;
	time_t			last_eat;
} t_philo;

long	ft_atoi(const char *str);