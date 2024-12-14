/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:14:45 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/14 15:48:57 by hceviz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

//check the effect of static in function
//buff[read_bytes] is for providing an end in strjoin while loop
//otherwise there will not be any null terminator so strjoin will iterate infinitively
//and also in some cases read() might read bytes less than buffer size
//so buff[read_bytes] ensures that only the valid portion of the buffer is treated as a string
//and in every while loop we check !strchr(buff, '\n') so if we dont null termianate buff,
//strchr will iterate it infinitively
static char	*get_myline(int fd, char *stash)
{
	int		read_bytes;
	char	*buff;

	read_bytes = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(buff, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(stash);
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*return_myline(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash[0])
		return (NULL);
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


char	*after_new_line(char *stash)
{
	char	*after;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	after = malloc(ft_strlen(stash) - i);
	if (!after)
		return (NULL);
	if (stash[i] == '\n')
		i++;
	j = 0;
	while (stash[i + j])
	{
		after[j] = stash[i + j];
		j++;
	}
	//after[j] = '\0';
	return (after);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_myline(fd, stash);
	if (!stash)
		return (NULL);
	line = return_myline(stash);
	stash = after_new_line(stash);
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
}*/
