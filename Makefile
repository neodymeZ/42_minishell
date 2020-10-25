# ADD HEADER

NAME			= minishell
CFLAGS			= -Wall -Werror -Wextra
NODEPS			= clean fclean re
LIBS			= -L $(LIBFT_FLDR) -lft
INCLUDES		= -I $(LIBFT_FLDR) -I $(HDRS_FLDR)
SRCS_FLDR		= ./srcs
HDRS_FLDR		= ./includes
LIBFT_FLDR		= ./libft
SRCS_LIST		= minishell.c minishell_utils_prompt.c minishell_utils_input.c \
				error_handler.c signal_handlers.c \
				builtin.c builtin_env.c builtin_utils_env.c \
				env.c env_utils.c \
				lexer.c lexer_utils_buffer.c lexer_utils_input.c \
				lexer_utils_tokens.c \
				parser.c parser_utils_nodes.c \
				executor.c executor_utils.c
HDRS_LIST		= minishell.h errors.h lexer.h parser.h executor.h builtin.h
SRCS			= $(addprefix $(SRCS_FLDR)/,$(SRCS_LIST))
OBJS			= $(SRCS:.c=.o)
HDRS			= $(addprefix $(HDRS_FLDR)/,$(HDRS_LIST))
DEPS			= $(SRCS:.c=.d)
LIBFT			= $(LIBFT_FLDR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully \
	compiled minishell\033[0m"

# Include all .d dependency files to the Makefile.
# Including dependencies is conditional - it shall not work when cleaning.

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

# Generate a dependency file for each source file

%.d: %.c $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDES) $< -MM -MF $@; \
	(/bin/echo -n srcs/ && cat $@) > temp && mv temp $@

# Dependencies for .o files are automatically merged with the dependencies from
# .d file for each object

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

$(LIBFT):
	@echo "\033[90m\033[32mLET'S GO!!!\033[90m\033[0m"
	@$(MAKE) -C $(LIBFT_FLDR)

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	@$(MAKE) -C $(LIBFT_FLDR) clean
	@rm -f $(OBJS) $(DEPS)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object and temp files \
	for minishell were deleted\033[0m"

.PHONY: fclean
fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m All compiled \
	items were deleted.\033[0m"

.PHONY: re
re: fclean all
