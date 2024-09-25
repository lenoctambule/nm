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
    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
        size_t      offset  = file->ehdr64.e_shoff + i * file->ehdr64.e_shentsize;
        Elf64_Shdr  *shdr   = (Elf64_Shdr *)(file->filemap + offset);
        if (shdr->sh_type == SHT_SYMTAB)
            printf("symbol section found at %lX and ends at %lX\n", shdr->sh_offset, shdr->sh_offset + shdr->sh_size);
        if (shdr->sh_type == SHT_DYNSYM)
            printf("dl symbol section found at %lX and ends at %lX\n", shdr->sh_offset, shdr->sh_offset + shdr->sh_size);
        if (shdr->sh_type == SHT_STRTAB)
            printf("str section found at %lX and ends at %lX\n", shdr->sh_offset, shdr->sh_offset + shdr->sh_size);
        if (shdr->sh_type == SHT_STRTAB && i == file->ehdr64.e_shstrndx)
            printf(".shstrtab section found at %lX and ends at %lX\n", shdr->sh_offset, shdr->sh_offset + shdr->sh_size);
    }
}