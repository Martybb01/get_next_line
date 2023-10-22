#include "get_next_line.h"

static char *leggi_dal_file(int fd)
{
    int bytes_letti;
    char *cup_buffer;
    static int count = 1;

    printf("ft_calloc#[%d] ", count++);
    cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!cup_buffer)
        return (NULL);
    bytes_letti = read(fd, cup_buffer, BUFFER_SIZE);
    if (bytes_letti <= 0)
    {
        free(cup_buffer);
        return (NULL);
    }
    return (cup_buffer);
}

char *get_next_line(int fd)
{
    char *basin_buffer;

    basin_buffer = leggi_dal_file(fd);
    return (basin_buffer);
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
