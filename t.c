#include <signal.h>
#include <unistd.h>

void langis(int nbr)
{
	(void)nbr;
}

int main(void)
{
	char *t;

	signal(SIGINT, langis);
	signal(SIGQUIT, langis);
	read(0, &t, 1);
	read(0, &t, 1);
	read(0, &t, 1);
	read(0, &t, 1);
}
