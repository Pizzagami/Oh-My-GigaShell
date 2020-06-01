#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
 
#define BUFF_LEN        1024
 
int          main(int argc, char *argv[])
{
  int        ret;
  char       buff[BUFF_LEN];
 
  if (argc > 1)
    {
      printf("Before: %s\n", getcwd(buff, BUFF_LEN -1));
      ret = chdir(argv[1]);
      if (ret != 0)
        {
          fprintf(stderr, "%s\n", strerror(errno));
        }
      printf("After: %s\n", getcwd(buff, BUFF_LEN -1));
    }
  else
    printf("usage: %s <directory>\n", argv[0]);
  return (0);
}
