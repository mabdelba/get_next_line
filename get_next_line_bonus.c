/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:10:02 by mabdelba          #+#    #+#             */
/*   Updated: 2021/11/29 13:57:03 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_first(char *str)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	tab = (char *)malloc((i + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tab[j] = str[j];
		j++;
	}
	tab[j] = '\0';
	if (tab[0] == '\0')
		return (NULL);
	return (tab);
}

char	*ft_stock_rest(char *save)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	ptr = (char *)malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (save[i])
		ptr[j++] = save[i++];
	ptr[j] = '\0';
	free(save);
	if (ptr[0] == '\0')
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

char	*ft_file(char *save, int fd)
{
	char	*buf;
	int		a;

	a = 1;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (a != 0 && ft_strchr(save) == 0)
	{
		a = read(fd, buf, BUFFER_SIZE);
		buf[a] = '\0';
		if (a == -1)
		{
			free(buf);
			return (NULL);
		}
		if (a == 0)
			break ;
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*tab[10240];
	char		*line;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	tab[fd] = ft_file(tab[fd], fd);
	if (!tab[fd])
		return (NULL);
	line = ft_first(tab[fd]);
	tab[fd] = ft_stock_rest(tab[fd]);
	return (line);
}
