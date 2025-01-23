/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:22:02 by egibeaux          #+#    #+#             */
/*   Updated: 2025/01/20 12:54:39 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_join(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*ft_cpyline(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i] || !str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_leftover(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	s = malloc (sizeof(char) * (ft_strlen(str) - i) + 1);
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (str[i + j])
	{
		s[j] = str[i + j];
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

char	*ft_get_line(int fd, char *str)
{
	char	*buffer;
	int		bytes;

	if (!str)
		str = malloc(1);
	bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes] = '\0';
		str = ft_join(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_line(fd, buffer);
	if (!buffer)
		return (free(buffer), NULL);
	line = ft_cpyline(buffer);
	buffer = ft_get_leftover(buffer);
	if (!buffer && !line)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
/*
int	main()

{
 	int	fd;
 	int	i;

 	i = 16;
	
 	fd = open("test.txt", O_RDONLY);
 	if (fd == -1)
 		return (-1);
 	char	*line;

 	line = get_next_line(fd);
 	while (line && i)
 	{
 		printf("%s", line);
 		free(line);
 		line = get_next_line(fd);
 		i--;
 	}
 	free(line);

 	close(fd);
}
*/
