#include "minishell.h"

int	filename_len(char *cmd)
{
	int len;

	len = 0;
	while (ft_strchr("<>|;\\\"\' \0", cmd[len]) == NULL) // add non-allowed chars
		len++;
	return (len);
}

// returns the last "<" or "<<" + filename/delimiter
char	**extract_filein(char *cmd)
{
	char	**file_info;

	if (ft_strchr(cmd, '<') == NULL)
		return (NULL);
	file_info = malloc(2 * sizeof(char*));
	while (*cmd)
	{
		if (*cmd == '<')
		{
			cmd++;
			if (*cmd == '<')
			{
				file_info[1] = ft_strdup("<<");
				cmd++;
			}
			else
				file_info[1] = ft_strdup("<");
			if (*cmd == ' ')
				cmd++;
			file_info[0] = ft_substr(cmd, 0, filename_len(cmd));
		}
		cmd++;
	}
	return (file_info);
}

// returns the last ">" or ">>" + filename
char	**extract_fileout(char *cmd)
{
	char	**file_info;

	if (ft_strchr(cmd, '>') == NULL)
		return (NULL);
	file_info = malloc(2 * sizeof(char*));
	while (*cmd)
	{
		if (*cmd == '>')
		{
			cmd++;
			if (*cmd == '>')
			{
				file_info[1] = ft_strdup(">>");
				cmd++;
			}
			else
				file_info[1] = ft_strdup(">");
			if (*cmd == ' ')
				cmd++;
			file_info[0] = ft_substr(cmd, 0, filename_len(cmd));
		}
		cmd++;
	}
	return (file_info);
}
