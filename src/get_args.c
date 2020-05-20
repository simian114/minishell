/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:55:32 by gmoon             #+#    #+#             */
/*   Updated: 2020/05/20 12:35:01 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_count(char *command)
{
	int count;
	int quote;

	count = 0;
	quote = 0;
	while (*command)
	{
		if (quote == 0 && (*command == '\'' || *command == '\"'))
			quote += *command;
		else if (quote != 0 && *command == quote)
			quote -= *command;
		if (quote == 0 &&
			(*command != ' ' && *command != '>' && *command != '|' && *command != '<') &&
			(*(command + 1) == ' ' || !*(command + 1) ||
			*(command + 1) == '>' || *(command + 1) == '|' || *(command + 1) == '<'))
			count++;
		else if (quote == 0 && *command == '>')
		{
			count++;
			while (*command == '>')
				command++;
			command--;
		}
		else if (quote == 0 && *command == '|')
		{
			count++;
			while (*command == '|')
				command++;
			command--;
		}
		else if (quote == 0 && *command == '<')
		{
			count++;
			while (*command == '<')
				command++;
			command--;
		}
		command++;
	}
	return (count);
}

static int	key_len(char *str)
{
	int len;

	len = 0;
	while (*str &&
		!(*str == ' ' || *str == '\'' || *str == '\"' || *str == '<' || *str == '>'))
	{
		str++;
		len++;
	}
	return (len);
}

static char	*convert_arg_1_1(char **command, char **ret)
{
	int		len;

	len = 0;
	while (*(*command + len) == '>')
		len++;
	free(*ret);
	if (len < 3)
		*ret = char_to_str(len * -1);
	else
	{
		ft_putstr_fd("\033[3m\033[31mPINE_APPLE:\033[0m ", 2);
		ft_putstr_fd("parse error near `>'", 2);
		return (0);
	}
	*command += len;
	return (*ret);
}

static char	*convert_arg_1_2(char **command, char **ret)
{
	int		len;

	len = 0;
	while (*(*command + len) == '<')
		len++;
	free(*ret);
	if (len == 1)
		*ret = char_to_str(-3);
	else
	{
		ft_putstr_fd("error in <.\n", 2);
		return (0);
	}
	*command += len;
	return (*ret);
}

static char	*convert_arg_1_3(char **command, char **ret)
{
	int		len;

	len = 0;
	while (*(*command + len) == '|')
		len++;
	free(*ret);
	if (len == 1)
		*ret = char_to_str(-4);
	else
	{
		ft_putstr_fd("error in |.\n", 2);
		return (0);
	}
	*command += len;
	return (*ret);
}

static char	*convert_arg_1(char **command, char **ret, int *quote)
{
	if (*quote == 0 && **command == '>')
		return (convert_arg_1_1(command, ret));
	else if (*quote == 0 && **command == '<')
		return (convert_arg_1_2(command, ret));
	else if (*quote == 0 && **command == '|')
		return (convert_arg_1_3(command, ret));
	return (*ret);
}

static char **convert_arg_2(char **command, t_list *envs, int *quote, char **ret)
{
	char	*key;

	if (*quote == 0 && (**command == '\'' || **command == '\"'))
		*quote += **command;
	else if (*quote != 0 && **command == *quote)
		*quote -= **command;
	else if (*quote != '\'' && **command == '$') // 이부분
	{
		(*command)++;
		key = ft_substr(*command, 0, key_len(*command));
		*ret = ft_strjoin_s1free(*ret, find_value(envs, key));
		*command += ft_strlen(key) - 1;
	}
	else
		*ret = ft_strjoin_free(*ret, char_to_str(**command));
	(*command)++;
	return (command);
}

static char	*convert_arg(char **command, t_list *envs)
{
	char *ret;
	int quote;

	quote = 0;
	ret = ft_strdup("");
	while (**command)
	{
		if (quote == 0 && (**command == '>' || ** command == '<' || **command == '|'))
		{
			ret = convert_arg_1(command, &ret, &quote);
			return (ret);
		}
		command = convert_arg_2(command, envs, &quote, &ret);
		if (quote == 0 && (**command == ' ' || **command == '>'
			|| **command == '|' || **command == '<'))
			break;
	}
	return (ret);
}

char **get_args(char *command, t_list *envs)
{
	int count;
	char **args;
	int i;

	count = args_count(command);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	args[count] = 0;
	i = -1;
	while (++i < count)
	{
		while (*command == ' ' && *command)
			command++;
		args[i] = convert_arg(&command, envs);
	}
	return (args);
}
