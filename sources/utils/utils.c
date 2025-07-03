#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (!s1 || !s2)
		return (-1);
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	while (*p1 || *p2)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	int i;
	
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = 0;
	while (dst[dst_len])
		dst_len++;
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}
void print_tokens(t_token *token)
{
    int i = 0;
    while (token)
    {
        printf("token[%d]: type='%s', value='%s'\n", i,
            token->type ? token->type : "NULL",
            token->value ? token->value : "NULL");
        token = token->next;
        i++;
    }
}