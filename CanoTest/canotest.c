#include <libc.h>
#include <termios.h>

int	main(int argc, char **argv)
{;
	int x = 0;
	struct termios  config;	
	int fd;

	fd = open("/dev/ttys0", O_RDWR | O_NOCTTY | O_NDELAY);
	fd = 0;
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
    	printf("communication speed error\n");
		exit(0);
	}
	if(tcsetattr(fd, 0, &config) < 0)
	{
		printf("error applying configuration\n");
		exit(0);
	}
	char str[100];
	while(1)
	{
		printf("test\n\r");
		printf("%d\n",getchar());
//		x = read(fd, str,sizeof(str));
//		str[x] = '\n';
//		printf("%s",str);	
	}
	close(fd);
}
