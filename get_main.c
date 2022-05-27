/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:36:12 by maldahma          #+#    #+#             */
/*   Updated: 2022/05/26 11:38:02 by maldahma             ###   ########.ae       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void			*allo;
	int				len;
	char unsigned	*temp;

	allo = malloc(count * size);
	if (!allo)
		return (NULL);
	len = count * size;
	temp = (unsigned char *)allo;
	while (len > 0)
	{
		temp[len] = '\0';
		len--;
	}
	return (temp);
}

void	fill_str(char const *s, unsigned int start, size_t len, char *sub)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = 0;
	while (s[slen])
		slen++;
	if (start > slen)
		sub[0] = '\0';
	else
	{
		while (i < len && s[start + i] != 0)
		{
			sub[i] = s[start + i];
			i++;
		}
		sub[i] = '\0';
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub;

	i = 0;
	slen = 0;
	if (!s)
		return (NULL);
	while (s[slen])
		slen++;
	if (slen < len)
		sub = ft_calloc((slen + 1), sizeof(char));
	else
		sub = ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	fill_str(s, start, len, sub);
	return (sub);
}

int	str_length(char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

//joins 2 strings and frees input varaiblei's allocated memory
char	*join_str(char *a, char *b)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ((sizeof(a) * str_length(a)) + (sizeof(b) * str_length(b)));
	str = malloc((sizeof(a) * str_length(a)) + (sizeof(b) * str_length(b)) + 1);
	if (!str)
		return (NULL);
	while (i < j)
		str[i++] = '\0';
	i = 0;
	if (!str)
		return (str);
	j = 0;
	while (i < str_length(a))
		str[i++] = a[j++];
	j = 0;
	while (i < (str_length(a) + str_length(b)))
		str[i++] = b[j++];
	str[i] = '\0';
	free(a);
	free(b);
	return (str);
}

char	*fill_static(char *str, int length)
{
	static char	clone[(100 + 1)];
	int			i;

	i = 0;
	while (i < length)
	{
		clone[i] = str[i];
		i++;
	}
	clone[i] = '\0';
	free(str);
	return (clone);
}

char	*init(char static *grandparent, char *parent, int i)
{
if (grandparent)
		parent = grandparent;
	else
	{
		parent = malloc(sizeof(char) * 1);
		if (!parent)
			return (NULL);
		parent[0] = '\0';
	}
	if (parent)
	{
		while (i < str_length(parent))
		{
			if (parent[i] == '\n')
			{
				grandparent = ft_substr(parent, i + 1, str_length(parent));
				temp = ft_substr(parent, 0, i + 1);
				if ((!temp) || (!grandparent))
					return (NULL);
				return (temp);
			}
			i++;
		}
	}
}

char	*get_next_line(int fd)
{
	char static	*grandparent;
	char		*parent;
	char		*child;
	char		*temp;
	int			i;

	i = 0;

/*	if (grandparent)
		parent = grandparent;
	else
	{
		parent = malloc(sizeof(char) * 1);
		if (!parent)
			return (NULL);
		parent[0] = '\0';
	}
	if (parent)
	{
		while (i < str_length(parent))
		{
			if (parent[i] == '\n')
			{
				grandparent = ft_substr(parent, i + 1, str_length(parent));
				temp = ft_substr(parent, 0, i + 1);
				if ((!temp) || (!grandparent))
					return (NULL);
				return (temp);
			}
			i++;
		}
	}*/
	i = 0;
	while (i != -1)
	{
		child = malloc(sizeof(char) * BUFFER_SIZE);
		if (!child)
			return (NULL);
		while (i < BUFFER_SIZE)
			child[i++] = '\0';
		child[i] = '\0';
		i = 0;
		read(fd, child, BUFFER_SIZE);
		while (i < str_length(child))
		{	
			if (child[i] == '\n')
			{
			/*	return (find_end_of_line(grandparent, parent, child, temp, i));*/
				if (!(i == str_length(child) - 1))
				{
					grandparent = ft_substr(child, i + 1, str_length(child));
					if (!grandparent)
						return (NULL);
					temp = join_str(parent, ft_substr(child, 0, i + 1));
				}
				else
				{
					temp = join_str(parent, child);
				}
				if (!temp)
					return (NULL);
				else
				{
					return (fill_static(temp, str_length(temp)));
				}
			}
			i++;
		}	
		if (!(i == str_length(child) - 1))
		{
			grandparent = ft_substr(child, i + 1, str_length(child));
			if (!grandparent)
				return (NULL);
			temp = join_str(parent, ft_substr(child, 0, i + 1));
			if (!temp)
				return (NULL);
		}
		else
		{
			temp = join_str(parent, child);
			if (!temp)
				return (NULL);
			return (fill_static(temp, str_length(temp)));
		}
		if (!temp)
			return (NULL);
		parent = temp;
		i = 0;
	}
	return (NULL);
}

int	main(void)
{
	FILE	*file1;
	//char	c;
	//char	b;
	char	*d;
	int		i;
	i = 0;
	file1 = fopen("file.txt", "r");
	d = get_next_line(3);
	printf("%s", d);
	d = get_next_line(3);
	printf("%s", d);
	d = get_next_line(3);
	printf("%s", d);
	d = get_next_line(3);
	printf("%s", d);
	/*while(i < 40)
	{
		read(3, &c, 1);
		if (c == '\n' && b == '\n')
			i = 40;
		else
		{
			b = c;
			printf("%c", c);
		}
		i++;
	}*/
	fclose(file1);
	return (0);
}
