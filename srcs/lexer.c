/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:26:06 by heboni            #+#    #+#             */
/*   Updated: 2022/09/04 22:45:45 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**lexer(char *line, t_env **envs) //из lexer'a лучше получать t_lst_elems (список токенов-нод)
{
	char	**tokens;
	int		*special_indexes;
	int		special_indexes_n;
	int		tokens_count;

	// printf("[lexer] line: %s\n", line);
	
	special_indexes = NULL;
	tokens = get_tokens(line, envs, &special_indexes, &special_indexes_n);
	printf("[lexer] ");
	print_tokens_array(tokens, 0);
	print_int_array(special_indexes, special_indexes_n);
	if (special_indexes)
		free(special_indexes);
	return (tokens); //TO DO t_lst_elems
}

t_ast_node *parser(char *line, t_env **envs)
{
	t_ast_node *ast_nodes;
	char	**tokens;
	int		*special_indexes;
	int		special_indexes_n;
	// int		tokens_count;
	
	special_indexes = NULL;
	tokens = get_tokens(line, envs, &special_indexes, &special_indexes_n);
	// tokens_count = get_tokens_count(tokens); //зачем нужен tokens_count?
	printf("[parser] ");
	// printf("tokens_count: %d\n", tokens_count);
	print_tokens_array(tokens, 0);
	print_int_array(special_indexes, special_indexes_n);
	if (special_indexes)
		free(special_indexes);
	// ast_nodes = NULL;
	ast_nodes = tokens_to_ast_nodes(tokens, special_indexes, special_indexes_n);
	if (ast_nodes == NULL)
		printf("[parser NO_NODES_LIST]\n");
	// print_nodes_list(ast_nodes);
	free_tokens_array(tokens);
	return (ast_nodes);
}

void	print_nodes_list(t_ast_node *ast_nodes)
{	
	t_ast_cmd *cmd;
	
	if (ast_nodes == NULL)
	{
		printf("[print_nodes_list NO_LIST]\n");
		return ;
	}
	printf("[print_nodes_list]\n");
	while (ast_nodes)
	{
		printf("type: %u ", ast_nodes->type);
		if (ast_nodes->type == MSH_PIPE)
			printf("PIPE\n");
		if (ast_nodes->type == MSH_CMD)
		{
			cmd = ast_nodes->data;
			printf("CMD: %s\n", cmd->cmd_name);
		}
		ast_nodes = ast_nodes->next;
	}
	printf("[print_nodes_list END]\n");
}

t_ast_node *tokens_to_ast_nodes(char **tokens, int *special_indexes, int special_indexes_n)
{
	int	i;
	t_ast_node *ast_nodes;
	char **tokens_pntr = tokens;

	i = 0;
	ast_nodes = NULL;
	while (*tokens != NULL)
	{
		// printf("%s\n", *tokens);
		if (ft_strcmp(*tokens, "|") == 0)
			ast_node_lst_push_bottom(&ast_nodes, MSH_PIPE);
		else if (ft_strcmp(*tokens, ">") == 0)
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_R);
		else if (ft_strcmp(*tokens, ">>") == 0)
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_RR);
		else if (ft_strcmp(*tokens, "<") == 0)
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_L);
		else if (ft_strcmp(*tokens, "<<") == 0)
			ast_node_lst_push_bottom(&ast_nodes, MSH_REDIRECT_LL);
		// else if ((*tokens)[0] == '.' && (*tokens)[1] == '/')
		// 	ast_node_lst_push_bottom(&ast_nodes, MSH_FILE);
		else
		{
			printf("no seg %s\n", *tokens);
			ast_cmd_node_lst_push_bottom(&ast_nodes, tokens_pntr, i, MSH_CMD); //в аргументы нужно сложить все токены до 1-го | <

		}
		printf("%s\n", *tokens++);
		i++;
	}
	// print_nodes_list(ast_nodes);
	return (ast_nodes);
}

void	ast_cmd_node_lst_push_bottom(t_ast_node **head, char **tokens, int i, t_ast_type type)
{
	t_ast_node	*new;
	t_ast_node	*last_node;
	t_ast_cmd	*cmd;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	if (type == MSH_CMD)
	{
		cmd = (t_ast_cmd *)malloc(sizeof(t_ast_cmd));
		cmd->cmd_name = ft_strdup(tokens[i]);
		new->data = cmd;
	}
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_node0(*head);
	last_node->next = new;
	return ;
}

void	ast_node_lst_push_bottom(t_ast_node **head, t_ast_type type)
{
	t_ast_node	*new;
	t_ast_node	*last_node;
	t_ast_cmd	*cmd;

	new = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (new == NULL)
		exit(STACK_OVERFLOW);
	new->type = type;
	// if (type == MSH_CMD)
	// {
	// 	cmd = (t_ast_cmd *)malloc(sizeof(t_ast_cmd));
	// 	cmd->cmd_name = ;
	// 	// new->data = (t_ast_cmd *)malloc(sizeof(t_ast_cmd));
	// 	new->data = cmd;
	// }
	// new->var_name = ft_strdup(name);
	// new->var_value = ft_strdup(value);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	last_node = get_last_node0(*head);
	last_node->next = new;
}

t_ast_node	*get_last_node0(t_ast_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int get_tokens_count(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens != NULL)
	{
		count++;
		tokens++;
	}
	return (count);
}



void	print_int_array(int *array, int n)
{
	int	i;

	i = -1;
	printf(" [print_special_indexes_int_array]\n");
	while (++i < n)
		printf("%d ", array[i]);
	printf(" [print_special_indexes_int_array] END\n");
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

char	**get_tokens(char *line, t_env **envs, int **special_indexes, int *special_indexes_n)
{
	char **tokens;
	int	tokens_count;
	int len;
	int	i;
	int tmp_i;

	i = -1;
	tokens_count = 0;
	*special_indexes_n = 0;
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
			int token_len = i - tmp_i + cur_env_vars_len; //TO DO внести cur_env_vars_len в context
			printf("\ni: %d, tmp_i: %d, cur_env_vars_len: %d, token_len: %d", i, tmp_i, cur_env_vars_len, token_len);
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n\n", tokens_count);
			
			if (is_exeption_token(line, tmp_i, '\"'))
			{
				printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
				special_indexes = int_array_realloc(special_indexes, special_indexes_n);
				(*special_indexes)[*special_indexes_n - 1] = tokens_count - 1;
			}
			
			tokens = tokens_realloc(tokens, tokens_count);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий токен
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			double_quotes_token_saver(tokens, tokens_count - 1, line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_tokens_array(tokens, tokens_count);
		} 
		else if (line[i] == '\'') //пока обработаю легкий случай: без внутренних таких же ""
		{
			tmp_i = i; //'
			i = single_quote_lexer(line, i, envs); //в случае '..''..' выделяю больше памяти чем нужно, обрезаю \0 в saver
			int token_len = i - tmp_i; 
			printf("\ni: %d, tmp_i: %d, token_len: %d", i, tmp_i, token_len);//получить длину токена 
			tokens_count++;
			printf("\n[get_tokens] tokens_count: %d\n", tokens_count);
			
			if (is_exeption_token(line, tmp_i, '\''))
			{
				printf("\n[get_tokens] ONLY SPECIAL CHAR TOKEN\n");
				special_indexes = int_array_realloc(special_indexes, special_indexes_n);
				(*special_indexes)[*special_indexes_n - 1] = tokens_count - 1;
			}
			
			tokens = tokens_realloc(tokens, tokens_count);
			tokens[tokens_count - 1] = (char *)malloc(sizeof(char) * token_len); //выделить память под текущий(новый) токен
			tokens[tokens_count - 1][0] = '\0';
			if (tokens[tokens_count - 1] == NULL)
				exit(STACK_OVERFLOW);
			single_quote_token_saver(tokens, tokens_count - 1, line, tmp_i, envs);// single_quote_token_saver(tokens[tokens_count - 1], line, tmp_i, envs);//заполнить текущий токен
			printf("saved_token: %s\n\n", tokens[tokens_count - 1]);
			print_tokens_array(tokens, tokens_count);
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
			print_tokens_array(tokens, tokens_count);
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
			print_tokens_array(tokens, tokens_count);
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

int	**int_array_realloc(int **array, int *array_n)
{
	int	*tmp_array;
	int	i;

	i = -1;
	tmp_array = NULL;
	printf("[int_array_realloc] array_n: %d\n", *array_n);
	if (*array_n != 0)
	{
		tmp_array = (int *)malloc(sizeof(int) * *array_n); //выделить память под char **
		if (tmp_array == NULL)
			exit(STACK_OVERFLOW);
		while (++i < *array_n)
		{
			tmp_array[i] = (*array)[i];
			printf("[int_array_realloc] tmp_array[%d]=%d\n", i, tmp_array[i]);
		}
		free(*array);
	}
	*array_n += 1;
	*array = (int *)malloc(sizeof(int) * *array_n); //выделить память под char **
	if (*array == NULL)
		exit(STACK_OVERFLOW);
	
	if (tmp_array != NULL)
	{
		//из tmp_array перенести в переаллоцированный array
		i = -1;
		while (++i < (*array_n - 1))
			(*array)[i] = tmp_array[i];
		free(tmp_array);
	}
	return (array);
}

char	**tokens_realloc(char **tokens, int tokens_count) //почитать как делать realloc двумерных массивов с сохранением информации
{
	char	**tmp_tokens;
	int		token_len;
	int		i;
	
	i = -1;
	tmp_tokens = NULL;
	printf("[tokens_realloc] tokens_count: %d\n", tokens_count);
	if (tokens != NULL)
	{
		tmp_tokens = (char **)malloc(sizeof(char *) * tokens_count); //выделить память под char **
		if (tmp_tokens == NULL)
			exit(STACK_OVERFLOW);
		tmp_tokens[tokens_count - 1] = NULL; //нужно делать какой-то временный массив токенов, пересохранять туда все из tokens
		while (++i < tokens_count - 1)
		{
			printf("[tokens_realloc] TEST %d\n", i);
			tmp_tokens[i] = ft_strdup(tokens[i]);
			free(tokens[i]); //освободить память каждого эл-та массива
			printf("[tokens_realloc] %d: %s\n", i, tmp_tokens[i]);
			// token_len = ft_strlen(tokens[i]); printf("[tokens_realloc] %d token_len: %d\n", i, token_len);
			// tmp_tokens[i] = (char *)malloc(sizeof(char) * token_len + 1);
			// tmp_tokens[i][token_len] = '\0';
		}
		free(tokens);
	}
	tokens = (char **)malloc(sizeof(char *) * tokens_count + 1); //выделить память под char **
	if (tokens == NULL)
		exit(STACK_OVERFLOW);
	tokens[tokens_count] = NULL;
	
	if (tmp_tokens != NULL)
	{
		//из tmp_tokens перенести в переаллоцированный tokens
		i = -1;
		while (++i < tokens_count - 1)
		{
			tokens[i] = ft_strdup(tmp_tokens[i]);
			free(tmp_tokens[i]);
		}
		free(tmp_tokens);
	}
	return (tokens);
}

void	print_tokens_array(char **tokens, int tokens_count)
{
	int i = -1;
	
	printf("print_tokens_array\n");
	if (tokens_count == 0)
	{
		while (*tokens != NULL)
			printf("%s\n", *tokens++);
	} else 
	{
		while (++i < tokens_count)
			printf("%s\n", tokens[i]);
	}
	printf("print_tokens_array END\n\n");
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

void	double_quotes_token_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	int	k;

	k = ft_strlen(tokens[token_n]) - 1;
	printf("\n[double_quotes_token_saver] k=%d\n", k);
	while (line[++i] != '\"')
	{
		// printf("double: %c\n", line[i]);
		// printf("%c", line[i]);
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"')
		{
			i = get_env_var_value_to_saver(tokens, token_n, line, i + 1, envs);
			i++;
			// i = get_env_var_value(line, i + 1, envs);
			break;
		}
		else
		{
			tokens[token_n][++k] = line[i];
			printf("%c", tokens[token_n][k]);
		}
		// printf("%c", line[i]); //05.08
		// tokens[token_n][++k] = line[i];
		// printf("%c", tokens[token_n][k]);
	}
	k = ft_strlen(tokens[token_n]) - 1;
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
			i = get_env_var_value(line, i + 1, envs); // i = get_env_var_value(line, i + 1, 0, envs);
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

int	double_quotes_lexer(char *line, int i, t_env **envs)
{
	// printf("in double\n");
	while (line[++i] != '\"')
	{
		// printf("double[%d]: %c\n", i, line[i]);
		// printf("%c", line[i]); //05.08
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\"') //11.08 fix "$", "$ aaa"
			i = get_env_var_value(line, i + 1, envs); // i = get_env_var_value(line, i + 1, 0, envs); //05.08
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

int	get_env_var_value_to_saver(char **tokens, int token_n, char *line, int i, t_env **envs)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		tmp_i;
	int		k;

	k = ft_strlen(tokens[token_n]) - 1;
	printf("\n[get_env_var_value_to_saver] k=%d\n", k);
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
	get_env_name_from_line(&var_name, line, tmp_i); //get_env_name_from_line(&var_name, line, tmp_i, 0); //get_env_name_from_line(&var_name, line, tmp_i, handle_quotes);
	// printf("\nvar_len %d\n", var_len); printf("var_name: %s\n", var_name); //printf("var_value: "); //print_env_list(envs); 
	var_value = get_env_value_by_name(var_name, envs);
	if (var_value) //если env_var не существует, текущий аргумент - null
	{
		while (*var_value)
		{
			tokens[token_n][++k] = *var_value;
			printf("%c", tokens[token_n][k]);
			var_value++;
		}
	}
	free(var_name);
	return (i - 1);
}

int	get_env_var_value(char *line, int i, t_env **envs)
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
	get_env_name_from_line(&var_name, line, tmp_i);
	// printf("\nvar_len %d\n", var_len); printf("var_name: %s\n", var_name); printf("var_value: "); //print_env_list(envs); 
	var_value = get_env_value_by_name(var_name, envs);
	printf("%s", var_value);
	free(var_name);
	return (i - 1);
}

void	get_env_name_from_line(char **var_name, char *line, int tmp_i)
{
	int	j;

	j = 0;
	while (line[tmp_i] != ' ')
	{
		// printf("\nsave var_name\n%c", line[tmp_i]);
		if (line[tmp_i] == '\0' || line[tmp_i] == '$' || line[tmp_i] == '\'' || line[tmp_i] == '\"') //добавить другие пробелы
			break ;
		(*var_name)[j] = line[tmp_i];
		tmp_i++;
		j++;
	}
	(*var_name)[j] = '\0';
}

//handle_quotes
// int	get_env_var_value(char *line, int i, int handle_quotes, t_env **envs)
// {
// 	char	*var_name;
// 	char	*var_value;
// 	int		var_len;
// 	int		tmp_i;

// 	var_len = 0;
// 	tmp_i = i;
// 	while (line[i] != ' ')
// 	{
// 		if (line[i] == '\0' || line[i] == '$' || line[i] == '\"' || line[i] == '\'') //добавить другие пробелы
// 			break ;
// 		var_len++;
// 		i++;
// 	}
// 	var_name = (char *)malloc(sizeof(char) * var_len + 1);
// 	if (var_name == NULL)
// 		exit(STACK_OVERFLOW);
// 	get_env_name_from_line(&var_name, line, tmp_i, handle_quotes);
// 	// printf("\nvar_len %d\n", var_len); printf("var_name: %s\n", var_name); printf("var_value: "); //print_env_list(envs); 
// 	var_value = get_env_value_by_name(var_name, envs);
// 	printf("%s", var_value);
// 	free(var_name);
// 	return (i - 1); //TO DO заменить на i, в вызывающей ф-и убрать i++
// }

// void	get_env_name_from_line(char **var_name, char *line, int tmp_i, int handle_quotes)
// {
// 	int	j;

// 	j = 0;
// 	while (line[tmp_i] != ' ')
// 	{
// 		// printf("\nsave var_name\n%c", line[tmp_i]);
// 		if (line[tmp_i] == '\0' || line[tmp_i] == '$' || line[tmp_i] == '\'' || ((handle_quotes == 0) && line[tmp_i] == '\"')) //добавить другие пробелы
// 			break ;
// 		(*var_name)[j] = line[tmp_i];
// 		tmp_i++;
// 		j++;
// 	}
// 	(*var_name)[j] = '\0';
// }