#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_getch()
{
	struct termios config;
	char sequence[10];
	int svg;
	int pos;
	int entier;

	tcgetattr(STDIN_FILENO, &config);
	svg = config.c_lflag;
	config.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	pos = 0;
	entier=getchar();
	if (entier==27)
	{
		entier=getchar();
		sequence[pos]=(char)entier;
		++pos;
		if (entier=='[') 
		{ 
			do 
			{ 
				entier=getchar();
				sequence[pos]=(char)entier;
				++pos;
			} 
			while (entier <= 0x40);
			sequence[pos]='\0';
			if (strcmp(sequence,"[A")==0)
				entier=403; 
			// fleche haute = 27
			else if (strcmp(sequence,"[21~")==0)
				entier=420; // touche F10=27
			else
				entier = 0; 
		}
		else
		{
			ungetc(entier,stdin);
			entier=0;
		}
	}
	config.c_lflag = svg;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	return entier;
}

int main() 
{ 
	printf("test - Appuyer sur une touche : ");
	int retour=my_getch();
	printf("\nvaleur entier de retour : %d\n",retour);
	return 0; 
} 

