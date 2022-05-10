/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:51:36 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/10 19:07:27 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *acc, char *buff)
{
	char	*new_acc;
	char	*p;
	size_t	size;

	if (!acc)
		return (ft_strdup(buff));
	size = ft_strlen(acc) + ft_strlen(buff);
	new_acc = (char *)malloc(size + 1);
	if (!new_acc)
		return (NULL);
	ft_memset(new_acc, 0, size + 1);
	p = new_acc;
	ft_memcpy(new_acc, acc, ft_strlen(acc) + 1);
	while (*new_acc)
		new_acc++;
	while (*buff)
		*new_acc++ = *buff++;
	free(acc);
	return (p);
}

char	*ft_wtoacc(char *acc, int fd)
{
	char	*buff;
	int		r;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	r = 1;
	while (ft_strchr(acc, '\n') == NULL && r)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[r] = '\0';
		acc = ft_strjoin(acc, buff);
	}
	free(buff);
	return (acc);
}

char	*ft_getline(char *acc)
{
	char	*line;
	int		i;

	if (!*acc)
		return (NULL);
	i = 0;
	while (acc[i] && acc[i] != '\n')
		i++;
	if (acc[i] == '\n')
	{
		line = (char *)malloc((i + 2) * sizeof(char));
		ft_memset(line, 0, i + 2);
		ft_memcpy(line, acc, i + 1);
	}
	else
	{
		line = (char *)malloc((i + 1) * sizeof(char));
		ft_memset(line, 0, i + 1);
		ft_memcpy(line, acc, i);
	}
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_setacc(char *acc)
{
	char	*p;
	int		i;
	int		j;

	if (!*acc)
	{
		free(acc);
		return (NULL);
	}
	i = 0;
	while (acc[i] && acc[i] != '\n')
		i++;
	p = (char *)malloc((ft_strlen(acc) - i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_memset(p, 0, ft_strlen(acc) - i + 1);
	j = 0;
	if (acc[i] == '\n')
		i++;
	while (acc[i])
		p[j++] = acc[i++];
	free(acc);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*acc[OPEN_MAX + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	acc[fd] = ft_wtoacc(acc[fd], fd);
	if (!acc[fd])
		return (NULL);
	line = ft_getline(acc[fd]);
	acc[fd] = ft_setacc(acc[fd]);
	return (line);
}
