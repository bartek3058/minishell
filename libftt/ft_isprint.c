/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:40:19 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/13 20:01:57 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int s)
{
	if (!(s >= 32 && s <= 126))
		return (0);
	return (1);
}

/*int main ()
{
	char a[] = "ab\nc";
	int	b;

	b = ft_isprint(a);
	printf("%d", b);
	return (0);
}*/
