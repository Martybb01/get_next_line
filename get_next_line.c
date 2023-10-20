/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marboccu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:41:52 by marboccu          #+#    #+#             */
/*   Updated: 2023/10/20 20:13:18 by marboccu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* usa: read, free, ft_strdup, ft_strjoin, ft_strchr.
    Ritorna una linea letta da un file descriptor.
    * Se la funzione è troppo lunga, creare una custom free_strjoin richiamando dentro strjoin e free */
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
            // free(linea_letta);
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

/* usa ft_substr, ft_strlen, free  */
static char *genera_linea(char *line_buffer)
{
    ssize_t i;
    char *linea_letta;

    i = 0;
    /* trova la fine della linea */
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    /* se il char corrente o il prox è \0 non c'è next line (linea è vuota) */
    // if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
    //     return (NULL);
    /* crea sottostringa da fine di stringa_letta a fine di line_buffer */
    linea_letta = ft_substr(linea_letta, 0, i + 1);
    if (!linea_letta)
    {
        free(linea_letta);
        linea_letta = NULL;
    }
    return (linea_letta);
}

// static char *genera_linea_finale(char *line_buffer)
// {
//     ssize_t i;
//     char *linea_letta;

//     i = 0;
//     while (linea_letta[i] != '\n' && linea_letta[i] != '\0')
//         i++;
//     if (linea_letta[i] == '\0' || linea_letta[i + 1] == '\0')
//         return (NULL);
//     linea_letta = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer));
//     if (!linea_letta)
//     {
//         free(linea_letta);
//         linea_letta = NULL;
//     }
//     return (linea_letta);
// }

/* crea un altra funzione simile a genera linea che usa substr per salvarsi la parte finale quindi parte da i + 1 e finisce a strlen(s)*/

char *get_next_line(int fd)
{
    static char *save;
    char *buffer;
    char *linea;

    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer || fd < 0 || BUFFER_SIZE < 1)
    {
        free(buffer);
        free(save);
        buffer = NULL;
        save = NULL;
        return (NULL);
    }
    linea = riempi_buffer(fd, save, buffer);
    free(buffer);
    // buffer = NULL;
    if (!linea)
        return (NULL);
    save = genera_linea(linea);
    if (!save)
        return (NULL);
    // save = genera_linea_finale(linea);
    return (linea);
}

int main()
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    // while ((line = get_next_line(fd)))
    // {
    //     printf("%s\n", line);
    //     free(line);
    // }
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
}
