# include "nm.h"

void    handle_path(char *path)
{
    t_elf_file  file;

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