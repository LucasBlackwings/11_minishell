/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:34:36 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/06/14 12:35:55 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_prompt(char *user_env, char *session_manager_env, char *pwd_env)
{
	int		user_env_len;
	int		session_manager_env_len;
	int		pwd_env_len;
	int		prompt_len;
	int		i;
	int		j;
	char	*prompt;

	user_env_len = 0;
	session_manager_env_len = 0;
	pwd_env_len = 0;
	while (user_env[user_env_len])
		user_env_len++;
	while (*session_manager_env != '/')
		session_manager_env++;
	session_manager_env++;
	while (session_manager_env[session_manager_env_len] != '.')
		session_manager_env_len++;
	session_manager_env[session_manager_env_len] = '\0';
	while (pwd_env[pwd_env_len])
		pwd_env_len++;
	prompt_len = user_env_len + session_manager_env_len + pwd_env_len + 5;
	prompt = (char *)malloc(prompt_len * sizeof(char));
	i = 0;
	j = 0;
	while (user_env[j])
	{
		prompt[i] = user_env[j];
		i++;
		j++;
	}
	prompt[i] = '@';
	i++;
	j = 0;
	while (session_manager_env[j])
	{
		prompt[i] = session_manager_env[j];
		i++;
		j++;
	}
	prompt[i] = ':';
	i++;
	j = 0;
	while (pwd_env[j])
	{
		prompt[i] = pwd_env[j];
		i++;
		j++;
	}
	prompt[i] = '$';
	prompt[i + 1] = ' ';
	prompt[i + 2] = '\0';
	return (prompt);
}
