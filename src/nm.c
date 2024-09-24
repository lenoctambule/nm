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
    if (!check_ehdr_ident(filemap, &elfclass))
        return print_error(path, "File format is not recognized");
    if (elfclass == ELFCLASS64)
    {
        Elf64_Ehdr  hdr = *(Elf64_Ehdr *)filemap;

        if (!check_ehdr_common(hdr.e_type, hdr.e_machine, hdr.e_version))
            return print_error(path, "File format is not recognized");
    }
    else
    {
        Elf32_Ehdr  hdr = *(Elf32_Ehdr *)filemap;

        if (!check_ehdr_common(hdr.e_type, hdr.e_machine, hdr.e_version))
            return print_error(path, "File format is not recognized");
    }
}