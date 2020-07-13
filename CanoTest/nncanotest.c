#include <libc.h>
#include <termios.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str != 0)
	{
		i++;
		str++;
	}
	return (i);
}

void putstr(char *str)
{
	int x;

	x = 0;
	while(str && str[x])
		x++;
	write(1,str,x);
}

void strend(char *str, char c)
{
	int i;

	i = 0;
	while(str && str[i])
		i++;
	str[i - 1] = c;
}
int	main(int argc, char **argv)
{
	int x = 0;
	struct termios  config;
	struct termios save;	
	int fd;
	tcgetattr(0, &save);
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
	config.c_iflag &= ~(IXON);
	config.c_oflag = 0;
	config.c_lflag &= ~(ECHO | ECHOE | ICANON | IEXTEN | ISIG);
	config.c_cflag &= 0;
	config.c_cflag |= CS8;
	config.c_cc[VMIN]  = 1;
	config.c_cc[VTIME] = 0;
	if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0)
   	{
    	printf("communication speed error\n");
		exit(0);
	}
	if(tcsetattr(fd, TCSADRAIN, &config) < 0)
	{
		printf("error applying configuration\n");
		exit(0);
	}

	char c = '\0';
	char *str;
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	char *tmp;
	int i = 0;
	int y = 0;
	write(1, "&>",2); 
	while(1)
	{
		write(1, &c, 1);
		int x = 0;
//		printf("test\n\r");
//		printf("%d\n",getchar());
		x = read(fd, &c, 1);
		if((int)c == 3 || (int)c == 4)
			break;
		else if ((int)c == 10)
		{
			putstr("\r\n&>");
			y = 1;
		}
		else if((int)c == 127)
		{
			putstr("\b \b");
			c = '\0';
			strend(str,'\0');
		}
		x = 0;
		i = ft_strlen(str);
		tmp = str;
		str = malloc(sizeof(char) * (i + 3));
		while(x < i)
		{
			str[x] = tmp[x];
			x++;
		}
		free(tmp);
		str[i] = c;
		str[i + 1] = (y == 1)? '\r': '\0';
	   	str[i + 2] = '\0';
		c = (y == 1)? '\0' : c;
		y = 0;		
	}
	putstr("\n\r");
	putstr(str);
	free(str);
	tcsetattr(0, TCSADRAIN, &save);
	close(fd);
}
