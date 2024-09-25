#include "nm.h"


void    parse32(t_file *file)
{
    (void) file;
}

void    parse64(t_file *file)
{
    file->ehdr64 = *(Elf64_Ehdr *)file->filemap;
    if (!check_ehdr_common(file->ehdr64.e_type, file->ehdr64.e_machine, file->ehdr64.e_version))
        return print_error(file->path, "File format is not recognized");
    file->l_shdr64 = (Elf64_Shdr *) malloc(file->ehdr64.e_shnum * sizeof(Elf32_Shdr));
    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
        size_t      offset  = file->ehdr64.e_shoff + i * file->ehdr64.e_shentsize;
        memcpy(&file->l_shdr64[i], file->filemap + offset, sizeof(Elf64_Shdr));
    }
}