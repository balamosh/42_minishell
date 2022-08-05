/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:26:06 by heboni            #+#    #+#             */
/*   Updated: 2022/08/05 15:46:35 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**lexer(char *line, t_env **envs)
{
	char	**tokens;
	int		tokens_count;

	// printf("[lexer] line: %s\n", line);
	tokens_count = get_tokens(line, envs);//получить число токенов для дальнейшего выделения памяти
	printf("[lexer] tokens_count: %d\n", tokens_count);
	if (tokens_count == 0)
		return (NULL);
	
	// tokens = (char **)malloc(sizeof(char *) * tokens_count); //выделить память под char **
	// if (tokens == NULL)
	// 	exit(STACK_OVERFLOW);
	// tokens = get_tokens2(line, tokens, tokens_count, envs);
	
	return (tokens); //TO DO void
}

// char	**get_tokens2(char *line, char **tokens, int tokens_count, t_env **envs)
// {
// 	int read_chars_count;
// 	int token_len;
// 	int	i;

// 	i = -1;
// 	read_chars_count = 0;
// 	//1)realloc
// 	//2) - очень много проходов по line
	
// 	while (++i < tokens_count)//2)цикл
// 	{
// 		token_len = get_current_token_len(line, read_chars_count);//получить число символов в текущем токене
// 		tokens[i] = (char *)malloc(sizeof(char) * token_len);//выделить память под текущий токен
// 		if (tokens[i] == NULL)
// 			exit(STACK_OVERFLOW);
// 		save_current_token(line, token_len, read_chars_count);//сохранить текущий токен
// 		read_chars_count += token_len;
		
// 		printf("%s\n", tokens[i]);
// 	}
// }
// int	get_current_token_len()
// {
// 	int token_len;

// 	token_len = 0;
	
// 	return (token_len);
// }

int	get_tokens(char *line, t_env **envs) //вероятно изменить возвр. зн. на char **tokens
{
	char **tokens;
	char *cur_token; //TEST
	int	tokens_count;
	int len;
	int	i;
	int tmp_i;

	i = -1;
	tokens_count = 0;
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
		if (line[i] == '\"') //пока обработаю легкий случай: без внутренних таких же ""
		{
			tmp_i = i; //"
			i = double_quotes_lexer(line, i, envs); //тут последний символ токена //только как учитывать длину переменных окружения
			int token_len = i - tmp_i + cur_env_vars_len; //длина токена ' - ' (token + '\0')
			printf("\ni: %d, cur_env_vars_len: %d, token_len: %d", i, cur_env_vars_len, token_len);
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n\n", tokens_count);
			
			tokens = tokens_realloc(tokens, tokens_count);//реаллок массива токенов
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий токен
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);//выделить память под текущий токен
			double_quotes_token_saver(tokens[tokens_count - 1], line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_tokens_array(tokens, tokens_count);
		} 
		else if (line[i] == '\'') //пока обработаю легкий случай: без внутренних таких же ""
		{
			tmp_i = i; //'
			i = single_quote_lexer(line, i, envs);
			int token_len = i - tmp_i; printf("\ntmp_i: %d, i: %d, token_len: %d", tmp_i, i, token_len);//получить длину токена 
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n", tokens_count);
			
			tokens = tokens_realloc(tokens, tokens_count);//можно делать реаллок массива токенов
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий токен
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			single_quote_token_saver(tokens[tokens_count - 1], line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_tokens_array(tokens, tokens_count);
			
			// cur_token = (char *)malloc(sizeof(char) * token_len);
			// if (cur_token == NULL)
			// 	exit(STACK_OVERFLOW);
			// single_quote_token_saver(cur_token, line, tmp_i, envs);
			// printf("saved_token: %s\n\n", cur_token);
		} 
		else if (line[i] != '\0')
		{
			i = regular_char_lexer(line, i, envs);
			tokens_count++;
			//сохранить токен до пайпа и выйти(запомнить i/счетчик_пайпов++), получить t_ast_node, добавить в t_lst_elems
			if (line[i] == '|')
			{
				printf("\nPIPE\n");
				return (tokens_count);
			}
			printf("\n[get_tokens] line[%d]: %c, tokens_count: %d\n", i, line[i], tokens_count);
		}
	}
	return (tokens_count);
}

void	print_tokens_array(char **tokens, int tokens_count)
{
	int i = -1;

	printf("print_tokens_array\n");
	while (++i < tokens_count)
		printf("%s\n", tokens[i]);
	printf("print_tokens_array END\n\n");
}

void	single_quote_token_saver(char *allocated_token, char *line, int i, t_env **envs)
{
	int	k;

	k = -1;
	printf("single_quote_token_saver\n");
	while (line[++i] != '\'')
	{
		// printf("single: %c\n", line[i]);
		// printf("%c", line[i]);
		allocated_token[++k] = line[i];
		printf("%c", allocated_token[k]);
		if (line[i] == '\0')
		{
			printf("\nNot closed quote \'\n");
			exit(-1) ; //TO DO strerror
		}
	}
	allocated_token[++k] = '\0';
	printf("\nsingle_quote_token_saver END\n");
}

void	double_quotes_token_saver(char *allocated_token, char *line, int i, t_env **envs)
{
	int	k;

	k = -1;
	printf("double_quotes_token_saver\n");
	while (line[++i] != '\"')
	{
		// printf("double: %c\n", line[i]);
		// printf("%c", line[i]);
		allocated_token[++k] = line[i];
		printf("%c", allocated_token[k]);
		// if (line[i] == '$')
		// 	i = env_var_value_token_saver(line, allocated_token, i + 1, 1, envs); //TO DO
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			exit(-1) ; //TO DO strerror
		}
	}
	allocated_token[++k] = '\0';
	printf("\ndouble_quotes_token_saver END\n");
}


char	**tokens_realloc(char **tokens, int tokens_count) //почитать как делать realloc двумерных массивов с сохранением информации
{
	
	// if (tokens != NULL)
	// {
	// 	//нужно делать какой-то временный массив токенов, пересохранять туда все из tokens
	// 	//освободить память каждого эл-та массива
	// 	free(tokens);
	// }
	tokens = (char **)malloc(sizeof(char *) * tokens_count); //выделить память под char **
	if (tokens == NULL)
		exit(STACK_OVERFLOW);
	//из tmp_tokens перенести в tokens
	//free(tmp_tokens);
	return (tokens);
}

int	regular_char_lexer(char *line, int i, t_env **envs)
{
	// printf("in regular\n");
	// while (line[i] != ' ') //добавить другие пробелы
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
		// if (line[i] == '$')
		if (line[i] == '$' && line[i + 1] != ' ')//04.08 fix $TERM $ HOME
		{
			i = get_env_var_value(line, i + 1, 0, envs);
			i++;
			continue; //04.08 fix $TERM$HOME - должен быть 1 аргумент
		}
		printf("%c", line[i]);
		if (line[i] == ' ') //добавить другие пробелы
			break ;
		if (line[i] == '\0')
			break ;
		if (line[i] == '|' || line[i + 1] == '|')
			break;
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
		if (line[i] == '$')
			i = get_env_var_value(line, i + 1, 0, envs); //05.08
		else
			printf("%c", line[i]); //05.08
		if (line[i] == '\0')
		{
			printf("Not closed quote \"\n");
			exit(-1) ; //TO DO strerror
		}
	}
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
			exit(-1) ; //TO DO strerror
		}
	}
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


int	get_env_var_value(char *line, int i, int handle_quotes, t_env **envs)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;

	var_len = 0;
	tmp_i = i;
	while (line[i] != ' ')
	{
		if (line[i] == '\0' || line[i] == '$' || line[i] == '\"' || line[i] == '\'') //добавить другие пробелы
			break ;
		var_len++;
		i++;
	}
	var_name = (char *)malloc(sizeof(char) * var_len + 1);
	if (var_name == NULL)
		exit(STACK_OVERFLOW);
	get_env_name_from_line(&var_name, line, tmp_i, handle_quotes);
	// printf("\nvar_len %d\n", var_len); printf("var_name: %s\n", var_name); printf("var_value: "); //print_env_list(envs); 
	var_value = get_env_value_by_name(var_name, envs);
	printf("%s", var_value);
	free(var_name);
	return (i - 1);
}

void	get_env_name_from_line(char **var_name, char *line, int tmp_i, int handle_quotes)
{
	int	j;

	j = 0;
	while (line[tmp_i] != ' ')
	{
		// printf("\nsave var_name\n%c", line[tmp_i]);
		if (line[tmp_i] == '\0' || line[tmp_i] == '$' || line[tmp_i] == '\'' || ((handle_quotes == 0) && line[tmp_i] == '\"')) //добавить другие пробелы
			break ;
		(*var_name)[j] = line[tmp_i];
		tmp_i++;
		j++;
	}
	(*var_name)[j] = '\0';
}