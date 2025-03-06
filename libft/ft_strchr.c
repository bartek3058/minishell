/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:05:35 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 12:52:24 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;
	char	cc;

	cc = (char)c;
	a = (char *)s;
	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == cc)
			return (&a[i]);
		i++;
	}
	if (a[i] == cc)
		return (&a[i]);
	return (NULL);
}
/*int main()
{
	const char a[] = "tripouille";
	//char b[] = "c";
	printf("%s\n", ft_strchr(a, 't' + 256));
	printf("%s\n", strchr(a, 't' + 256));
       return (0);
}*/
