/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:22:23 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 12:43:53 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	my_funcion(unsigned int i, char s)
{
	char d;

	d = 0;
	d = s;
		d += i;
	return (d);
}

int	ft_strlen(char *s)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		a++;
		b++;
	}
	return (b);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*int main()
{
	const char	*s;

	s = "";
	printf("%s", ft_strmapi(s, my_funcion));
	return (0);
}*/	
