#include "nm.h"

static int  check_shndx64(t_elf_file *file, Elf64_Section shndx) {
    return (shndx < file->ehdr64.e_shnum);
}

static int  is_data64(t_elf_file *file, Elf64_Sym *symbol)
{
    return file->l_shdr64[symbol->st_shndx].sh_type != SHT_NOBITS
            && file->l_shdr64[symbol->st_shndx].sh_flags & SHF_ALLOC;;
}

static char  get_symbol_class64(t_elf_file *file, Elf64_Sym *symbol)
{
    (void) file;
    char    ret = '?';
    int     valid_shndx = check_shndx64(file, symbol->st_shndx);
    Elf64_Shdr  shstrhdr = file->l_shdr64[file->ehdr64.e_shstrndx];

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
        && is_data64(file, symbol))
    {
        if ((file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_WRITE)) == 0)
            ret = 'r';
        else if (file->l_shdr64[symbol->st_shndx].sh_flags & (SHF_IA_64_SHORT))
            ret = 'g';
        else
            ret = 'd';
    }
    if (valid_shndx && !(file->l_shdr64[symbol->st_shndx].sh_flags & SHF_ALLOC) && (ELF64_ST_TYPE(symbol->st_info) == STT_SECTION))
    {
        char    *name = strid_to_str(file->filemap + shstrhdr.sh_offset, file->l_shdr64[symbol->st_shndx].sh_name, shstrhdr.sh_size);
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
    if (ret == '?' && valid_shndx && ELF64_ST_TYPE(symbol->st_info) != SHT_NOBITS
        && !(file->l_shdr64[symbol->st_shndx].sh_flags & SHF_WRITE))
        return 'n';
    if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
        ret = ft_toupper(ret);
    return (ret);
}

int     extract_symtab64(t_elf_file *file, Elf64_Shdr *shdr)
{
    (void) file; (void) shdr;
    Elf64_Sym   *symbols = file->filemap + shdr->sh_offset;
    Elf64_Shdr  link = file->l_shdr64[shdr->sh_link];
    Elf64_Shdr  shstrhdr = file->l_shdr64[file->ehdr64.e_shstrndx];
    size_t      num = shdr->sh_size / sizeof(Elf64_Sym);
    t_symbol    sym;

    for (size_t i = 1; i < num; i++)
    {
        sym.class = get_symbol_class64(file, &symbols[i]);
        if (!sym.class
            || ((sym.class == 'a' || ELF64_ST_TYPE(symbols[i].st_info) == STT_SECTION) && !print_debug))
            continue;
        if (external &&
            !(ELF64_ST_BIND(symbols[i].st_info) == STB_GLOBAL
            || ELF64_ST_BIND(symbols[i].st_info) == STB_WEAK))
            continue;
        if (undefined && (symbols[i].st_shndx != SHN_UNDEF))
            continue;
        if (ELF64_ST_TYPE(symbols[i].st_info) == STT_SECTION)
            sym.name = strid_to_str(file->filemap + shstrhdr.sh_offset, file->l_shdr64[symbols[i].st_shndx].sh_name, shstrhdr.sh_size);
        else
            sym.name = strid_to_str(file->filemap + link.sh_offset, symbols[i].st_name, link.sh_size);
        sym.value = symbols[i].st_value;
        sym.is_undefined = symbols[i].st_shndx == SHN_UNDEF;
        if (sym.name != NULL)
        {
            if (no_sort)
                print_sym(file, &sym);
            else
                file->l_symbols[file->symc++] = sym;
        }
    }
    return 0;
}

static int      check_offset64(t_elf_file *file, int i)
{
    return file->l_shdr64[i].sh_offset + file->l_shdr64[i].sh_size >= (Elf64_Off)file->s.st_size;
}

static int      count_symbols64(t_elf_file *file)
{
    size_t  count = 0;

    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
        if (file->l_shdr64[i].sh_type == SHT_SYMTAB
            && !check_offset64(file, i))
            count += file->l_shdr64[i].sh_size / sizeof(Elf64_Sym);
    }
    return count;
}

void    parse64(t_elf_file *file)
{
    size_t  symcount = 0;

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
    symcount = count_symbols64(file);
    if (symcount == 0)
        return print_error(file->path, "no symbols");
    if (!no_sort)
    {
        file->l_symbols = (t_symbol *)malloc(symcount * sizeof(t_symbol));
        if (file->l_symbols == NULL)
            return print_error(file->path, strerror(errno));
    }
    ft_memset(file->l_symbols, 0, symcount * sizeof(t_symbol));
    for (size_t i = 0; i < file->ehdr64.e_shnum; i++)
    {
        if (file->l_shdr64[i].sh_type == SHT_SYMTAB
            && !check_offset64(file, i))
            extract_symtab64(file, &file->l_shdr64[i]);
    }
    if (!no_sort)
    {
        sort_symbols(file);
        for (size_t i = 0; i < file->symc; i++)
            print_sym(file, &file->l_symbols[i]);
    }
}