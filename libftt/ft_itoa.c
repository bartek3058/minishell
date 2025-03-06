/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:15:22 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 14:14:59 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ic(char *s)
{
	s[0] = '0';
	return (s);
}

static size_t	ft_numbers(int n)
{
	size_t	a;

	a = 0;
	if (n <= 0)
		a++;
	while (n)
	{
		n /= 10;
		a++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;
	size_t	c;
	long	nb;

	nb = n;
	c = ft_numbers(n);
	ret = (char *)malloc(sizeof (char) * (c + 1));
	if (ret == 0)
		return (NULL);
	if (nb < 0)
	{
		ret[0] = '-';
		nb = -nb;
	}
	ret[c--] = '\0';
	if (nb == 0)
		return (ic(ret));
	i = c;
	while (nb > 0)
	{
		ret[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}
/*int main()
{
	int c = 1;
	printf("%s", ft_itoa(c));
	return (0);
}*/
