# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 15:03:49 by rvan-aud          #+#    #+#              #
#    Updated: 2022/03/18 15:13:51 by rvan-aud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.cpp

NAME		= containers

CXX			= clang++

RM			= rm -f

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I srcs/ -D STL=${STL}

OBJS		= $(SRCS:.cpp=.o)

$(NAME):	$(OBJS)
			@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
