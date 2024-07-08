/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_commands_syntax.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:16:01 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/29 13:12:05 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unbuilt_cd_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : cd\n");
	if (array[i] && str_search_str(array[i], "|><") == 0)
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	if (array[i] && str_search_str(array[i], "|><") == 0)
		return (printf_error(ERR_CD_ARGS), -1);
	return (words_handled - 1);
}

int	unbuilt_pwd_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : pwd\n");
	while (array[i] && str_search_str(array[i], "|><") == 0)
	{
		words_handled++;
		i++;
	}
	return (words_handled - 1);
}

int	unbuilt_env_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : env\n");
	if (array[i] && str_search_str(array[i], "|><") == 0)
		return (printf_error(ERR_ENV_ARGS), -1);
	return (words_handled - 1);
}

int	unbuilt_echo_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : echo\n");
	if (array[i] && ft_strncmp(array[i], "-n", 2) == 0)
	{
		printf("Option \"-n\" has been set!\n");
		words_handled++;
		i++;
	}
	while (array[i] && ft_strncmp(array[i], "-n", 2) == 0)
	{
		printf("Argument that MUST BE IGNORED : \"-n\" !\n");
		words_handled++;
		i++;
	}
	while (array[i] && str_search_str(array[i], "|><") == 0)
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	return (words_handled - 1);
}

int	unbuilt_exit_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : exit\n");
	if (array[i] && str_search_str(array[i], "|><") == 0)
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	if (array[i] && str_search_str(array[i], "|><") == 0)
		return (printf_error(ERR_EXIT_ARGS), -1);
	return (words_handled - 1);
}

int	unbuilt_unset_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : unset\n");
	while (array[i] && str_search_str(array[i], "|><") == 0)
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	return (words_handled - 1);
}

int	unbuilt_export_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : export\n");
	while (array[i] && str_search_str(array[i], "|><") == 0)
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	return (words_handled - 1);
}
