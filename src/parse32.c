#include "nm.h"

static int  check_shndx32(t_elf_file *file, Elf32_Section shndx) {
    return (shndx < file->ehdr32.e_shnum);
}

static int  is_data32(t_elf_file *file, Elf32_Sym *symbol)
{
    return file->l_shdr32[symbol->st_shndx].sh_type != SHT_NOBITS
            && file->l_shdr32[symbol->st_shndx].sh_flags & SHF_ALLOC;;
}

static char  get_symbol_class32(t_elf_file *file, Elf32_Sym *symbol)
{
    (void) file;
    char    ret = '?';
    int     valid_shndx = check_shndx32(file, symbol->st_shndx);
    Elf32_Shdr  shstrhdr = file->l_shdr32[file->ehdr32.e_shstrndx];

    if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK)
    {
        if (ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT)
            ret = 'v';
        else
            ret = 'w';
        if (symbol->st_shndx != SHN_UNDEF)
            ret = ft_toupper(ret);
        return ret;
    }
    if (ELF32_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE)
         return 'u';
    if (symbol->st_shndx == SHN_UNDEF)
         return 'U';
    if (valid_shndx
        && file->l_shdr32[symbol->st_shndx].sh_flags & SHF_EXECINSTR)
        ret = 't';
    else if (symbol->st_shndx == SHN_ABS)
        ret = 'a';
    else if (valid_shndx
        && file->l_shdr32[symbol->st_shndx].sh_type == SHT_NOBITS)
        ret = 'b';
    else if (symbol->st_shndx == SHN_COMMON)
        ret = 'c';
    else if (valid_shndx
        && is_data32(file, symbol))
    {
        if ((file->l_shdr32[symbol->st_shndx].sh_flags & (SHF_WRITE)) == 0)
            ret = 'r';
        else if (file->l_shdr32[symbol->st_shndx].sh_flags & (SHF_IA_64_SHORT))
            ret = 'g';
        else
            ret = 'd';
    }
        if (valid_shndx && !(file->l_shdr32[symbol->st_shndx].sh_flags & SHF_ALLOC) && (ELF32_ST_TYPE(symbol->st_info) == STT_SECTION))
    {
        char    *name = strid_to_str(file->filemap + shstrhdr.sh_offset, file->l_shdr32[symbol->st_shndx].sh_name, shstrhdr.sh_size);
        if (name != NULL)
        {
            int     n = ft_strlen(name);
            char    *db_name[] = {".debug", ".line", ".stab", ".zdebug", NULL};

            for (int i = 0; db_name[i] != NULL; i++)
            {
                if (ft_strnstr(name, db_name[i], n) == name)
                    return 'N';
            }
        }
    }
    if (ret == '?' && valid_shndx && ELF32_ST_TYPE(symbol->st_info) != SHT_NOBITS
        && !(file->l_shdr32[symbol->st_shndx].sh_flags & SHF_WRITE))
        return 'n';
    if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
        ret = ft_toupper(ret);
    return (ret);
}

int     extract_symtab32(t_elf_file *file, Elf32_Shdr *shdr)
{
    (void) file; (void) shdr;
    Elf32_Sym   *symbols = file->filemap + shdr->sh_offset;
    Elf32_Shdr  link = file->l_shdr32[shdr->sh_link];
    size_t      num = shdr->sh_size / sizeof(Elf32_Sym);
    t_symbol    sym;

    for (size_t i = 1; i < num; i++)
    {
        sym.class = get_symbol_class32(file, &symbols[i]);
        if (!sym.class
            || (sym.class == 'a' && !print_debug))
            continue;
        if (external &&
            !(ELF32_ST_BIND(symbols[i].st_info) == STB_GLOBAL
            || ELF32_ST_BIND(symbols[i].st_info) == STB_WEAK))
            continue;
        if (undefined && (symbols[i].st_shndx != SHN_UNDEF))
            continue;
        sym.name = strid_to_str(file->filemap + link.sh_offset, symbols[i].st_name, link.sh_size);
        sym.value = symbols[i].st_value;
        sym.is_undefined = symbols[i].st_shndx == SHN_UNDEF;
        if (sym.name != NULL && sym.name[0] != 0)
        {
            if (no_sort)
                print_sym(file, &sym);
            else
                file->l_symbols[file->symc++] = sym;
        }
    }
    return 0;
}

static int      check_offset32(t_elf_file *file, int i)
{
    return file->l_shdr32[i].sh_offset + file->l_shdr32[i].sh_size >= (Elf32_Off)file->s.st_size;
}

static int      count_symbols32(t_elf_file *file)
{
    size_t  count = 0;

    for (size_t i = 0; i < file->ehdr32.e_shnum; i++)
    {
        if (file->l_shdr32[i].sh_type == SHT_SYMTAB
            && !check_offset32(file, i))
            count += file->l_shdr32[i].sh_size / sizeof(Elf32_Sym);
    }
    return count;
}

void    parse32(t_elf_file *file)
{
    size_t  symcount = 0;

    file->ehdr32 = *(Elf32_Ehdr *)file->filemap;
    if (!check_ehdr_body(file,
                        file->ehdr32.e_type,
                        file->ehdr32.e_machine,
                        file->ehdr32.e_version,
                        file->ehdr32.e_phoff,
                        file->ehdr32.e_shoff,
                        file->ehdr32.e_flags,
                        file->ehdr32.e_ehsize,
                        file->ehdr32.e_phentsize,
                        file->ehdr32.e_phnum,
                        file->ehdr32.e_shentsize,
                        file->ehdr32.e_shnum,
                        file->ehdr32.e_shstrndx))
        return ;
    file->l_shdr32 = file->filemap + file->ehdr32.e_shoff;
    for (size_t i = 0; i < file->ehdr32.e_shnum; i++)
    {
        if (!check_shdr(file,
                        file->l_shdr32[i].sh_type,
                        file->l_shdr32[i].sh_offset,
                        file->l_shdr32[i].sh_size,
                        file->l_shdr32[i].sh_link))
            return ;
    }
    symcount = count_symbols32(file);
    if (symcount == 0)
        return print_error(file->path, "no symbols");
    if (!no_sort)
    {
        file->l_symbols = (t_symbol *)malloc(symcount * sizeof(t_symbol));
        if (file->l_symbols == NULL)
            return print_error(file->path, strerror(errno));
    }
    ft_memset(file->l_symbols, 0, symcount * sizeof(t_symbol));
    for (size_t i = 0; i < file->ehdr32.e_shnum; i++)
    {
        if (file->l_shdr32[i].sh_type == SHT_SYMTAB
            && !check_offset32(file, i))
            extract_symtab32(file, &file->l_shdr32[i]);
    }
    if (!no_sort)
    {
        sort_symbols(file);
        for (size_t i = 0; i < file->symc; i++)
            print_sym(file, &file->l_symbols[i]);
    }
}