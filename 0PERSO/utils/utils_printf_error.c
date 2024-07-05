/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:08:47 by lahlsweh          #+#    #+#             */
/*   Updated: 2024/07/05 13:17:24 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_error(int status)
{
	if (status == ERR_PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (status == ERR_REDIR_OUT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (status == ERR_REDIR_IN)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (status == ERR_APPEND_REDIR_OUT)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (status == ERR_HERE_DOC)
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (status == ERR_NEWLINE)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (status == ERR_CD_ARGS)
		printf("bash: cd: too many arguments\n");
	else if (status == ERR_ENV_ARGS)
		printf("bash: env: too many arguments\n");
	else if (status == ERR_EXIT_ARGS)
		printf("bash: exit: too many arguments\n");
	return ;
}
