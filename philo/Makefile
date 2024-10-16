# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquissan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 14:40:09 by aquissan          #+#    #+#              #
#    Updated: 2024/09/30 14:50:54 by aquissan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# NAMES
NAME = philo
NAMES_BONUS = philo_bonus

# DIRECTORIES
HEADERS = includes
DIR_SRC = sources
DIR_OBJ = objects
DIR_BONUS = bonus
DIR_OBJ_BONUS = objects_bonus

# FLAGS
FLAGS = -Wall -Wextra -Werror -g -pthread
CC = cc 
MK = mkdir -p
RM = rm -rf

# NAMED
FILES = main.c utils.c check_freeze.c philosophers_central.c initialize.c\
		forks_set.c
FILES_BONUS = check_freeze_bonus.c initialize_bonus.c philosophers_central_bonus.c\
		forks_set_bonus.c main_bonus.c utils_bonus.c
SRC = $(addprefix $(DIR_SRC)/, $(FILES))
OBJ = $(addprefix $(DIR_OBJ)/, $(FILES:.c=.o))
BONUS = $(addprefix $(DIR_BONUS)/, $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(DIR_OBJ_BONUS)/, $(FILES_BONUS:.c=.o))

# RULES
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(MK) $(DIR_OBJ)
	$(CC) -c -I$(HEADERS) $(FLAGS) $< -o $@

$(DIR_OBJ_BONUS)/%.o: $(DIR_BONUS)/%.c
	$(MK) $(DIR_OBJ_BONUS)
	$(CC) -c $(FLAGS) $< -o $@
clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)
	$(RM) $(DIR_OBJ)
	$(RM) $(DIR_OBJ_BONUS)
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAMES_BONUS)

bonus: $(NAMES_BONUS)

$(NAMES_BONUS): $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAMES_BONUS)


re: fclean all
push: fclean
	git status; git add .; git status; git commit -m "in progress";
	git push

.PHONY: all clean fclean