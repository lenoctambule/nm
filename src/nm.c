# include "nm.h"

void    print_error(char *file, char *message)
{
    (void) file; (void) message;
    ft_putstr_fd("'", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd("' : ", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd("\n", 2);
}


void    handle_path(char *path)
{
    t_file  file;

    file.fd  = open(path, O_RDONLY);
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
        cast_32_to_64(&file);
}