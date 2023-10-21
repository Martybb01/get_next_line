/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:53:52 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/21 14:30:26 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strdup(char *s1)
{
    char *s2;
    unsigned int i;

    i = 0;
    s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
    if (!s2)
        return (NULL);
    while (s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return (s2);
}
char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    char *str;

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

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *str;
    size_t i;

    i = 0;
    if (!s)
        return (NULL);
    if (start > ft_strlen(s))
        return (ft_strdup(""));
    if (len > ft_strlen(s + start))
        len = ft_strlen(s + start);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    while (i < len)
    {
        str[i] = s[start + i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char *ft_strchr(char *s, int c)
{
    unsigned int i;
    char carattere;

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
