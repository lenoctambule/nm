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

int     check_ehdr_ident(char *bytes, int *elfclass);
int     check_ehdr_common(uint16_t e_type,
                        uint16_t e_machine,
                        uint32_t e_version);

void    print_error(char *file, char *message);
void    handle_path(char *path);

#endif