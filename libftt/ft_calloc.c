/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:20:01 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 14:56:38 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = c;
		n--;
		p++;
	}
	return (s);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dst;

	if (nmemb > SIZE_MAX / size)
		return (0);
	dst = (void *)malloc(nmemb * size);
	if (!dst)
		return (NULL);
	ft_memset (dst, 0, nmemb * size);
	return (dst);
}

/*int main ()
{
	size_t a;
	size_t b;
	a = 10;
	b = 10;
	char *h;
	char *c;
	h = ft_calloc(a, b);
	c = calloc(a, b);
        printf("%s\n", h);
        printf("%s", c);
        return (0);
}*/
