# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:56:38 by ddantas-          #+#    #+#              #
#    Updated: 2023/03/05 16:30:44 by ddantas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -pthread -Wall -Wextra #-Werror
NAME = philo
RM = rm

FILESC = philo.c ft_atoi.c philo_utils.c philo_action.c \
		philo_utils_2.c

OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -f $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re bonus