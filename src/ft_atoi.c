/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wprintes <wprintes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:38:52 by wprintes          #+#    #+#             */
/*   Updated: 2022/10/27 20:39:30 by wprintes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_var(long *n1, int *n2, int *n3);
static int	is_whitespace(const char c);
void		ft_bzero(void *str, size_t n);

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	else
		ft_bzero(result, nmemb * size);
	return (result);
}

void	ft_bzero(void *str, size_t n)
{
	size_t			counter;
	char			*str_p;

	counter = 0;
	str_p = str;
	while (counter != n)
	{
		str_p[counter] = 0;
		counter++;
	}
}
