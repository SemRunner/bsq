NAME = bsq
COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -O3 -c
FLAGS1 = -c -O3
SOURCES_DIR = srcs/
SOURCES = bsq_calc_1.c bsq_calc_2.c bsq_error.c buffer.c input1.c main.c str_func.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = includes

all: $(NAME)

$(NAME):
	$(COMPILER) $(FLAGS) $(addprefix $(SOURCES_DIR), $(SOURCES)) -I $(HEADERS)
	$(COMPILER) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
