#include "minishell.h"

int	filename_len(char *cmd)
{
	int len;

	len = 0;
	while (ft_strchr("<>|;\\\"\' \0", cmd[len]) == NULL) // add non-allowed chars
		len++;
	return (len);
}

/*char dir is << or >> */
char	**get_fileinfo(char *cmd, char *dir)
{
	char	**file_info;

	if (ft_strchr(cmd, *dir) == NULL)
		return (NULL);
	file_info = malloc(2 * sizeof(char *));
	memset(file_info, 0, 2 * sizeof(char *));
	while (*cmd)
	{
		if (*cmd == *dir) // one dir char
		{
			cmd++;
			free(file_info[1]);
			if (*cmd == *dir) // two dir chars
			{
				file_info[1] = ft_strdup(dir);
				cmd++;
			}
			else
				file_info[1] = ft_substr(dir, 0, 1);
			if (*cmd == ' ')
				cmd++;
			if (filename_len(cmd) > 0)
				file_info[0] = ft_substr(cmd, 0, filename_len(cmd));
			else
			{
				printf("Syntax error\n");
				return (NULL);
			}
		}
		cmd++;
	}
	return (file_info);
}
/*
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
}*/
