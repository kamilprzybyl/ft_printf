CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

$(NAME): all
 
all:
	@make -C libft 									# go to libft directory and do make 
	@$(CC) -c $(CFLAGS) *.c							# compile *.c 
	@ar -rc $(NAME) *.o								# create a static library
	@echo "\033[32m$(NAME) built!\033[0m" 			# print "built" in green

test:
	@$(CC) test.c -L. libft/libft.a $(NAME)			# compile test.c
	@./a.out 
	
clean:
	@make -C libft clean							# do clean in libft
	@rm *.o

fclean:
	@make -C libft fclean							# do fclean in libft
	@rm $(NAME) a.out *.o

re: fclean all

.PHONY: all clean fclean re