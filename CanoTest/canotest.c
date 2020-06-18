#include <libc.h>
#include <termios.h>

int	main(int argc, char **argv)
{
	char str[100000] = {0};
	int x = 0;
	struct termios  config;	
	int fd;

	fd = open("/dev/ttys0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
		{
			printf("FAILURE\n");
			exit(0);
		}
	if (!isatty(fd)) 
		{
			printf("tts0 non lier au terminal \n");
			exit(0);
		}
	if (tcgetattr(fd, &config) < 0)
		{ 
			printf("config termios failure \n");
			exit(0);
		}	
	config.c_iflag &= ~(IUTF8 | IXON);
	config.c_oflag = 0;
	config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	config.c_cflag &= 0;
	config.c_cflag |= CS8;
	config.c_cc[VMIN]  = 1;
	config.c_cc[VTIME] = 0;
	if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0)
   	{
    	printf("com speed error\n");
		exit(0);
	}
	if(tcsetattr(fd, TCSAFLUSH, &config) < 0)
	{
		printf("error applying configuration\n");
		exit(0);
	}
	
	

	close(fd);
//	x = read(0, str, 100000);
}
