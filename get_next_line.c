/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:19:42 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/15 17:34:39 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//track null terminator
// if (!stash[0]) // to return null when you
//try to read file with just newline without character
// stash = malloc(0); //check the reliability
char	*get_myline(int fd, char *stash)
{
	int		bytes_read;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buff, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), free(stash), NULL);
		else if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		if (!stash)
			stash = malloc(0);
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*return_myline(char *stash)
{
	char	*line;
	size_t	i;

	if (!stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
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

char	*after_next_line(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > 4294967295)
		return (NULL);
	stash = get_myline(fd, stash);
	if (!stash)
		return (NULL);
	line = return_myline(stash);
	if (!line)
	{
		stash = line;
		return (stash);
	}
	stash = after_next_line(stash);
	return (line);
}
/*
int main(void)
{
    char *line;
    int fd;
	int x = 3;

    // Test 1: Valid file with multiple lines
    printf("Test 1: Reading from a valid file (sample.txt)\n");
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening sample.txt");
        return (1);
    }

    int line_number = 1;
    while (x > 0)
    {
		line = get_next_line(fd);
        printf("Line %d: %s", line_number++, line);
		x--;
	}
    close(fd);
	return (1);
}
*/
