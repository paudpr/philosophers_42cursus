# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 16:20:07 by pdel-pin          #+#    #+#              #
#    Updated: 2022/09/27 14:32:16 by pdel-pin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread
CFLAGS += -I $(INC_PATH)

INC_PATH	= includes
SRC_PATH	= sources
OBJ_PATH	= objects

SRC =	main.c \
		check_args.c \
		utils.c \
		philo.c \
		check_deaths.c \
		do_.c \
		init.c \
		print.c \
		

all: $(NAME)

OBJS_NAME = $(SRC:%.c=%.o)

SRCS_NAME = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH) 2> /dev/null

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
			$(CC) $(CFLAGS) -c $< -o $@

			
$(NAME): $(OBJS)
		$(CC) $^ -o $@ $(CFLAGS)


##RULES

debug: CFLAGS +=  -g3 -fsanitize=thread
debug: $(NAME)

debug_bonus: CFLAGS +=  -g3 -fsanitize=address
debug_bonus: $(NAME)

norminette:
	norminette $(SRCS) 

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
		rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re norminette bonus