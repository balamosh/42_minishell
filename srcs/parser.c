/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 22:19:51 by heboni            #+#    #+#             */
/*   Updated: 2022/09/16 07:48:02 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *parser(char *line, t_env **envs)
{
	t_ast_node *ast_nodes;
	char	**tokens;
	int		*exeption_indexes;
	int		exeption_indexes_n;
	int		tokens_count;
	
	exeption_indexes = NULL;
	tokens = get_tokens(line, envs, &exeption_indexes, &exeption_indexes_n);
	if (tokens == NULL)
	{
		printf("TOKENS == NULL\n");
		return (NULL);
	}
	tokens_count = get_tokens_count(tokens);
	printf("[parser] ");
	// printf("tokens_count: %d\n", tokens_count);
	print_string_array(tokens, 0);
	print_int_array(exeption_indexes, exeption_indexes_n);
	// ast_nodes = NULL;
	ast_nodes = tokens_to_ast_nodes(tokens, tokens_count, exeption_indexes, exeption_indexes_n);
	if (ast_nodes == NULL)
		printf("[parser NO_NODES_LIST]\n");
	// print_nodes_list(ast_nodes);
	if (exeption_indexes)
		free(exeption_indexes);
	free_string_array(tokens);
	return (ast_nodes);
}

char	**get_tokens(char *line, t_env **envs, int **exeption_indexes, int *exeption_indexes_n)
{
	char **tokens;
	int	tokens_count;
	int len;
	int	i;
	int tmp_i;

	i = -1;
	tokens_count = 0;
	*exeption_indexes_n = 0;
	printf("[get_tokens] line: %s\n", line);
	len = ft_strlen(line); 
	printf("[get_tokens]: len = %d\n", len);
	line[len] = '\0';
	tokens = NULL;
	while (++i < len)
	{
		cur_env_vars_len = 0; //TO DO передавать аргументом/в контексте
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' \
				|| line[i] == '\r' || line[i] == '\f' || line[i] == '\v')
		{
			i++;
		}
		if (line[i] == '\"')
		{
			tmp_i = i; //"
			i = double_quotes_lexer(line, i, envs);
			if (msh_ctx->not_closed_quote == 1)
				return (NULL);
			int token_len = i - tmp_i + cur_env_vars_len; //TO DO внести cur_env_vars_len в context
			printf("\ni: %d, tmp_i: %d, cur_env_vars_len: %d, token_len: %d", i, tmp_i, cur_env_vars_len, token_len);
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n\n", tokens_count);
			
			if (is_exeption_token(line, tmp_i, '\"'))
			{
				printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
				exeption_indexes = int_array_realloc(exeption_indexes, exeption_indexes_n);
				(*exeption_indexes)[*exeption_indexes_n - 1] = tokens_count - 1;
			}
			
			tokens = tokens_realloc(tokens, tokens_count);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий токен
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			double_quotes_token_saver(tokens, tokens_count - 1, line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_string_array(tokens, tokens_count);
		}
		else if (line[i] == '\'') //пока обработаю легкий случай: без внутренних таких же ""
		{
			tmp_i = i; //'
			i = single_quote_lexer(line, i, envs); //в случае '..''..' выделяю больше памяти чем нужно, обрезаю \0 в saver
			if (msh_ctx->not_closed_quote == 1)
				return (NULL);
			int token_len = i - tmp_i; 
			printf("\ni: %d, tmp_i: %d, token_len: %d", i, tmp_i, token_len);//получить длину токена 
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n", tokens_count);
			
			if (is_exeption_token(line, tmp_i, '\''))
			{
				printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
				exeption_indexes = int_array_realloc(exeption_indexes, exeption_indexes_n);
				(*exeption_indexes)[*exeption_indexes_n - 1] = tokens_count - 1;
			}
			
			tokens = tokens_realloc(tokens, tokens_count);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
			tokens[tokens_count - 1][0] = '\0';
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			single_quote_token_saver(tokens, tokens_count - 1, line, tmp_i, envs);// single_quote_token_saver(tokens[tokens_count - 1], line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_string_array(tokens, tokens_count);
		}
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			tmp_i = i;
			i = special_chars_lexer(line, i);
			int token_len = i - tmp_i;
			tokens_count++;	
			i--; //если ls|grep делаем токен [|]: special_chars_lexer возвр. i~], token_len=1, возвр. на | 
			tokens = tokens_realloc(tokens, tokens_count);//можно делать реаллок массива токенов
			// printf("[get_tokens] %s\n", tokens[0]);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
			tokens[tokens_count - 1][0] = '\0';
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			special_chars_token_saver(tokens, tokens_count - 1, line, tmp_i);
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_string_array(tokens, tokens_count);
		}
		else if (line[i] != '\0')
		{
			tmp_i = i;
			i = regular_char_lexer(line, i, envs);
			int token_len = i - tmp_i + cur_env_vars_len;
			printf("\ni: %d, tmp_i: %d, cur_env_vars_len: %d, token_len: %d", i, tmp_i, cur_env_vars_len, token_len);//получить длину токена 
			tokens_count++;
			printf("\n[get_tokens] line[%d]: %c, tokens_count: %d\n", i, line[i], tokens_count);

			tokens = tokens_realloc(tokens, tokens_count);//можно делать реаллок массива токенов
			// printf("[get_tokens] %s\n", tokens[0]);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
			tokens[tokens_count - 1][0] = '\0';
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			regular_char_token_saver(tokens, tokens_count - 1, line, tmp_i, envs);// single_quote_token_saver(tokens[tokens_count - 1], line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_string_array(tokens, tokens_count);
		}
	}
	return (tokens);
}

int	is_exeption_token(char *line, int tmp_i, char c)
{
	// if (((line[tmp_i + 1] == '|' || line[tmp_i + 1] == '>' || line[tmp_i + 1] == '<')\
	// 	&& line[tmp_i + 2] == '\"' && (line[tmp_i + 3] == ' ' ||  line[tmp_i + 3] == '\0')) || \
	// 	(((line[tmp_i + 1] == '>' && line[tmp_i + 2] == '>') || (line[tmp_i + 1] == '<' && line[tmp_i + 2] == '<')) && \
	// 	line[tmp_i + 3] == '\"' && (line[tmp_i + 4] == ' ' ||  line[tmp_i + 4] == '\0')) )
	if (((line[tmp_i + 1] == '|' || line[tmp_i + 1] == '>' || line[tmp_i + 1] == '<')\
		&& line[tmp_i + 2] == c && (line[tmp_i + 3] == ' ' ||  line[tmp_i + 3] == '\0')) || \
		(((line[tmp_i + 1] == '>' && line[tmp_i + 2] == '>') || (line[tmp_i + 1] == '<' && line[tmp_i + 2] == '<')) && \
		line[tmp_i + 3] == c && (line[tmp_i + 4] == ' ' ||  line[tmp_i + 4] == '\0')) )
			return (1); //TO DO добавить другие пробелы
	return (0);
}