/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:25:04 by braimbau          #+#    #+#             */
/*   Updated: 2021/01/26 16:34:00 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	check_errors(struct termios *config, int fd)
{
	if (cfsetispeed(config, B9600) < 0 || cfsetospeed(config, B9600) < 0)
	{
		ft_putstr("communication speed error\n");
		exit(0);
	}
	if (tcsetattr(fd, TCSADRAIN, config) < 0)
	{
		ft_putstr("error applying configuration\n");
		exit(0);
	}
}

void	term_init(struct termios *save_cano, struct termios *save_nncano)
{
	struct termios	config;
	int				fd;

	tcgetattr(0, &(*save_cano));
	fd = 0;
	if (tcgetattr(fd, &config) < 0)
	{
		ft_putstr("config termios failure \n");
		exit(0);
	}
	config.c_iflag &= ~(IXON);
	config.c_lflag &= ~(ECHO | ICANON | ISIG);
	config.c_cflag &= 0;
	config.c_cflag |= CS8;
	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;
	check_errors(&config, fd);
	tcgetattr(0, &(*save_nncano));
	return ;
}
