#include "libft.h"

static int		depend_mask(char c, const char *mask)
{
	while(*mask)
	{
		if (c == *mask)
			return (1);
		mask++;
	}
	return (0);
}

static int		split_len(const char *str, const char *mask)
{
	int		i;

	i = 0;
	while (str[i] && !depend_mask(str[i], mask))
		i++;
	return (++i);
}

static int		recursive_count(const char *str, const char *mask)
{
	if (depend_mask(*str, mask))
		return (recursive_count(++str, mask));
	if (*str)
	{
		while (!depend_mask(*str, mask) && *str)
			str++;
		return (1 + recursive_count(str, mask));
	}
	else
		return (0);
}

static int		recursive_split(char **dst, const char *str,
	const char *mask)
{
	char	*res;
	int		i;

	if (depend_mask(*str, mask))
		return (recursive_split(dst, ++str, mask));
	if (*str)
	{
		if (!(res = (char *)malloc(sizeof(char) * split_len(str, mask))))
			return (0);
		i = 0;
		while (*str && !depend_mask(*str, mask))
		{
			res[i] = *str;
			i++;
			str++;
		}
		res[i] = '\0';
		*dst = res;
		return (recursive_split(++dst, str, mask));
	}
	*dst = NULL;
	return (1);
}

char			**ft_strsplitm(const char *s, const char *mask)
{
	int		len;
	char	**res;

	if (!s || !mask)
		return (NULL);
	len = recursive_count(s, mask);
	if ((res = (char **)malloc(sizeof(char *) * (len + 1))))
		if (!recursive_split(res, s, mask))
			ft_arrfree(&res);
	return (res);
}
