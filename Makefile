NAME = ircserv

SRCS = 	main.cpp \
		srcs/Server.cpp \
		srcs/User.cpp \
		commands/CmdHandler.cpp \
		commands/Command.cpp \
		commands/Ping.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = includes/Server.hpp \
		includes/User.hpp \
		includes/Command.hpp \
		includes/CmdHandler.hpp

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