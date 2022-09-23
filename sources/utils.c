/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:54 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/23 16:13:55 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				r;
	unsigned int	sol;

	i = 0;
	r = 1;
	sol = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			r = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		sol = (sol * 10) + (str[i] - 48);
		if (sol > 2147483657 && r == 1)
			return (-1);
		if (sol > 2147483648 && r == -1)
			return (0);
		i++;
	}
	return (sol * r);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	if (s == NULL)
		return (0);
	while (s[c] != 0)
		c++;
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	s1 = malloc(sizeof(char) * (len + 1));
	if (s1 == NULL)
		return (s1);
	if (start > ft_strlen(s))
	{
		s1[0] = '\0';
		return (s1);
	}
	i = 0;
	while (i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
