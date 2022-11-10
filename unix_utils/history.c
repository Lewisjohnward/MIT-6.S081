#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/*
 *
 * Time taken: 2:30
 *
 * I was first rumaging around incorrectly with console in the kernel dir 
 * this is a  program that will print from a file that is appended to
 * with the string given by to the shell in file .history 
 *
 * NOTES
 *
 * #define O_RDONLY  0x000
 * #define O_WRONLY  0x001
 * #define O_RDWR    0x002
 * #define O_CREATE  0x200
 * #define O_TRUNC   0x400
 *
 */

/*This is user/history.c */
int
main(int argc, char *argv[])
{
  //char str[] = "history WIP\n";
  //fprintf(1, str, strlen(str)); 
  char buf[512];
  char *p;
  p = buf;
  int bytes;
  char error[] = "Unable to open .history";
  int fd;
  if((fd = open(".history", O_RDONLY)) < 0)
  {
      fprintf(2, error, strlen(error));
      exit(1);
  }

  bytes = read(fd, p, 512);
  p[bytes] = 0;
  printf("%s", buf);

  exit(0);
}


/* This part needs to go into user/sh.c */
void 
updatehistory(const char *str)
{
    int fd;
    char tmp;
    if((fd = open(".history", O_CREATE | O_RDWR)) < 0)
        fprintf(2, "cannot open history\n");

    /* put position at the back of file */
    while((read(fd, &tmp, 1)) != 0)
    {}

    if((write(fd, str, strlen(str))) <= 0)
        fprintf(2, "write history\n");
}
