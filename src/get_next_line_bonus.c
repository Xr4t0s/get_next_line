/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nitadros <nitadros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:47:32 by nitadros          #+#    #+#             */
/*   Updated: 2024/12/10 22:24:46 by nitadros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

char	*get_good_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc(sizeof(char), (ft_strlen(buffer) - i + 1));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*free_buff(char *ret, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(ret, buffer);
	free(ret);
	return (tmp);
}

char	*get_good_line(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	ret = ft_calloc(sizeof(char), (i + 2));
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] && line[i] == '\n')
		ret[i++] = '\n';
	return (ret);
}

char	*read_lines(int fd, char *buffer)
{
	char	*ret;
	int		bytes_read;

	if (!buffer)
		buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	ret = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, ret, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(ret), NULL);
		ret[bytes_read] = 0;
		buffer = free_buff(buffer, ret);
		if (ft_strchr(ret, '\n'))
			break ;
	}
	free(ret);
	if (!buffer)
		return (NULL);
	if (!buffer[0])
		return (free(buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buffer[fd] = read_lines(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_good_line(buffer[fd]);
	buffer[fd] = get_good_next(buffer[fd]);
	return (line);
}

/* int main()
{
	int fd;
	fd = open("get_next_line.h", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	int fd2 = open("get_next_line_utils.c", O_RDONLY);
	char *line2 = get_next_line(fd2);
	printf("%s", line2);
	if (line2)
		free(line2);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
} */
