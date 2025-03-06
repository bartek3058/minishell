/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:47:51 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 13:14:13 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			a;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	a = 0;
	while ((*p1 || *p2) && a < n)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
		a++;
	}
	return (0);
}
/*int main()
{
	//char a[] = "abcd";
	//char b[] = "abc";
	printf ("%d\n", ft_strncmp("t", "", 0));
	printf ("%d\n", ft_strncmp("t", "", 0));
	return (0);
}*/
