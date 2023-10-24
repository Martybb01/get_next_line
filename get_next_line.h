/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:53:43 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/24 12:41:05 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

size_t ft_strlen(char *s);
char *ft_strdup(char *s1);
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(char *s, int c);
void *ft_calloc(size_t nitems, size_t size);

#endif
