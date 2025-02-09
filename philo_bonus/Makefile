# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 18:37:50 by aibn-che          #+#    #+#              #
#    Updated: 2024/03/03 18:16:54 by aibn-che         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BSRCS = ./detached_thread.c ./ft_atoi.c ./init.c ./parsing.c ./philo_bonus.c ./simulation.c ./struct_utils.c ./aux_utils.c
BOBJS = $(BSRCS:.c=.o)

B_HEADER = philo_bonus.h

CFLAGS = -Wall -Wextra -Werror

BONUS_NAME = philo_bonus

all: $(BONUS_NAME)

%.o:%.c $(B_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME): $(BOBJS)
	$(CC) $(CFLAGS) $^ -o $(BONUS_NAME)

clean:
	rm -f $(BOBJS)

fclean: clean
	rm -f $(BONUS_NAME)
	
re: fclean $(BONUS_NAME)
