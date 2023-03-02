NAME = minishell

B 	= 	cd\
		env\
		redir_ex\
		echo\

U	=	utils_env\
		utils_executor\
		utils_expander\
		utils_parser\
		utils_child\
		utils\

FILES = main\
		ft_parser\
		ft_split_exp\
		ft_free\
		ft_expander\
		ft_exit\
		$(BLT)\
		$(ULT)\

LIBFT = Libft/libft.a

BLT = $(addprefix Builting/, $(B))
ULT = $(addprefix Utils/, $(U))
SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))

READLINE_DIR = ${HOME}/.brew/opt/readline

F_READLINE = -I$(READLINE_DIR)/include

COMPILE = -lreadline -L$(READLINE_DIR)/lib

CC = clang
##CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Wstring-compare -fsanitize=address -g3
RM = rm -rf

ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
endif

all: $(NAME)

.c.o: $(SRC)
	@$(CC) $(CFLAGS) $(F_READLINE) -c -o $@ $^

$(NAME): $(OBJ)
	@make -C Libft/
	@$(CC) $(CFLAGS) $(LIBFT) $(COMPILE) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)"

clean:
	@$(RM) $(OBJ)
	@make clean -C Libft/
	@echo "$(RED)Cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C Libft/

re: clean all

.PHONY: all clean fclean re