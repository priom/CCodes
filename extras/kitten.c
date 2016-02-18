/*
 * Unix cat utility clone
 * Tami Meredith, Fall 2015
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int
main (argc, argv) 
  int argc;
  char **argv;
{
  char buf[BUFSIZE];
  size_t cnt;

  int  fd = open(argv[1],O_RDONLY);
  while ((cnt = read(fd,buf,BUFSIZE)) > 0) {
    write(1,buf,cnt);
  }
  return (0);
}
