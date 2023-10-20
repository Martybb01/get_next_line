/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:41:52 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/20 14:56:28 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* usa: read, free, ft_strdup, ft_strjoin, ft_strchr.
    Ritorna una linea letta da un file descriptor */
static char *riempi_buffer(int fd, char *linea_letta, char *buffer)
{
    ssize_t bytes_letti;
    char *temp;

    bytes_letti = 1;
    while (bytes_letti > 0)
    {
        /* legge fino a BUFFER_SIZE byte da fd e li immagazzina in buffer. Salva i bytes letti della variabile.  */
        bytes_letti = read(fd, buffer, BUFFER_SIZE);

        /* errore nel leggere il file descriptor*/
        if (bytes_letti == -1)
        {
            free(linea_letta);
            return (NULL);
        }
        /* abbiamo letto l'intero file, quindi usciamo dal loop */
        if (bytes_letti == 0)
            break;
        buffer[bytes_letti] = '\0';

        /* condizione vera se è il primo ciclo */
        if (!linea_letta)
            linea_letta = ft_strdup(""); // alloca stringa vuota
        temp = linea_letta;              // salva puntatore corrente in temp per poterlo liberare dopo

        linea_letta = ft_strjoin(linea_letta, buffer);
        free(temp);
        temp = NULL;

        /* è stata letta una linea completa.*/
        if (ft_strchr(buffer, '\n'))
            break;
    }
    return (linea_letta);
}

/* prende il line_buffer come parametro, e lo legge finchè non trova il carattere \n o \0, ossia la fine della linea o la fine del file.
Setta il line_buffer a \0 alla fine della linea e ritorna una sottostringa del buffer dalla fine della linea alla fine del buffer.
Questa sottostringa è ritornata come left_c */
// char *set_line(char *line_buffer)
// {
//     int i;
//     char *left_c;

//     i = 0;
//     while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
//         i++;

// }

// char *get_next_line(int fd)
// {
//     static char *save;
//     char *buffer;
// }

int main()
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
}
