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

int     check_header(char *bytes, int *elfclass)
{
    if ((bytes[EI_MAG0] != 0x7f
    || bytes[EI_MAG1] != 'E'
    || bytes[EI_MAG2] != 'L'
    || bytes[EI_MAG3] != 'F')
    && (bytes[EI_CLASS] != ELFCLASS32
    || bytes[EI_CLASS] != ELFCLASS64))
        return -1;
    *elfclass = bytes[EI_CLASS];
    return 1;
}

void    handle_path(char *path)
{

    int     fd;
    t_stat  s;
    void    *filemap;
    int     elfclass = ELFCLASSNONE;

    fd  = open(path, O_RDONLY);
    if (fd == -1)
        return print_error(path, strerror(errno));
    if (fstat(fd, &s) == -1)
        return print_error(path, strerror(errno));
    if (!S_ISREG(s.st_mode))
        return print_error(path, "Is a directory");
    if (s.st_size <= 64)
        return print_error(path, "File format is not recognized");
    filemap = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (filemap == MAP_FAILED)
        return print_error(path, strerror(errno));
    if (check_header(filemap, &elfclass) == -1)
        return print_error(path, "File format is not recognized");
    printf("%d\n", 32 * elfclass);
}