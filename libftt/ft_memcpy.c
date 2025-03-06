/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:53:42 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 13:09:44 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	while (n > 0)
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
		n--;
	}
	return (dest);
}

/*int main ()
{
	char dest[] = "354";
	char src[] = "ad34";
	char *d;
	char *c;
	d = ft_memcpy(dest, src, 2);
	c = memcpy(dest, src, 2);
	printf("%s\n", d);
	printf("%s\n", c);
	return (0);
}*/
