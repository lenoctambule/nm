# include "nm.h"

int check_header(char *bytes, int *elfclass)
{
    if ((bytes[EI_MAG0] != 0x7f
    || bytes[EI_MAG1] != 'E'
    || bytes[EI_MAG2] != 'L'
    || bytes[EI_MAG3] != 'F')
    && (bytes[EI_CLASS] != ELFCLASS32
    || bytes[EI_CLASS] != ELFCLASS64))
        return -1;
    *elfclass = bytes[EI_CLASS];
    return 1;
}