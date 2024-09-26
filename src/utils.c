#include "nm.h"

int check_options(int ac, char **av)
{
    for (int i = 0; i < ac; i++)
    {
        if (av[i][0] != '-')
            return i;
        for (int j = 1; av[i][j]; j++)
        {
            switch (av[i][j])
            {
            case 'a':
                print_debug = 1;
                break;
            case 'r':
                rev_sort = 1;
                break;
            case 'p':
                no_sort = 1;
                break;
            case 'g':
                external = 1;
                break;
            case 'u':
                undefined = 1;
                break;
            default:
                return -1;
                break;
            }
        }
    }
    return 0;
}

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
        str[15 - i] = digits[addr % 16];
        addr /= 16;
    }
    ft_putstr_fd(str, 1);
}

void    print_sym(t_symbol *sym, Elf64_Section shndx)
{
    if (shndx != SHN_UNDEF)
        print_addr(sym->value);
    else
        ft_putstr_fd("                ", 1);
    ft_putchar_fd(' ', 1);
    ft_putchar_fd(sym->class, 1);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd(sym->name, 1);
    ft_putchar_fd('\n', 1);
}

char    *strid_to_str(char *strsec, size_t n, size_t limit)
{
    if (n > limit)
        return NULL;
    return strsec + n;
}