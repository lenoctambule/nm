#include "nm.h"

void    parse32(t_elf_file *file)
{
    (void) file;
}

static char  is_relevant(t_elf_file *file, Elf64_Sym *symbol)
{
    (void) file;
    char ret = '?';
    if (symbol->st_shndx == SHN_ABS)
        ret = 'a';
    else if (file->l_shdr64[symbol->st_shndx].sh_type == SHT_NOBITS)
        ret = 'b';
    else if (symbol->st_shndx == SHN_COMMON)
        ret = 'c';
    else if (file->l_shdr64[symbol->st_shndx].sh_type == SHT_PROGBITS && file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_ALLOC | SHF_WRITE))
        ret = 'd';
    if (ELF64_ST_VISIBILITY(symbol->st_info) == STB_GLOBAL)
        ret = ft_toupper(ret);
    return (ret);
}

int     extract_symtab64(t_elf_file *file, Elf64_Shdr *shdr)
{
    (void) file; (void) shdr;
    Elf64_Sym   *symbols = file->filemap + shdr->sh_offset;
    Elf64_Shdr  link = file->l_shdr64[shdr->sh_link];
    size_t      num = shdr->sh_size / sizeof(Elf64_Sym);
    for (size_t i = 0; i < num; i++)
    {
        char    type = is_relevant(file, &symbols[i]);
        if (!type)
            continue;
        char *str = strid_to_str(file->filemap + link.sh_offset, symbols[i].st_name, link.sh_size);
        if (str != NULL && str[0])
        {
            // print_addr(symbols[i].st_value);
            ft_putchar_fd(' ', 1);
            ft_putchar_fd(type, 1);
            ft_putchar_fd(' ', 1);
            ft_putstr_fd(str, 1);
            ft_putchar_fd('\n', 1);
        }
    }
    return 0;
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
        if (file->l_shdr64[i].sh_type == SHT_SYMTAB || file->l_shdr64[i].sh_type == SHT_DYNSYM)
            extract_symtab64(file, &file->l_shdr64[i]);
    }
}