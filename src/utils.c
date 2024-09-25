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

char    *strid_to_str(char *strsec, size_t n, size_t limit)
{
    size_t i = 0;
    size_t j = 0;

    while (j < limit)
    {
        if (i == n)
            return (strsec + j);
        if (strsec[j] == 0)
            i++;
        j++;
    }
    return NULL;
}