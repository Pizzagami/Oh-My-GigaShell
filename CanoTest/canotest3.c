#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int	open_port(void)
{
  int fd; /* File descriptor for the port */
  
  
  fd = open("/dev/ttys0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
    {
      /*
       * Could not open the port.
       */
      
      perror("open_port: Unable to open /dev/ttyS0 - ");
    }
  else
    fcntl(fd, F_SETFL, 0);
  
  return (fd);
}


void config_port(int fd)
{
  struct termios options;
  
  /*
   * Get the current options for the port...
   */
  
  tcgetattr(fd, &options);
  
  /*
   * Set the baud rates to 9600
   */
  
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  
  /*
   * Enable the receiver and set local mode...
   */
  
  options.c_cflag |= (CLOCAL | CREAD);

  /*
   * Setting Parity Checking
   */
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  /*
   * Setting Hardware Flow Control
   */
  options.c_cflag &= ~CRTSCTS;
  
  /*
   * Choosing Canonical (line oriented) Input
   */
  options.c_lflag |= ICANON;

  options.c_iflag &= ~(IXON | IXOFF | IXANY);
  options.c_oflag |= OPOST;

  /*
   * Set the new options for the port...
   */
  
  tcsetattr(fd, TCSANOW, &options);
}


int main(void)
{
  int fd;
  char *msg;
  char buff[100];
  int n;

  msg = "Listen....\n";
  fd = open_port();
  config_port(fd);

  write(fd, msg, 6);
  n = read(fd, buff, sizeof(buff));
  buff[n] = '\0';

  printf("%s", buff);
  close(fd);
}

