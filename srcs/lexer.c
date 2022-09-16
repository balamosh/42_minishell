/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:26:06 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 09:24:22 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regular_char_lexer(char *line, int i, t_env **envs)
{
	// printf("in regular\n");
	while (1)
	{
		if (line[i] == '\'')
		{
			i = single_quote_lexer(line, i, envs);
			if (line[i] == '\'') //ech'o' 90
				i++;
			if (line[i] == '\"') //ec'h'"o" 90   01.08
				i++;
		}
		if (line[i] == '\"')
		{
			i = double_quotes_lexer(line, i, envs);
			if (line[i] == '\"') //ech"o" 90
				i++;
		}
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0')//04.08 fix $TERM $ HOME //11.08 fix $
		{
			i = get_env_var_value_to_lexer(line, i + 1, envs); // i = get_env_var_value_to_lexer(line, i + 1, 0, envs);
			i++;
			continue; //04.08 fix $TERM$HOME - должен быть 1 аргумент
		}
		printf("%c", line[i]);
		if (line[i] == ' ') //добавить другие пробелы
			break ;
		if (line[i] == '\0')
			break ;
		if (line[i] == '|' || line[i + 1] == '|' || line[i] == '>' || line[i + 1] == '>' || line[i] == '<' || line[i + 1] == '<')
			break; //после printf для кейсов a| b, a|b
		i++;
	}
	return (i);
}

int	special_chars_lexer(char *line, int i) //из regular_char не надо вызывать special_chars_lexer, special_chars_lexer будет 
{ // всегда вызываться на уровень выше, чтобы было корректное token_count
	printf("%c", line[i]);
	i++;
	if ((line[i - 1] == '>' && line[i] == '>') || (line[i - 1] == '<' && line[i] == '<'))
	{
		printf("%c\n", line[i]);
		i++;
	}
	return (i);
}

int	double_quotes_lexer(char *line, int i, t_env **envs)
{
	// printf("in double\n");
	while (line[++i] != '\"')
	{
		// printf("double[%d]: %c\n", i, line[i]);
		// printf("%c", line[i]); //05.08
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"') //11.08 fix "$", "$ aaa"
			i = get_env_var_value_to_lexer(line, i + 1, envs); // i = get_env_var_value_to_lexer(line, i + 1, 0, envs); //05.08
		else
			printf("%c", line[i]); //05.08
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			msh_ctx->not_closed_quote = 1;
			return (i);// break;
		}
	} //TO DO в кажом if ниже возвращается i, удалить из каждого
	if (line[i + 1] == '\"')
	{
		i = double_quotes_lexer(line, i + 1, envs);
		return (i); //01.08
	}
	if (line[i + 1] == '\'')
	{
		i = single_quote_lexer(line, i + 1, envs);
		return (i); //01.08
	}
	if (line[i + 1] == '|')
		return (i); //03.08
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //04.08 //добавить другие пробелы
	{
		i = regular_char_lexer(line, i + 1, envs);
		return (i); //01.08
	}
	return (i);
}

int	single_quote_lexer(char *line, int i, t_env **envs)
{
	while (line[++i] != '\'')
	{
		// printf("single: %c\n", line[i]);
		printf("%c", line[i]);
		if (line[i] == '\0')
		{
			printf("Not closed quote \'\n");
			msh_ctx->not_closed_quote = 1;
			return (i);// break;
		}
	} //TO DO в кажом if ниже возвращается i, удалить из каждого
	// printf("\nSINGLE_I: %d", i);
	if (line[i + 1] == '\'')
	{
		i = single_quote_lexer(line, i + 1, envs);
		return (i); //01.08
	}	
	if (line[i + 1] == '\"')
	{
		i = double_quotes_lexer(line, i + 1, envs);
		return (i); //01.08
	}
	if (line[i + 1] == '|')
		return (i); //03.08
	if (line[i + 1] != ' ' && line[i + 1] != '\0') //04.08 //добавить другие пробелы
	{
		i = regular_char_lexer(line, i + 1, envs);
		return (i); //01.08
	}
	// printf("\nSINGLE_RETURN_I: %d", i);
	return (i);
}
