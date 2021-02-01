#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	is_nl(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	index_nl(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*res = NULL;
	int		i = 0;

	if (!(res = (char*)malloc(sizeof(char) * (ft_strlen(res) + 1))))
		return (NULL);
	if (str[0] == '\0')
	{
		res[0] = '\0';
		return (res);
	}
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	int		nb = ft_strlen(s1) + ft_strlen(s2) + 1;
	char	*res = NULL;

	if (!s1 && !s2)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * nb)))
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char *str, int begin, int size)
{
	int		i = 0;
	char		*res = NULL;

	if (size <= 0 || begin < 0 || !str)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (str[begin] != '\0' && size)
	{
		res[i] = str[begin];
		i++;
		begin++;
		size--;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_cut_begin(char *str)
{
	int		i = 0;
	int		j = 0;
	char	*res = NULL;

	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	i++;
	if (!(res = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
	{
		res[j] = str[j];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char	*res = NULL;
	char		*tmp = NULL;
	char		str[33];
	int			ret = 0;
	
	if (!line)
		return (-1);
	while (!is_nl(res) && (ret = read(fd, str, 32)))
	{
		if (ret == -1)
			return (-1);
		str[ret] = '\0';
		tmp = res;
		res = ft_strjoin(res, str);
		free(tmp);
	}
	if (res)
	{
		if (is_nl(res))
		{
			*line = ft_cut_begin(res);
			tmp = res;
			res = ft_substr(res, index_nl(res) + 1, ft_strlen(res) - index_nl(res) - 1);
			free(tmp);
		}
		else
		{
			*line = ft_strdup(res);
			free(res);
			return (0);
		}
	}
	else
	{
		*line = ft_strdup("");
		return (0);
	}
	return (1);
}

int		main(void)
{
	int		ret = 0;
	char	*line = NULL;
	int		i = 0;

	int		fd = open("tim", O_RDWR);
	while (i < 10)
	{
		ret = get_next_line(fd, &line);
		printf("ret = [%d] : {%s}\n", ret, line);
		free(line);
		i++;
	}
	while (1);
	return (0);
}
