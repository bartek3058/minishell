/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:04:14 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 14:19:50 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstt;
	size_t	srcc;

	dstt = ft_strlen(dst);
	srcc = ft_strlen(src);
	if (dstt >= size)
		dstt = size;
	if (dstt == size)
		return (size + srcc);
	if (srcc < size - dstt)
	{
		ft_memcpy(dst + dstt, src, srcc + 1);
	}
	else
	{
		ft_memcpy(dst + dstt, src, size - dstt - 1);
		dst[size - 1] = '\0';
	}
	return (dstt + srcc);
}
/*int main()
{
	char a[] = "Ola";
	char b[] = " ma kota";
	size_t c = 10;
	printf ("%ld", ft_strlcat(a, b, c));
	return (0);
}*/
