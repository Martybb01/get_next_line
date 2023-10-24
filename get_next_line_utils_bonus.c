/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:58 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/24 23:08:43 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			carattere;

	i = 0;
	carattere = (char)c;
	while (s[i])
	{
		if (s[i] == carattere)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == carattere)
		return ((char *)s + i);
	return (NULL);
}

void	*ft_calloc(size_t items, size_t size)
{
	void			*ptr;
	size_t			i;
	unsigned char	*str;

	ptr = (void *)malloc(items * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)ptr;
	while (i < items * size)
	{
		str[i] = '\0';
		i++;
	}
	return (ptr);
}
