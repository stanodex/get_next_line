/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:59 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/13 00:12:34 by hceviz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//in one calling buffer will decide stash
char	*create_stash(int fd, char *buff, char *stash)
{
	//control the cursor location
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1 )
			return (0);
		else if (read_bytes == 0)
			break;
		buff[read_bytes] = '\0';
		 if (!stash)
		 	stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buff); //what if i use stash = ft_strjoin(stash, buff) -> ask to gpt
		free(temp); //after free temp will not be exist
		temp = NULL; // by initializing to null it allows us to check it cuz it is exist
		if (has_newline(buff))
		{
			free(buff);
			break;
		}
	}
	//can i free buff in here cuz buff created in get_next_line
	return (stash);
}

char	*create_final(char *stash)
{
	int		i;
	char	*final;
	i = 0;
	while (stash[i] != '\n')
		i++;
	final = malloc((i * sizeof(char)) + 1);
	if (!final)
		return (NULL);
	i = 0;
	while (stash[i] != '\n')
	{
		final[i] = stash[i];
		i++;
	}
	final[i] = '\n';
	free(stash);
	return (final);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buff)
		return (0);
	if (has_newline(create_stash(fd, buff, stash)))
	{
		free(buff);
		return (stash);
	}
	res = create_final(create_stash(fd, buff, stash));
	free(buff);
	return (res);
}
