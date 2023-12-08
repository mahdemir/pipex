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
LIBFT_REPO		= https://github.com/mahdemir/libft.git
PULL_LOG		= ./pull_log
PROG_HEADER		= $(INC_DIR)/pipex.h

SRC = $(addprefix $(SRC_DIR)/, \
    	main.c \
		pipex.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

##### COMPILATION ##############################################################
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I $(INC_DIR)

SHELL	:= /bin/bash

NAME	= pipex
CHECKSUM_FILE := $(BUILD)/last_build_checksum

##### RULES ####################################################################

all: lft $(NAME)
	@if [ -e "$(CHECKSUM_FILE)" ] && [ "$$(cat $(CHECKSUM_FILE))" = "$$(make checksum)" ]; then \
		echo -e "${BOLD}${GREEN}[ OK ]  Pipex is already built!${END}"; \
	else \
		make checksum > "$(CHECKSUM_FILE)"; \
		echo -e "${BOLD}${GREEN}[ OK ]  Pipex built successfully! 🎉${END}"; \
	fi \

$(NAME): $(OBJ)
	@echo -e "${BOLD}${YELLOW}[ .. ]  Compiling pipex ..${END}"
	@$(CC) $(CFLAGS) $^ $(LIBFT_LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(PROG_HEADER) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make -s clean -C $(LIBFT_PATH); \
	else \
		echo -e "${BOLD}${PURPLE}    > - All objects files have been deleted ❌${END}"; \
	fi
	@rm -rf $(BUILD)

fclean:
	@if [ -d "$(LIBFT_PATH)" ]; then \
		make -s fclean -C $(LIBFT_PATH); \
	else \
		echo -e "${BOLD}${PURPLE}    > - All objects files have been deleted ❌${END}"; \
		echo -e "${BOLD}${RED}    > - Cleaning has been done ❌${END}"; \
	fi
	@rm -rf $(BUILD) $(LIBFT_PATH)
	@rm -f $(NAME) $(PULL_LOG)

re: fclean all

lft:
	@if [ ! -d "$(LIBFT_PATH)" ]; then \
		echo -e "${BOLD}${GRAY}    > - Cloning $(LIBFT_REPO) ..${END}\n"; \
		git clone $(LIBFT_REPO) $(LIBFT_PATH) &> /dev/null; \
    else \
        echo -e "${BOLD}${GRAY}    > - Checking for updates in $(LIBFT_REPO) ..${END}"; \
        LOCAL_HASH=$$(git -C $(LIBFT_PATH) rev-parse HEAD); \
        REMOTE_HASH=$$(git -C $(LIBFT_PATH) ls-remote origin -h refs/heads/main | cut -f1); \
        if [ "$$LOCAL_HASH" = "$$REMOTE_HASH" ]; then \
			echo -e "${BOLD}${GRAY}    > - Libft is already up to date!${END}\n"; \
        else \
			echo -e "${BOLD}${GRAY}    > - Updating libft.. See $(PULL_LOG) for details!${END}\n"; \
            git -C $(LIBFT_PATH) pull &> $(PULL_LOG); \
        fi \
    fi
	@make -s -C $(LIBFT_PATH)

checksum:
	@find $(SRC_DIR) -name '*.c' | xargs cat | shasum -a 256 | cut -d ' ' -f 1

.PHONY: all clean fclean re lft
