#include "nm.h"

int     check_ehdr_ident(char *bytes, int *elfclass)
{
    if ((
           bytes[EI_MAG0] != 0x7f
        && bytes[EI_MAG1] != 'E'
        && bytes[EI_MAG2] != 'L'
        && bytes[EI_MAG3] != 'F'
        )
    || (
        bytes[EI_CLASS] != ELFCLASS32
        && bytes[EI_CLASS] != ELFCLASS64
        )
    ||
        (
        bytes[EI_DATA] != ELFDATA2LSB
        && bytes[EI_DATA] != ELFDATA2MSB
        )
    ||
        (
        bytes[EI_VERSION] != EV_NONE
        && bytes[EI_VERSION] != EV_CURRENT
        )
    ||
        (
            bytes[EI_OSABI] != ELFOSABI_NONE && bytes[EI_OSABI] != ELFOSABI_SYSV &&
            bytes[EI_OSABI] != ELFOSABI_LINUX && bytes[EI_OSABI] != ELFOSABI_SOLARIS
        )
    ||
        (
            bytes[EI_ABIVERSION] != 0
        )
    )
        return (0);
    *elfclass = bytes[EI_CLASS];
    return (1);
}

int     check_ehdr_common(uint16_t e_type,
                        uint16_t e_machine,
                        uint32_t e_version)
{
    if ((e_type > ET_CORE)
        || !(e_machine == EM_X86_64 || e_machine == EM_386)
        || e_version != EV_CURRENT
    )
        return (0);
    return (1);
}
