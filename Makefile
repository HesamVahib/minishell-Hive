NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc

LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a


SRC_PART = 	main.c \
			clean_utility.c \
			custom_export.c \
			env_list_creator.c \
			extract_env_list.c \
			mode_change.c \
			set_start.c \
			init_env_pack.c \
			minishell.c \
			exit_process.c \
			restore_std_fd.c \
			utility1.c \
			utility2.c \
			tokenization.c \
			lexer.c \
			cmd_syntax_analyzer.c \
			expansion.c \
			heredoc.c \
			tokenz_util_wsplitter.c \
			expansion_utils.c \
			lexer_utils.c \
			sig_handlers.c \
			ft_cmdlen.c \
			tokenz_util_quotes.c \
			print_cmd_temp.c	# Temporary Files		

OBJ_PART = $(SRC_PART:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

$(NAME): $(OBJ_PART)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ_PART) $(LIBFT) -lreadline
	echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled minishell executable\033[0m"

all: $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@/bin/rm -f $(OBJ_PART)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object files deleted\033[0m"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Executable $(NAME) is deleted.\033[0m"

re: fclean all

.PHONY: all clean fclean re
