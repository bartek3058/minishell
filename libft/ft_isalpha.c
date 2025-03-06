/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogalsk <brogalsk@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:00:19 by brogalsk          #+#    #+#             */
/*   Updated: 2024/03/07 15:27:35 by brogalsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	if (!((a >= 65 && a <= 90) || (a >= 97 && a <= 122)))
		return (0);
	return (1);
}
/*int main ()
{
	char a[] = "ab0c";
	int b;
	b = ft_isalpha(a);
	printf("%d", b);
	return (0);
}*/
