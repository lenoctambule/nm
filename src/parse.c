#include "nm.h"


void    parse32(t_elf_file *file)
{
    (void) file;
}

void    parse64(t_elf_file *file)
{
    file->ehdr64 = *(Elf64_Ehdr *)file->filemap;
    if (!check_ehdr_body(file,
                        file->ehdr64.e_type,
                        file->ehdr64.e_machine,
                        file->ehdr64.e_version,
                        file->ehdr64.e_phoff,
                        file->ehdr64.e_shoff,
                        file->ehdr64.e_flags,
                        file->ehdr64.e_ehsize,
                        file->ehdr64.e_phentsize,
                        file->ehdr64.e_phnum,
                        file->ehdr64.e_shentsize,
                        file->ehdr64.e_shnum,
                        file->ehdr64.e_shstrndx))
        return ;
    file->l_shdr64 = file->filemap + file->ehdr64.e_shoff;
    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
        if (!check_shdr(file,
                        file->l_shdr64[i].sh_type,
                        file->l_shdr64[i].sh_offset,
                        file->l_shdr64[i].sh_size,
                        file->l_shdr64[i].sh_link))
            return ;
    }
    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
    }
}