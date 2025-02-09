# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 18:37:50 by aibn-che          #+#    #+#              #
#    Updated: 2024/03/03 16:50:37 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MSRCS = ./detached_thread.c ./ft_atoi.c ./init.c ./parsing.c ./philo.c ./simulation.c ./struct_utils.c
MOBJS = $(MSRCS:.c=.o)

HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror

NAME = philo

all : $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MOBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	rm -f $(MOBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean $(NAME)
