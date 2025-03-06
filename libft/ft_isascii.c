/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:31:29 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/14 08:49:50 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int s)
{
	if (!(s >= 0 && s <= 127))
		return (0);
	return (1);
}

/*int main ()
{
	char a = 'a';
	int b;

	b = ft_isascii(a);
	printf("%d", b);
	return (0);
}*/
