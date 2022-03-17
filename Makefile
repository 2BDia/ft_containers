# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 15:03:49 by rvan-aud          #+#    #+#              #
#    Updated: 2022/03/17 15:30:13 by rvan-aud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.cpp

SRCS_T		= main_time.cpp

NAME		= containers

CXX			= clang++

RM			= rm -f

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I srcs/ -D STL=${STL}

OBJS		= $(SRCS:.cpp=.o)

OBJS_T		= $(SRCS_T:.cpp=.o)

$(NAME):	$(OBJS)
			@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

time:		$(OBJS_T)
			@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS_T)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_T)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
