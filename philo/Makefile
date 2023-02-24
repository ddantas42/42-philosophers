# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:56:38 by ddantas-          #+#    #+#              #
#    Updated: 2023/02/23 22:57:45 by ddantas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -pthread -Wall -Wextra #-Werror
NAME = philo
RM = rm

FILESC = philo.c ft_atoi.c philo_utils.c philo_action.c

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