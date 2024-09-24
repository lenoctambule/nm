#include "nm.h"

int main(int ac, char **av)
{
    int     fd;
    t_stat  s;

    ac--; av++;
    if (ac != 1 || av[0][0] == 0)
        return ft_putstr_fd("Usage : nm <file_path>\n", 2), 1;
    fd  = open(av[0], O_RDONLY);
    if (fd == -1)
        return perror("Error"), 1;
    if (stat(fd, &s) == -1 
        || !S_ISREG(s.st_mode))
        return perror("Error"), 1;
    
}