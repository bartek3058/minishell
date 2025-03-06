/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:58:33 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 10:26:56 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*dst;
	size_t		i;
	char		cc;

	cc = (char) c;
	dst = (const char *) s;
	i = 0;
	while (i < n)
	{
		if (dst[i] == cc)
			return ((void *)&dst[i]);
		i++;
	}
	return (NULL);
}
/*int main()
{
	char a[] = {0, 1, 2 ,3 ,4 ,5};
	//char b[] = "$";
	void *c;
	void *d;
	
	d = ft_memchr(a, 0, 1);
	c = memchr(a, 0, 1);
	char *c_c = (char *) c;
	char *d_d = (char *) d;
	printf("%s\n", c_c);
	printf("%s\n", d_d);
	return (0);
}*/
