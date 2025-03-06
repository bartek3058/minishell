/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:30:08 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 18:13:50 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	char	*s3;
	char	*s4;
	int		i;
	int		a;

	i = 0;
	a = 0;
	s3 = (char *)s1;
	s4 = (char *)s2;
	d = (char *)malloc(ft_strlen(s3) + ft_strlen(s4) + 1);
	if (d == NULL)
		return (0);
	while (s3[i] != '\0')
		d[i++] = s3[a++];
	a = 0;
	while (s4[a] != '\0')
		d[i++] = s4[a++];
	d[i] = '\0';
	return (d);
}

/*int main()
{
	char	*a;
	char	*b;

	a = "abc";
	b = "def";
	printf("%s", ft_strjoin(a, b));
	return (0);
}*/
