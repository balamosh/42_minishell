/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_saver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 07:39:35 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 07:43:07 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quotes_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	int	*i_ptr;
	int	*k2;
	int	k;

	k = ft_strlen(tokens[token_n]) - 1;
	// *k2 = ft_strlen(tokens[token_n]) - 1;
	k2 = &k;
	i_ptr = &i;
	printf("\n[double_quotes_token_saver] k=%d, k2=%d\n", k, *k2);
	while (line[++i] != '\"')
	{
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"')
		{
			i = get_env_var_value_to_saver(tokens, token_n, line, i + 1, envs);
			k = ft_strlen(tokens[token_n]) - 1; ////10.09 echo "''' $USER   ''"
			i++;
			// i = get_env_var_value(line, i + 1, envs);
			// break; //10.09 echo "''' $USER   ''"
		}
		else
		{
			tokens[token_n][++k] = line[i];
			printf("%c", tokens[token_n][k]);
		}
	}
	// k = ft_strlen(tokens[token_n]) - 1; //10.09 echo "''' $USER   ''"
	tokens[token_n][++k] = '\0';
	if (line[i + 1] == '\'')
	{
		single_quote_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	if (line[i + 1] == '\"')
	{
		double_quotes_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	if (line[i + 1] == '|')
	{
		printf("\n[double_quotes_token_saver] PIPE\n");
		return ;
	}
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //добавить другие пробелы
	{
		regular_char_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	printf("\n[double_quotes_token_saver] END\n");
}

void	single_quote_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	int	k;

	k = ft_strlen(tokens[token_n]) - 1;
	printf("\n[single_quote_token_saver] k=%d\n", k);
	while (line[++i] != '\'')
	{
		tokens[token_n][++k] = line[i];
		printf("%c", tokens[token_n][k]);
	}
	tokens[token_n][++k] = '\0';
	if (line[i + 1] == '\'')
	{
		single_quote_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	if (line[i + 1] == '\"')
	{
		double_quotes_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	if (line[i + 1] == '|')
	{
		printf("\n[single_quote_token_saver] PIPE\n");
		return ;
	}
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //добавить другие пробелы
	{
		regular_char_token_saver(tokens, token_n, line, i + 1, envs);
		return ;
	}
	printf("\n[single_quote_token_saver] END\n");
}

void	regular_char_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	int	k;

	// k = ft_strlen(tokens[token_n]) - 1;
	// printf("\n[regular_char_token_saver] k=%d\n", k);
	while (1)
	{
		k = ft_strlen(tokens[token_n]) - 1;
		printf("\n[regular_char_token_saver] k=%d\n", k);
		if (line[i] == '\'')
		{
			single_quote_token_saver(tokens, token_n, line, i, envs);
			return ;
		}
		if (line[i] == '\"')
		{
			double_quotes_token_saver(tokens, token_n, line, i, envs);
			return ;
		}
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0')//04.08 fix $TERM $ HOME //11.08 fix $
		{
			i = get_env_var_value_to_saver(tokens, token_n, line, i + 1, envs);
			// i = get_env_var_value(line, i + 1, 0, envs);
			i++;
			continue; //04.08 fix $TERM$HOME - должен быть 1 аргумент
		}
		if (line[i] == ' ') //добавить другие пробелы
			break ;
		if (line[i] == '\0')
			break ;
		tokens[token_n][++k] = line[i];
		printf("k=%d: %c", k, tokens[token_n][k]);
		if (line[i] == '|' || line[i + 1] == '|' || line[i] == '>' || line[i + 1] == '>' || line[i] == '<' || line[i + 1] == '<')
			break;
		i++;
	}
	tokens[token_n][++k] = '\0';
	printf("\n[regular_char_token_saver END]\n");
}

void	special_chars_token_saver(char **tokens, int token_n, char *line, int i)
{
	int	k;

	k = -1;
	printf("\n[special_chars_token_saver]\n");
	tokens[token_n][++k] = line[i];
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || (line[i - 1] == '<' && line[i] == '<'))
	{
		tokens[token_n][++k] = line[i];
		i++;
	}
	tokens[token_n][++k] = '\0';
	printf("\n[special_chars_token_saver END]\n");
}