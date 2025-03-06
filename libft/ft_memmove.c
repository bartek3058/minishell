/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:21:44 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 12:42:59 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	s = (const unsigned char *) src;
	d = (unsigned char *) dest;
	if (d > s)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

/*int main ()
{
	char a[] = { 0, 0, 0, 0, 0, 0, 0};
	char b[] = {65, 66, 67, 68, 69, 0, 45};
	char *c;
	char *d;
	c = ft_memmove(a, b, 7);
	d = memmove(a, b, 7);
	printf("%s\n", c);
	printf("%s\n", d);
	return (0);
}*/
