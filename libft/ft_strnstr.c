/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:50:41 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 14:18:18 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*b;
	const char	*l;
	size_t		i;
	size_t		j;

	i = 0;
	b = big;
	l = little;
	if (little[0] == 0)
		return ((char *) big);
	while (i < len && b[i] != '\0')
	{
		j = 0;
		if (b[i] == l[j])
		{
			while (l[j] != '\0' && b[i + j] == l[j] && i + j < len)
				j++;
			if (l[j] == '\0')
				return ((char *)(b + i));
		}
		i++;
	}
	return (NULL);
}

/*int main()
{
	const char a[] = "123456782356789";
	const char b[] = "235";
	printf("%s", ft_strnstr(a, b, 11));
	//printf("%d", strnstr(a, b, 2));
	return (0);
}*/
