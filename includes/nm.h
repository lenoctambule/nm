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

void    print_error(char *file, char *message);
int     check_header(char *bytes, int *elfclass);
void    handle_path(char *path);

#endif