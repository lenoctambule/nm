#include "nm.h"

static int  check_shndx(t_elf_file *file, Elf64_Section shndx) {
    return (shndx < file->ehdr64.e_shnum);
}

static int is_data(t_elf_file *file, Elf64_Sym *symbol)
{
    return file->l_shdr64[symbol->st_shndx].sh_type != SHT_NOBITS
            && file->l_shdr64[symbol->st_shndx].sh_flags & SHF_ALLOC;;
}

static char  get_symbol_class(t_elf_file *file, Elf64_Sym *symbol)
{
    (void) file;
    char    ret = '?';
    int     valid_shndx = check_shndx(file, symbol->st_shndx);

    if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
    {
        if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
            ret = 'v';
        else
            ret = 'w';
        if (symbol->st_shndx != SHN_UNDEF)
            ret = ft_toupper(ret);
        return ret;
    }
    if (ELF64_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE)
         return 'u';
    if (symbol->st_shndx == SHN_UNDEF)
         return 'U';
    if (valid_shndx
        && file->l_shdr64[symbol->st_shndx].sh_flags & SHF_EXECINSTR)
        ret = 't';
    else if (symbol->st_shndx == SHN_ABS)
        ret = 'a';
    else if (valid_shndx
        && file->l_shdr64[symbol->st_shndx].sh_type == SHT_NOBITS)
        ret = 'b';
    else if (symbol->st_shndx == SHN_COMMON)
        ret = 'c';
    else if (valid_shndx
        && is_data(file, symbol))
    {
        if ((file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_WRITE)) == 0)
            ret = 'r';
        else if (file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_IA_64_SHORT))
            ret = 'g';
        else
            ret = 'd';
    }
    else if (valid_shndx
        && file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_IA_64_SHORT))
        ret = 'g';
    if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
        ret = ft_toupper(ret);
    return (ret);
}

int     extract_symtab64(t_elf_file *file, Elf64_Shdr *shdr)
{
    (void) file; (void) shdr;
    Elf64_Sym   *symbols = file->filemap + shdr->sh_offset;
    Elf64_Shdr  link = file->l_shdr64[shdr->sh_link];
    size_t      num = shdr->sh_size / sizeof(Elf64_Sym);
    t_symbol    sym;

    for (size_t i = 1; i < num; i++)
    {
        sym.class = get_symbol_class(file, &symbols[i]);
        if (!sym.class || (sym.class == 'a' && !print_debug))
            continue;
        sym.name = strid_to_str(file->filemap + link.sh_offset, symbols[i].st_name, link.sh_size);
        if (sym.name != NULL || *sym.name == 0)
        {
            print_sym(&sym, symbols[i].st_shndx);
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
        if (file->l_shdr64[i].sh_type == SHT_SYMTAB)
            extract_symtab64(file, &file->l_shdr64[i]);
    }
}