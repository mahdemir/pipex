##### FONT APPEARANCE ##########################################################
END		=$'\033[0m
BOLD	=$'\033[1m
UNDER	=$'\033[4m
REV		=$'\033[7m
GREY	=$'\033[30m
RED		=$'\033[31m
GREEN	=$'\033[32m
YELLOW	=$'\033[33m
BLUE	=$'\033[34m
PURPLE	=$'\033[35m
CYAN	=$'\033[36m
WHITE	=$'\033[37m

##### DIRECTORIES ##############################################################
BUILD			= .build
OBJ_DIR			= $(BUILD)/obj
SRC_DIR			= ./src
INC_DIR			= ./inc
LIBFT_PATH		= ./libft
LIBFT_LIB		= $(LIBFT_PATH)/libft.a
PROG_HEADER		= $(INC_DIR)/pipex.h

SRC = $(addprefix $(SRC_DIR)/, \
    	main.c \
		error_hangling.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

##### COMPILATION ##############################################################
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I $(INC_DIR)

SHELL	:= /bin/bash

NAME	= pipex

##### RULES ####################################################################

all: $(NAME)

$(NAME): $(OBJ) | lft
	@echo -e "${BOLD}${YELLOW}[ .. ] | Compiling pipex..${END}"
	@$(CC) $(CFLAGS) $^ $(LIBFT_LIB) -o $@
	@echo -e "${BOLD}${GREEN}[ OK ] | Compilation is successful! 🎉${END}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(PROG_HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -s clean -C $(LIBFT_PATH)
	@rm -rf $(BUILD)
	@echo -e "${BOLD}${RED}> All objects files have been deleted ❌${END}"

fclean: clean
	@make -s fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo -e "${BOLD}${RED}> Cleaning has been done ❌${END}"

re: fclean all

lft:
	@if [ -f $(LIBFT_LIB) ]; then \
		echo -e "${BOLD}${GREEN}[ OK ] | Libft is already built.${END}"; \
	else \
		make -s -C $(LIBFT_PATH); \
		echo -e "\n${BOLD}${GREEN}[ OK ] | Libft built successfully!${END}"; \
	fi

.PHONY: all clean fclean re lft
