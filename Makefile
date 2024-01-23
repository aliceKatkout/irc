NAME = ircserv

SRCS = 	srcs/main.cpp \
		srcs/Server.cpp \
		srcs/User.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = srcs/Server.hpp \
		srcs/User.hpp

FLAGS = -Wall -Wextra -Werror -std=c++98 

all : $(NAME)

$(NAME) : $(OBJS)  $(INCLUDES)
	c++ $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
	c++ $(FLAGS)  -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re