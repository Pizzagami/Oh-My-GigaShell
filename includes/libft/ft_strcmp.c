int	ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
		return((unsigned char)s1[i] - s2[i]);
	return (0);
}
