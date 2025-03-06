/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:22:12 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 08:45:24 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n > 0)
	{
		*p = '\0';
		n--;
		p++;
	}
}
/*int main ()
{
	char a[] = "abc";
	printf ("%s", ft_bzero(a, 2));
	return (0);
}*/
