#include "nm.h"

int main(int ac, char **av)
{
    ac--; av++;
    if (ac == 0)
        return ft_putstr_fd("Invalid args.\nUsage : nm <file_path>\n", 2), EXIT_FAILURE;
    for (int i = 0; i < ac; i++)
        handle_path(av[i]);
    return EXIT_SUCCESS;
}