NAME		= minishell

SRCS_DIR	= srcs/
HEAD_DIR	= includes/
BUILD_DIR	= build/

SRCS_FILES	= main.c							\
			  btree/btree_apply_prefix.c		\
			  btree/btree_create_node.c			\
			  libft/ft_strlen.c 				\
			  libft/ft_strcmp.c					\
			  libft/ft_strdup.c					\
			  parser.c							\
			  lexer.c							\
			  token_saver.c						\
			  array_realloc.c 					\
			  envs_lst_saver.c					\
			  envs_lst_utils.c					\
			  get_env.c 						\
			  tokens_to_ast_nodes.c 			\
			  ast_exec.c						\
			  ast.c								\
			  prompt.c							\
			  utils.c							\
			  free_utils.c 						\
			  test_ast.c						\
			  tests.c

OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(BUILD_DIR), $(OBJS_FILES))
DEPS		= $(OBJS:.o=.d)

CC			= gcc
CFLAGS		= -MMD
# CFLAGS		= -Wall -Werror -Wextra -MMD
LIBS		= -lreadline

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(BUILD_DIR)%.d
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(HEAD_DIR) -o $@ -c $<

$(BUILD_DIR)%.d: ;

$(DEPS):
-include $(wildcard $(DEPS))

clean: 
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: all bonus clean fclean re
