#include "nm.h"


void    parse(t_file file)
{
    Elf64_Ehdr  hdr = *(Elf64_Ehdr *)file.filemap;

    if (!check_ehdr_common(hdr.e_type, hdr.e_machine, hdr.e_version))
        return print_error(file.path, "File format is not recognized");
}