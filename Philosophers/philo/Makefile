NAME = philo

CC = cc
CFLAGS = -g # -Wall -Wextra -Werror

SRC =	ft_philosophers.c	\
	ft_philosophers_2.c	\
	ft_parsing.c		\
	ft_utils.c		\
	ft_lib.c

OBJ = $(SRC:.c=.o)

NORMINETTE =	*.c		\
		*.h

RESET			= "\033[0m"
GREEN			= "\033[92m"	# Green
RED			= "\033[91m"	# Red

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo $(GREEN)"--- EXECUTABLE ./$(NAME) is ready ---`make help`"$(RESET)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	@echo $(RED)"--- EXECUTABLE ./$(NAME) is removed ---"$(RESET)

re: fclean all

rf: re
	rm -f $(OBJ)
	rm -f $(NAME)
	@echo $(RED)"--- EXECUTABLE ./$(NAME) is removed ---"$(RESET)

s:
	ls -lh $(NAME)

help:
	@echo $(GREEN)
	@head -n 11 ft_philosophers.h
	@echo $(RESET)

norm:
	@norminette $(NORMINETTE)

sign:
	@codesign --entitlements entitlements.plist --sign - $(NAME)

.PHONY: all clean fclean re rf s help norm
