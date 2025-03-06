/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:06:21 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/15 14:23:53 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	a;
	char	*dest;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = start;
	a = 0;
	while (len > 0 && s[i] != '\0')
	{
		dest[a] = s[i];
		i++;
		a++;
		len--;
	}
	dest[a] = '\0';
	return (dest);
}
/*int main()
{
	char *d;
	unsigned int i = 0;
	size_t len = 10;

	d = ft_substr("jestem koxem", i, len);
	printf("%s", d);
	return (0);
}*/
