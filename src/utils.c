#include "nm.h"

void    cast_32_to_64(t_file *file)
{
    file->ehdr64.e_type = file->ehdr32.e_type;
    file->ehdr64.e_machine = file->ehdr32.e_machine;
    file->ehdr64.e_version = file->ehdr32.e_version;
    file->ehdr64.e_entry = file->ehdr32.e_entry;       // Entry point address
    file->ehdr64.e_phoff = file->ehdr32.e_phoff;       // Program header offset
    file->ehdr64.e_shoff = file->ehdr32.e_shoff;       // Section header offset
    file->ehdr64.e_flags = file->ehdr32.e_flags;       // Processor-specific flags
    file->ehdr64.e_ehsize = file->ehdr32.e_ehsize;     // ELF header size
    file->ehdr64.e_phentsize = file->ehdr32.e_phentsize; // Program header entry size
    file->ehdr64.e_phnum = file->ehdr32.e_phnum;       // Program header count
    file->ehdr64.e_shentsize = file->ehdr32.e_shentsize; // Section header entry size
    file->ehdr64.e_shnum = file->ehdr32.e_shnum;       // Section header count
    file->ehdr64.e_shstrndx = file->ehdr32.e_shstrndx; // Section header string index
}
