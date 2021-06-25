/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylazrek <ylazrek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:48:08 by ylazrek           #+#    #+#             */
/*   Updated: 2021/05/31 19:53:43 by ylazrek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line(char **str, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *str;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	*line = ft_substr(tmp, 0, i);
	if (!tmp[i])
	{
		*str = NULL;
		free(tmp);
		return (0);
	}
	*str = ft_strdup(&tmp[i + 1]);
	free(tmp);
	if (!*line || !*str)
		return (-1);
	if (*str != NULL)
		return (1);
	return (-1);
}

int	cas_null(char **str)
{
	if (!*str)
	{
		*str = ft_strdup("\0");
		if (!*str)
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[265];
	char		*buffer;
	int			ret;
	char		*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || fd > 256 || !line || BUFFER_SIZE <= 0
		|| !(buffer) || read(fd, buffer, 0) == -1)
		return (-1);
	if (cas_null(&str[fd]) == -1)
		return (-1);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret)
	{
		buffer[ret] = '\0';
		tmp = str[fd];
		str[fd] = ft_strjoin(str[fd], buffer);
		free(tmp);
		if (index_of(str[fd], '\n') != -1)
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (get_line(&str[fd], line));
}
