NAME = philo

LIST =			main.c death.c struct.c utils.c libft.c

OBJ = $(patsubst %.c,%.o,$(LIST))

D_FILES = $(patsubst %.c,%.d,$(LIST))

OTPFLAGS = -O2

FLAGS = -Wall -Wextra -Werror

all :	$(NAME)

$(NAME) :	$(OBJ)
	gcc $(FLAGS) $(OPTFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	gcc $(FLAGS) $(OPTFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean :
	rm -f $(OBJ) $(D_FILES)

fclean : clean
	rm -f $(NAME) $(D_FILES)

re : fclean all

.PHONY : all clean fclean re