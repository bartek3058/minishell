/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:24:03 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/13 19:56:19 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int a)
{
	if (!(a >= 48 && a <= 57))
		return (0);
	return (1);
}

/*int main ()
{
	char a[] = "1ia2";
	int b;
	b = ft_isdigit(a);
	printf ("%d", b);
	return (0);
}*/
