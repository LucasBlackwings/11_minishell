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

#include "minishell.h"

int	unbuilt_cd_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : cd\n");
	if (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	if (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		return (printf("bash: cd: too many arguments\n\n"), -1);
	}
	return (words_handled - 1);
}

int	unbuilt_pwd_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : pwd\n");
	while (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
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
	if (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		return (printf("bash: env: too many arguments\n\n"), -1);
	}
	return (words_handled - 1);
}

int	unbuilt_echo_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : echo\n");
	if (array[i] && array[i][0] == '-' && array[i][1] == 'n' && array[i][2] == '\0')
	{
		printf("Option \"-n\" has been set!\n");
		words_handled++;
		i++;
	}
	while (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
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
	if (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	if (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		return (printf("bash: exit: too many arguments\n\n"), -1);
	}
	return (words_handled - 1);
}

int	unbuilt_unset_syntax(char **array, int i)
{
	int	words_handled;

	words_handled = 1;
	i += 1;
	printf("Inbuilt command found : unset\n");
	while (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
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
	while (array[i] && array[i][0] != '|' && array[i][0] != '>' && array[i][0] != '<')
	{
		printf("Argument found : %s\n", array[i]);
		words_handled++;
		i++;
	}
	return (words_handled - 1);
}
