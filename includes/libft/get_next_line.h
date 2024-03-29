/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:04:49 by selgrabl          #+#    #+#             */
/*   Updated: 2021/01/28 10:46:32 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

int		get_next_line(int fd, char **line, char c);
char	*ft_strcpy(char *dest, char *src);
void	join(char **line, char **buf, int x);
int		increase_buf(char **buf);
int		clear_buff(int x, int fd, char ***buf);

#endif
