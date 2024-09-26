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

#

typedef struct stat t_stat;

typedef struct s_file {
    t_stat      s;
    char        *path;
    int         fd;
    void        *filemap;
    int         elfclass;
    Elf64_Ehdr  ehdr64;
    Elf32_Ehdr  ehdr32;
    Elf64_Shdr  *l_shdr64;
    Elf32_Shdr  *l_shdr32;
} t_elf_file;

void    parse32(t_elf_file *file);
void    parse64(t_elf_file *file);

int     check_ehdr_ident(char *bytes, int *elfclass);
int     check_ehdr_body(t_elf_file *file,
                        uint16_t    e_type,
                        uint16_t    e_machine,
                        uint32_t    e_version,
                        Elf64_Off   e_phoff,
                        Elf64_Off   e_shoff,
                        Elf64_Word  e_flags,
                        Elf64_Half  e_ehsize,
                        Elf64_Half  e_phentsize,
                        Elf64_Half  e_phnum,
                        Elf64_Half  e_shentsize,
                        Elf64_Half  e_shnum,
                        Elf64_Half  e_shstrndx);
int     check_shdr(t_elf_file *file,
                    Elf64_Word  sh_type,
                    Elf64_Off   sh_offset,
                    Elf64_Xword sh_size,
                    Elf64_Word  sh_link);

void    print_addr(size_t addr);
void    print_error(char *file, char *message);
char    *strid_to_str(char *strsec, size_t n, size_t limit);

void    handle_path(char *path);

#endif