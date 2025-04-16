NAME = PmergeMe

CC = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98

SRCDIR = srcs
SRCS =	$(SRCDIR)/main.cpp \
		$(SRCDIR)/utils.cpp

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
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