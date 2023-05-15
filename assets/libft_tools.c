
#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	s1--;
	s2--;
	while (n > 0)
	{
		s1++;
		s2++;
		n--;
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		else if (*s1 == '\0')
			return (-21);
		else if (*s2 == '\0')
			return (21);
		else if (*s1 != *s2)
			return ((int)*s1 - (int)*s2);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[(i)] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	hold;
	size_t	i;

	hold = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while ((i < size - 1) && (i != hold))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (hold);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[(i)] == (unsigned char)c)
			return ((char *)&s[(i)]);
		i--;
	}
	return (NULL);
}

// **************************************************
// compares each char from the string dereferenced	*
// by find against each char from the string 		*
// dereferenced by str.								*
// Return value is char position (in find) of the	*
// similar char. else it returns -1					*
// **************************************************
int	ft_strstrchr(char *str, char *find)
{
	int	i;
	int	j;

	i = -1;
	while (find[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (find[i] == str[j])
				return (j);
		}
	}
	return (-1);
}
