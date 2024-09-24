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