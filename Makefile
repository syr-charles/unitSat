NAME 	= 	unitSat

SRCS 	= 	main.c \
			solver.c \
			unitpropagate.c \
			stack.c \
			makeproblem.c \
			killproblem.c \
			merge.c 


OBJS 	= 	${SRCS:.c=.o}

%.o:%.c		
		gcc -Wall -Wextra -Werror -c $< -o $@

${NAME}:
		gcc -g -Wall -Wextra -Werror srcs/*.c -o ${NAME}

all:		${NAME}

clean:

fclean:		clean		
		rm -f ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
