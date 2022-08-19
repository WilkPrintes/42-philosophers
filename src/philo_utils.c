/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:56:26 by wprintes          #+#    #+#             */
/*   Updated: 2022/08/18 16:16:44 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_var(long *n1, int *n2, int *n3);
static int	is_whitespace(const char c);

long	ft_atoi(const char *str)
{
	long	result;
	int		increment;
	int		negative;

	init_var(&result, &increment, &negative);
	if (*str == '\0')
		return (0);
	while (is_whitespace(*str))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			negative++;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result * increment + *str - '0';
		str++;
	}
	if (negative == 1)
		result = result * -1;
	return (result);
}

static void	init_var(long *n1, int *n2, int *n3)
{
	*n1 = 0;
	*n2 = 10;
	*n3 = 0;
}

static int	is_whitespace(const char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}