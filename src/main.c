#include "nm.h"

int main(int ac, char **av)
{
    int     fd;
    t_stat  s;
    void    *filemap;
    int     elfclass = ELFCLASSNONE;

    ac--; av++;
    if (ac != 1 || av[0][0] == 0)
        return ft_putstr_fd("Usage : nm <file_path>\n", 2), EXIT_FAILURE;
    fd  = open(av[0], O_RDONLY);
    if (fd == -1)
        return perror("Error"), EXIT_FAILURE;
    if (fstat(fd, &s) == -1 
        || !S_ISREG(s.st_mode))
        return perror("Error"), EXIT_FAILURE;
    if (s.st_size <= 64)
        return ft_putstr_fd("File format is not recognized\n", 2), EXIT_FAILURE;
    filemap = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (filemap == MAP_FAILED)
        return perror("Error"), EXIT_FAILURE;
    if (check_header(filemap, &elfclass) == -1)
        return ft_putstr_fd("File format is not recognized\n", 2), EXIT_FAILURE;
    printf("%d\n", 32 * elfclass);
    return EXIT_SUCCESS;
}