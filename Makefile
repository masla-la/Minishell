NAME = minishell

B 	= 	cd\
		env\
		redir_ex\

FILES = main\
		utils_env\
		utils_expander\
		utils_executor\
		utils_child\
		utils\
		ft_parser\
		ft_split\
		ft_split_exp\
		ft_free\
		ft_expander\
		ft_exit\
		ft_itoa\
		$(BLT)

BLT = $(addprefix Builting/, $(B))
SRC = $(addsuffix .c, $(FILES))
OBJ = $(addsuffix .o, $(FILES))

CC = clang
CFLAGS = -Wall -Wextra -Werror
##CFLAGS += -Wstring-compare -fsanitize=address -g3
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
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

all: $(NAME)

.c.o: $(SRC)
	@$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)
	@echo "$(GREEN)Done$(RESET)"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re