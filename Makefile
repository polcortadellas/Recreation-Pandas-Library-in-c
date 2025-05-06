##
## EPITECH PROJECT, 2024
## G-AIA-200: Cuddle
## File description:
## Makefile
##

SRC =   src/df_read_csv.c \
	src/df_info.c \
	src/df_write.c \
	src/df_get_value.c \
	src/df_get_values.c \
	src/df_get_unique_values.c \
	src/df_tail.c \
	src/utils/dataframe_utils.c \
	src/utils/types.c \
	src/utils/tail_utils.c \
	src/df_write.c \
	src/df_apply.c \
	src/df_shape.c \
	src/utils/csv_line.c \
	src/df_describe.c \
	src/df_head.c \
	src/utils/head_utils.c \
	src/df_filter.c \
	src/df_free.c

FUNC = main.c

OBJ = $(SRC:.c=.o)

NAME = libcuddle.a
TESTS = tests/unit/test_df_get_value.c \
	tests/unit/test_df_get_values.c \
	tests/utils/df_mocking.c \
	src/df_get_value.c \
	src/df_get_values.c

TESTS_OBJ = $(TESTS:.c=.o)
TESTS_NAME = unit_tests
TESTS_LIBS = -lcriterion --coverage


all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	rm -f $(OBJ)
	cp include/cuddle.h include/dataframe.h
	echo -e "\033[3;34m\nLibrary of $(NAME) compiled successfully.\033[0m"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	gcc $(FUNC) -lcuddle -L ./ -g3 -lm
	rm -f $(OBJ)
	echo -e "\033[3;34m\nTest of $(NAME) compiled successfully.\033[0m"

tests_run: $(TESTS_OBJ)
	gcc $(TESTS_OBJ) $(TESTS_LIBS) -o $(TESTS_NAME)
	./$(TESTS_NAME)
	echo -e "\033[0;36mTests executed successfully.\033[0m"
