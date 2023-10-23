#include "get_next_line.h"

static char *append_buffer(char *basin_buffer, char *read_buffer)
{
    char *temp;

    temp = ft_strjoin(basin_buffer, read_buffer);
    free(basin_buffer);
    return (temp);
}

static char *leggi_dal_file(int fd)
{
    int bytes_letti;
    char *cup_buffer;
    char *basin_buffer;

    cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    basin_buffer = ft_calloc(1, sizeof(char));
    basin_buffer[0] = '\0';

    if (!cup_buffer || !basin_buffer)
        return (NULL);
    bytes_letti = 1;
    while (bytes_letti > 0)
    {
        bytes_letti = read(fd, cup_buffer, BUFFER_SIZE);
        if (bytes_letti == -1)
        {
            return (NULL);
        }
        if (cup_buffer != NULL)
            basin_buffer = append_buffer(basin_buffer, cup_buffer);
        if (ft_strchr(basin_buffer, '\n'))
            break;
    }
    free(cup_buffer);
    return (basin_buffer);
}

static char *genera_linea(char *line_buffer, char **extra)
{
    ssize_t i;

    i = 0;
    while (line_buffer[i])
    {
        if (line_buffer[i] == '\n')
        {
            *extra = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
            break;
        }
        i++;
    }
    line_buffer[i + 1] = '\0';
    return (line_buffer);
}
// static char *genera_linea(char *line_buffer, char **extra)
// {
//     ssize_t i;

//     i = 0;
//     while (line_buffer[i] && line_buffer[i] != '\n')
//         i++;
//     if (line_buffer[i] == '\n')
//     {
//         *extra =
//     }
// }

char *get_next_line(int fd)
{
    static char *save_buff;
    char *linea_letta;
    char *extra;

    if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
        return (NULL);

    if (!save_buff)
        save_buff = leggi_dal_file(fd);

    if (!save_buff)
        return (NULL);

    linea_letta = genera_linea(save_buff, &extra);
    save_buff = extra;

    if (linea_letta == NULL)
    {
        free(save_buff);
        save_buff = NULL;
    }

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
        printf("GNL %d: %s\n", count, next_line);
        free(next_line);
        next_line = NULL;
    }

    close(fd);
    return (0);
}
