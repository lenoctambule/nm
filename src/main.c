#include "nm.h"

int     print_debug = 0;
int     no_sort = 0;
int     rev_sort = 0;
int     external = 0;
int     undefined = 0;

void    handle_path(char *path)
{
    t_elf_file  file;

    ft_memset(&file, 0, sizeof(t_elf_file));
    file.fd  = open(path, O_RDONLY);
    file.path = path;
    if (file.fd == -1)
        return print_error(path, strerror(errno));
    if (fstat(file.fd, &file.s) == -1)
        return print_error(path, strerror(errno));
    if (!S_ISREG(file.s.st_mode))
        return print_error(path, "Is a directory");
    if (file.s.st_size <= 64)
        return print_error(path, "File format is not recognized");
    file.filemap = mmap(NULL, file.s.st_size, PROT_READ,
                        MAP_PRIVATE, file.fd, 0);
    if (file.filemap == MAP_FAILED)
        return print_error(path, strerror(errno));
    if (!check_ehdr_ident(file.filemap, &file.elfclass))
        return print_error(path, "File format is not recognized");
    if (file.elfclass == ELFCLASS32)
        parse32(&file);
    else
        parse64(&file);
}

int main(int ac, char **av)
{
    ac--; av++;
    if (ac == 0)
        handle_path("a.out");
    else
    {
        int i = check_options(ac, av);
        if (i == -1)
            return ft_putstr_fd("Invalid option.\n", 1), EXIT_FAILURE;
        for (; i < ac; i++)
            handle_path(av[i]);
    }
    return EXIT_SUCCESS;
}