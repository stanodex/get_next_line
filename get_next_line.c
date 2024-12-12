/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:41:59 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/12 17:48:06 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*getbuffer(int fd)
{
	//control the cursor location
	char	*buff;
	int		read_bytes;

	read_bytes = read(fd, buff, BUFFER_SIZE);
	if (bytes ) // check read return condition


}


char	*get_next_line(int fd)
{
	static char	*stash;
}