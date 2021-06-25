CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME_CHECK = server
NAME_PS = client

MAIN_CHECK = server.c
MAIN_PS = client.c
SRCS = srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/qst_ans.c \
		srcs/addBack.c

OBJS = $(SRCS:.c=.o)
MAIN_CHECK_O = $(MAIN_CHECK:.c=.o)
MAIN_PS_O = $(MAIN_PS:.c=.o)

all :  $(NAME_PS) $(NAME_CHECK)

$(NAME_CHECK): $(MAIN_CHECK_O) $(OBJS)
	$(CC) $(FLAGS) $(MAIN_CHECK_O) $(OBJS) -o $(NAME_CHECK)

$(NAME_PS): $(MAIN_PS_O) $(OBJS)
	$(CC) $(FLAGS) $(MAIN_PS_O) $(OBJS) -o $(NAME_PS)

clean:
	rm -rf $(OBJS)
	rm -rf $(MAIN_PS_O)
	rm -rf $(MAIN_CHECK_O)
fclean: clean
	rm -f $(NAME_PS)
	rm -f $(NAME_CHECK)

re: fclean all

%.o : %.c quiz.h srcs/get_next_line.h
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@