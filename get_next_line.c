/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 06:58:29 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/16 13:00:18 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//check bytes_read > 0 side
//line 80 is checking if it is ended cuz of \0 or \n
// it is tricky cuz if it is \n it iterates 1 more to 
// reach after newline
// used int deliberately for i's and j's because 
//BUFFER_SIZE has int type by default

char	*fill_buffer(int fd, char *stash)
{
	int		bytes_read;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(stash), NULL);
		buff[bytes_read] = '\0';
		stash = ft_strjoin(stash, buff);
		if (!stash)
			return (NULL);
	}
	free(buff);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i]) // stash[i]
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*after_newline(char *stash)
{
	char	*after;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!stash[0])
		return (NULL);
	/*if (!ft_strchr(stash, '\n'))
		return (free(stash), NULL);*/
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i])
		i++;
	after = malloc(ft_strlen(stash) - i + 1);
	if (!after)
		return (NULL);
	if (stash[i] == '\n')
		i++;
	while (stash[i])
		after[j++] = stash[i++];
	after[j] = '\0';
	free(stash);
	stash = NULL;
	return (after);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	stash = fill_buffer(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = after_newline(stash);
	return (line);
}
