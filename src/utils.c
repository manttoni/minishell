#include "minishell.h"

char  *skip_spaces(char *s)
{
	while (ft_isspace(*s))
			s++;
	return (s);
}

char    **copy_array(char **ar)
{
        char    **env;
        int             i;

        env = malloc((len(ar) + 1) * sizeof(char *));
        if (env == NULL)
                return (NULL);
        i = 0;
        while (ar[i])
        {
                env[i] = ft_strdup(ar[i]);
                i++;
        }
        env[i] = NULL;
        return (env);
}

int unclosed_quotes(char *s)
{
	int	i;
	char	c;

	i = 0;
	while(*s)
	{	
		c = 0;
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			while (*s)
			{
				if (*s == c)
				{
					c = 0;
					break;
				}
				s++;
			}
			if (c)
				return (1);
		}
		s++;
	}
	return (0);
}

int	print_error(char *s, int n)
{
	if (n == 1)
		ft_printf("-minishell: %s: %s\n", s, strerror(errno));
	else if (n == 0)
		ft_printf("-minishell: %s\n", s);
	return (1);
}
