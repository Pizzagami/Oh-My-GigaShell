/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_random_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braimbau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:12:31 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/08 13:15:09 by braimbau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		dereplace_stars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == CSTAR)
			str[i] = '*';
		i++;
	}
}

int			is_dir(char *path, char *file)
{
	struct stat buf;

	path = ft_strjoin_sep(path, file, '/');
	stat(path, &buf);
	free(path);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void		removedoublestars(char **str_p)
{
	char	*str;
	int		x;

	str = *str_p;
	x = 0;
	while (str && str[x] && str[x + 1])
	{
		if (str[x] == CSTAR && str[x + 1] == CSTAR)
			removechar(str_p, x + 1);
		else
			x++;
	}
}

int			numberstars(char *str)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (str && str[x])
	{
			if (str[x] == CSTAR)
			y++;
		x++;
	}
	return (y);
}

t_mx		init_mx(int p, int s)
{
	t_mx	x;

	x.s = s;
	x.p = p;
	return (x);
}
