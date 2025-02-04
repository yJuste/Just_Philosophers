NAME = philo

CC = cc
CFLAGS = -g # -Wall -Wextra -Werror
FLAGS = -pthread
IFLAGS = -I $(INC_DIR)

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRC =	main.c			\
	ft_parsing.c		\
	ft_philosophers.c	\
	ft_routine.c		\
	ft_monitoring.c		\
	ft_check.c		\
	ft_utils.c		\
	ft_lib.c

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

NORMINETTE =	$(SRC_DIR)/*.c		\
		$(INC_DIR)/*.h

RESET			= "\033[0m"
GREEN			= "\033[92m"	# Green
RED			= "\033[91m"	# Red

all: makedir $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"--- EXECUTABLE ./$(NAME) is ready ---`make help`"$(RESET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

makedir:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@echo $(RED)"--- EXECUTABLE ./$(NAME) is removed ---"$(RESET)

re: fclean all

rf: re
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo $(RED)"--- EXECUTABLE ./$(NAME) is removed ---"$(RESET)

s:
	ls -lh $(NAME)

help:
	@echo $(GREEN)
	@head -n 11 $(INC_DIR)/ft_philosophers.h
	@echo $(RESET)

norm:
	@norminette $(NORMINETTE)

.PHONY: all clean fclean re rf s help nrom
