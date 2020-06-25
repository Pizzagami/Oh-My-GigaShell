#include "libft.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while(s && s[i])
		i++;
	write(1, s, i);
}
