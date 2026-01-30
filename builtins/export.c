/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mada <kel-mada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:36:18 by kel-mada          #+#    #+#             */
/*   Updated: 2026/01/26 18:21:28 by kel-mada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h> 
#include <readline/history.h>
#include <fcntl.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen2(char **s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
		{
			len++;
		}
	}
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
		{
			len++;
		}
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2 [i] && (i < n - 1) && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

int	main(int ac, char *av[], char **envp)
{
	int		i;
	int		j;
	char	**temp;
	char	*tempstr = NULL;

	temp = malloc((ft_strlen2(envp) + 1) * sizeof(char **));
	i = 0;
	while (envp[i])
	{
		temp[i] = ft_strdup(envp[i]);
		i++;
	}
	temp[i] = "\0";
	i = 0;
	while (temp[i])
	{
		j = i + 1;
		while (temp[j])
		{
			if (ft_strncmp(temp[i], temp[j], ft_strlen(temp[i + 1])) > 0)
			{
				tempstr = temp[i];
				temp[i] = temp[j];
				temp[j] = tempstr;
				// free(tempstr);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (temp[i + 1])
	{
		printf("declare -x %s\n", temp[i]);
		// free(temp[i]);
		i++;
	}
	free(temp);
}
