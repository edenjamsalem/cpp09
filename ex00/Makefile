NAME = btc

CC = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS =	main.cpp \
		BitcoinExchange.cpp

OBJDIR = ./build
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -fr $(OBJDIR)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re