/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:09:52 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 12:51:50 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s_s1;
	const unsigned char	*s_s2;
	size_t				i;

	if (n == 0)
		return (0);
	s_s1 = (const unsigned char *) s1;
	s_s2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (*s_s1 != *s_s2)
			return (*s_s1 - *s_s2);
		s_s1++;
		s_s2++;
		i++;
	}
	return (0);
}

/*int main()
{
	char a[] = "abc123123";
	char b[] = "abc";
	int c;
	int d;

	d = ft_memcmp(a, b, 10);
	c = memcmp(a, b, 10);
	printf("%d\n", c);
	printf("%d\n", d);
	return (0);
}*/
