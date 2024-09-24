#ifndef __NM__
# define __NM__

# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h> 
# include <errno.h>
# include <stdio.h>
# include <elf.h>
# include <sys/mman.h>

typedef struct stat t_stat;

typedef struct s_file {
    t_stat      s;
    char        *path;
    int         fd;
    void        *filemap;
    int         elfclass;
    Elf64_Ehdr  ehdr64;
    Elf32_Ehdr  ehdr32;
} t_file;

void    cast_32_to_64(t_file *file);

int     check_ehdr_ident(char *bytes, int *elfclass);
int     check_ehdr_common(uint16_t e_type,
                        uint16_t e_machine,
                        uint32_t e_version);

void    print_error(char *file, char *message);
void    handle_path(char *path);

#endif