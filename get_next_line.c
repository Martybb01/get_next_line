/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:41:52 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/24 20:04:01 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* usa: read, free, ft_strjoin, ft_strchr, ft_calloc.
    Ritorna una linea letta da un file descriptor. */
static char *read_fd_line(int fd, char *line_read, char *buffer)
{
    ssize_t bytes_read;
    char *temp;

    bytes_read = 1;
    while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        if (!line_read)
        {
            line_read = ft_calloc(1, sizeof(char));
            if (!line_read)
                return (NULL);
        }
        temp = line_read;
        line_read = ft_strjoin(temp, buffer);
        free(temp);
    }
    free(buffer);
    return (line_read);
}

/* usa free, ft_calloc  */
static char *line_creator(char *line_buffer, char *line_read)
{
    ssize_t i;
    ssize_t len;

    i = 0;
    len = 0;
    while (line_buffer[i] != '\n' && line_buffer[i])
        i++;
    if (line_buffer[i] == '\n')
        i++;
    line_read = ft_calloc(sizeof(char), i + 1);
    if (!line_read)
        return (NULL);
    while (len < i)
    {
        line_read[len] = line_buffer[len];
        len++;
    }
    line_read[len] = '\0';
    return (line_read);
}

/* usa ft_calloc, ft_strlen, free */
static char *extract_new_line(char *line_buffer)
{
    ssize_t i;
    ssize_t len;
    char *new_line;

    i = 0;
    len = 0;
    if (!line_buffer)
        return (NULL);
    while (line_buffer[i] != '\n' && line_buffer[i])
        i++;
    if (line_buffer[i] == '\n')
        i++;
    new_line = ft_calloc(sizeof(char), ft_strlen(line_buffer) - i + 1);
    if (!new_line)
        return (NULL);
    while (line_buffer[i + len])
    {
        new_line[len] = line_buffer[i + len];
        len++;
    }
    free(line_buffer);
    new_line[len] = '\0';
    return (new_line);
}

char *get_next_line(int fd)
{
    static char *save_buff;
    char *buffer;
    char *line_read;

    line_read = NULL;
    buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (read(fd, 0, 0) < 0 || fd < 0 || BUFFER_SIZE < 1 || !buffer)
    {
        free(save_buff);
        free(buffer);
        save_buff = NULL;
        buffer = NULL;
        return (NULL);
    }
    save_buff = read_fd_line(fd, save_buff, buffer);
    if (*save_buff == 0)
    {
        free(save_buff);
        save_buff = 0;
        return (save_buff);
    }
    line_read = line_creator(save_buff, line_read);
    save_buff = extract_new_line(save_buff);
    return (line_read);
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
