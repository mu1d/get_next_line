/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:34:55 by maldahma          #+#    #+#             */
/*   Updated: 2022/02/24 11:23:00 by maldahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_static(int fd)
{
	static char	str[2];
	int			length;
	int			i;

	length = 2;
	i = 0;
	while (i < length)
	{
		read(fd, &str[i], 1);
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char	*output = malloc(6);
	int		length;
	int		i;

	length = 6;
	i = 0;
	//read(fd, &output[0], 1);
	while (i < length)
	{
		read(fd, &output[i], 1);
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	main(void)
{
	FILE	*file1;
	char	c;

	file1 = fopen("file.txt", "r");
	printf("%s", get_static(3));
	//read(3, &c, 1);
	//printf("%c", c);
	fclose(file1);
	return (0);
}
