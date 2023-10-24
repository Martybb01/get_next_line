/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:41:52 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/24 12:40:12 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// static char *ft_joinfree(char *linea_letta, char *buffer)
// {
//     char *temp;
//     temp = ft_strjoin(linea_letta, buffer);
//     free(buffer);
//     return (temp);
// }

/* usa: read, free, ft_strjoin, ft_strchr, ft_calloc.
    Ritorna una linea letta da un file descriptor. */
static char *leggi_linea(int fd, char *linea_letta, char *buffer)
{
    ssize_t bytes_letti;

    if (!linea_letta)
        linea_letta = ft_calloc(1, sizeof(char));
    bytes_letti = 1;
    while (bytes_letti > 0)
    {
        bytes_letti = read(fd, buffer, BUFFER_SIZE);

        if (bytes_letti == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_letti] = '\0';

        linea_letta = ft_strjoin(linea_letta, buffer);
        if (!linea_letta)
        {
            free(linea_letta);
            return (NULL);
        }

        if (ft_strchr(buffer, '\n'))
            break;
    }
    free(buffer);
    return (linea_letta);
}

/* usa free, ft_calloc  */
static char *genera_linea(char *line_buffer, char *linea_letta)
{
    ssize_t i;
    ssize_t len;

    i = 0;
    len = 0;
    /* trova la fine della linea */
    while (line_buffer[i] != '\n' && line_buffer[i])
        i++;
    if (line_buffer[i] == '\n')
        i++;
    linea_letta = ft_calloc(sizeof(char), i + 1);
    if (!linea_letta)
        return (NULL);
    while (len < i)
    {
        linea_letta[len] = line_buffer[len];
        len++;
    }
    linea_letta[len] = '\0';
    return (linea_letta);
}

/* usa ft_calloc, ft_strlen, free */
static char *estrai_nuova_linea(char *line_buffer)
{
    ssize_t i;
    ssize_t len;
    char *nuova_linea;

    i = 0;
    len = 0;
    if (!line_buffer)
        return (NULL);
    while (line_buffer[i] != '\n' && line_buffer[i])
        i++;
    if (line_buffer[i] == '\n')
        i++;
    nuova_linea = ft_calloc(sizeof(char), ft_strlen(line_buffer) - i + 1);
    if (!nuova_linea)
        return (NULL);
    while (line_buffer[i + len])
    {
        nuova_linea[len] = line_buffer[i + len];
        len++;
    }
    free(line_buffer);
    nuova_linea[len] = '\0';
    return (nuova_linea);
}

char *get_next_line(int fd)
{
    static char *save_buff;
    char *buffer;
    char *linea_letta;

    linea_letta = NULL;
    buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (read(fd, 0, 0) < 0 || fd < 0 || BUFFER_SIZE < 1)
    {
        free(save_buff);
        free(buffer);
        save_buff = NULL;
        buffer = NULL;
        return (NULL);
    }
    if (!buffer)
        return (NULL);
    save_buff = leggi_linea(fd, save_buff, buffer);
    if (*save_buff == 0)
    {
        free(save_buff);
        save_buff = 0;
        return (save_buff);
    }
    linea_letta = genera_linea(save_buff, linea_letta);
    save_buff = estrai_nuova_linea(save_buff);
    return (linea_letta);
}

int main(void)
{
    int fd;
    char *next_line;
    int count;

    count = 0;
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    while (1)
    {
        next_line = get_next_line(fd);
        if (!next_line)
            break;
        count++;
        printf("GNL %d: %s", count, next_line);
        free(next_line);
        next_line = NULL;
    }

    close(fd);
    return (0);
}
