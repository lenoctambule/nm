#include "nm.h"

void    print_error(char *file, char *message)
{
    (void) file; (void) message;
    ft_putstr_fd("'", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd("' : ", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd("\n", 2);
}

void    print_addr(size_t addr)
{
    char    str[] = "0000000000000000";
    char    digits[] = "0123456789abcdef";
    for (size_t i = 0; i < sizeof(size_t) * 2; i++)
    {
        str[16 - i] = digits[addr % 16];
        addr /= 16;
    }
    ft_putstr_fd(str, 1);
}

char    *strid_to_str(char *strsec, size_t n, size_t limit)
{
    if (n > limit)
        return NULL;
    return strsec + n;
}