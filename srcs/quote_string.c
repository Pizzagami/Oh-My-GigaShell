#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char(char *str, int index)
{
	int x;
	x = 0;
	while (x < index)
		x++;
	while (str[x])
	{
		str[x] = str[x + 1];
		x++ ;
	}
}

void replace_chars(char *str, char *quot)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && quot[i] == '0')
			str[i] = 1;
		if (str[i] == '$' && quot[i] < '2')
			str[i] = 2;
		i++;
	}
}

char	*quote_string(char *str, int *ec)
{
	int		i;
	int		x;
	char	*quot;

	i = 0;
	x = 0;
	quot = malloc(sizeof(char) * (strlen(str) + 1));
	while(str[i])
	{
		if (str[i] == 34) // "
		{
			remove_char(str, i);
			while (str[i] && str[i] != 34)
			{
				quot[x] = '2';
				x++;
				i++;
			}
			if (!str[i])
			{
				*ec = 97;
				free(quot);
				return(NULL);
			}
			remove_char(str, i);

		}
		if (str[i] == 39) // '
		{
			remove_char(str, i);
			while (str[i] && str[i] != 39)
			{
				quot[x] = '1';
				x++;
				i++;
			}
			if (!str[i])
			{
				*ec = 98;
				free(quot);
				return(NULL);
			}
			remove_char(str, i);

		}
		if (str[i] == 92) // backslash
		{
			remove_char(str, i);
			if (!str[i])
			{
				*ec = 99;
				free(quot);
				return (NULL);
			}
			quot[x] = '3';
			x++;
			i++;

		}
		else
		{
			quot[x] = '0';
			x++;
			i++;
		}

	}
	quot[x] = 0;
	replace_chars(str, quot);
	return (quot);
}
