#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
 *
 *  struct stat {
 *  int dev;     // File system's disk device
 *  uint ino;    // Inode number
 *  short type;  // Type of file
 *  short nlink; // Number of links to file
 *  uint64 size; // Size of file in bytes
 *  };
 *
 *  T_DIR = 1;
 *  T_FILE = 2;
 *
 * Directory is a file containing a sequence of dirent structures.
 * #define DIRSIZ 14
 *
 * struct dirent {
 *   ushort inum;
 *   char name[DIRSIZ];
 * };
 *
 */

void find(const char *path, const char *search)
{
    int fd;
    char buf[512], *p;
    struct stat st;
    struct dirent de;

    if((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        exit(1);
    }

    if(fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat &s\n", path);
        close(fd);
        exit(1);
    }
    /* Copies path into buf including null byte*/
    strcpy(buf, path);
    /* point p at buf + strlen(buf) */
    p = buf+strlen(buf);
    /* p[buf+strlen(buf)] = '/' */
    *p++ = '/';

    /* while read returns 16 bytes (correct read) populate dirent de */
    /* read each file and poplate struct dirent de */
    while(read(fd, &de, sizeof(de)) == sizeof(de)){

        /* Skips current loop iteration if inum == 0 */
        /* skip if . or .. */
        if(de.inum == 0)
            continue;

        if(!strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;

        /* copy DIRSIZE bytes of de.name into p\buf */
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        /* get stats of buf path */
        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }

        /* if type is dir then search */
        if(st.type == 1)
        {
            find(buf, search);
        }

        /* file found print */
        if(!strcmp(search, p))
            printf("%s\n", buf);
    }
}


int
main(int argc, char *argv[])
{
    char path[512];
    char search[512];

    if(argc < 2)
    {
        fprintf(2, "find: incorrect usage find <name>%s\n", path);
        exit(1);
    }

    if(argc == 3)
    {
        strcpy(path, argv[1]);
        strcpy(search, argv[2]);
        find(path, search);
    }

    strcpy(search, argv[1]);
    find(".", search);

  exit(0);
}
