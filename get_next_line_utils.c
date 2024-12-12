/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:04:09 by hceviz            #+#    #+#             */
/*   Updated: 2024/12/12 22:47:55 by hceviz           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

int	has_newline(char *to_search)
{
	int	i;

	i = 0;
	while (to_search[i])
	{
		if (to_search[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*arr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	arr = (char *)malloc(len + 1);
	if (arr == NULL)
		return (NULL);
	while (i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	q;

	if (!s1 || !s2)
		return (NULL);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	q = 0;
	while (s2[q])
	{
		res[i + q] = s2[q];
		q++;
	}
	res[i + q] = '\0';
	return (res);
}
