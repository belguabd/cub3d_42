/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:12:08 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 14:14:37 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*string;

	len = ft_strlen(s1);
	string = (char *)ft_malloc((len + 1) * sizeof(char), ALLOC);
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!line && !buffer)
		return (NULL);
	string = ft_malloc((ft_strlen(line) + ft_strlen(buffer)) + 1, ALLOC);
	if (!string)
		return (line = NULL, NULL);
	i = 0;
	while (line[i])
	{
		string[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (line = NULL, string);
}
