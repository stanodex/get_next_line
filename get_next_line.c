/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:14:45 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/13 19:56:58 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

//check the effect of static in function
static char	*read_data(int fd, char *buff, char *stash)
{
	int		read_bytes;

	read_bytes = 1;
	while (!has_newline(buff) && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		else if (read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		stash = ft_strjoin(stash, buff);
	}
	return (stash);
}

char	*extract(char **stash_ptr)
{
	int		i;
	char	*line;
	char	*stash;
	char	*temp;

	i = 0;
	stash = *stash_ptr;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
	{
		line = ft_substr(stash, 0, i + 1);
		line[i] = '\0';
		temp = ft_strdup(stash + i + 1);
		free(*stash_ptr);
		*stash_ptr = temp;
		free(temp);
	}
	else
	{
		line = ft_strdup(stash);
		free(stash);
		free(*stash_ptr);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	stash = read_data(fd, buff, stash);
	free(buff);
	res = ft_strdup(extract(&stash));
	return (res);
}

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
	line = get_next_line(fd);
    while (x > 0)
    {
        printf("Line %d: %s", line_number++, line);
		x--;
	}
    close(fd);
	return (1);
}
