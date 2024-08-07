/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:34:36 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/08 14:49:45 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*build_prompt_control(void)
{
	char	*user_env;
	char	*pwd_env;
	char	*session_manager_env;
	char	*prompt;
	int		prompt_len;

	user_env = getenv("USER");
	pwd_env = getenv("PWD");
	if (!user_env || !pwd_env)
		return (NULL);
	pwd_env = trim_pwd_env_if_home_user(user_env, pwd_env);
	session_manager_env = trim_session_manager_env();
	if (!session_manager_env)
		return (NULL);
	prompt_len = count_prompt_len(user_env, session_manager_env, pwd_env);
	prompt = build_prompt(user_env, session_manager_env, pwd_env, prompt_len);
	if (!prompt)
		return (NULL);
	return (prompt);
}

char	*trim_pwd_env_if_home_user(char *user_env, char *pwd_env)
{
	int	user_env_len;
	int	i;

	if (ft_strncmp(pwd_env, "/home/", 6) == 0)
	{
		user_env_len = 0;
		while (user_env[user_env_len])
			user_env_len++;
		i = 6;
		while (i - 6 < user_env_len && pwd_env[i] == user_env[i - 6])
			i++;
		if (user_env[i - 6] == '\0')
		{
			pwd_env += i - 1;
			pwd_env[0] = '~';
		}
	}
	return (pwd_env);
}

char	*trim_session_manager_env(void)
{
	char	*session_manager_env;
	int		i;

	i = 0;
	session_manager_env = getenv("SESSION_MANAGER");
	if (!session_manager_env)
		return (NULL);
	while (*session_manager_env != '/')
		session_manager_env++;
	session_manager_env++;
	while (session_manager_env[i] != '.')
		i++;
	session_manager_env[i] = '\0';
	return (session_manager_env);
}

int	count_prompt_len(char *user_env, char *session_manager_env, char *pwd_env)
{
	int		user_env_len;
	int		session_manager_env_len;
	int		pwd_env_len;
	int		prompt_len;

	user_env_len = 0;
	session_manager_env_len = 0;
	pwd_env_len = 0;
	prompt_len = 0;
	while (user_env[user_env_len])
		user_env_len++;
	while (session_manager_env[session_manager_env_len])
		session_manager_env_len++;
	while (pwd_env[pwd_env_len])
		pwd_env_len++;
	prompt_len = user_env_len + session_manager_env_len + pwd_env_len + 5;
	return (prompt_len);
}

char	*build_prompt(char *user_env, char *session_manager_env, char *pwd_env, int prompt_len)
{
	char	*prompt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	prompt = (char *)malloc(prompt_len * sizeof(char));
	if (!prompt)
		return (NULL);
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
