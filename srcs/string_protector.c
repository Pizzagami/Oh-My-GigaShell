#include <libc.h>

void delete_char(char *str, int index)
{
	int i;

	i = 0;
	while (i < index)
		i++;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

char *quote_string(char *str)
{
	int i;
	int x;
	char *quot;

	x = 0;
	i = 0;
	quot = malloc(sizeof(char) * strlen(str));
	while (str[i])
	{
		if (str[i] == '\"')
		{
			delete_char(str, i);
			while(str[i] != '\"')
			{
				quot[x] = '1';
				x++;
				i++;
			}
			delete_char(str, i);

		}
		if (str[i] == '\'')
		{
			delete_char(str, i);
			while(str[i] != '\'')
			{
				quot[x] = '2';
				x++;
				i++;
			}
			delete_char(str, i);
		}
		if (str[i] == '\\')
		{
			delete_char(str, i);
			quot[x] = '3';
			x++;
			i++;
		}
	}
	return (quot);
}

int main()
{
	char *str = "test";
	printf("%s\n", str);
	char *quot = quote_string(str);
	printf("%s | %s\n", str, quot);
}
