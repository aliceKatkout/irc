NAME = ircserv

SRCS = 	main.cpp \
		srcs/Server.cpp \
		srcs/User.cpp \
		srcs/Channel.cpp \
		srcs/utils.cpp \
		commands/CmdHandler.cpp \
		commands/Command.cpp \
		commands/Ping.cpp \
		commands/Nick.cpp \
		commands/UserCmd.cpp \
		commands/Join.cpp \
		commands/Pass.cpp \
		commands/Topic.cpp
		# commands/Mode.cpp
		# commands/Invite.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = includes/Server.hpp \
		includes/User.hpp \
		includes/Channel.hpp \
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