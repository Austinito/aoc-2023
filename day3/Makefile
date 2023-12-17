NAME = day3.o
SRC = day3.c
CFLAGS = -Wall -Wextra -Werror
INPUT = inputFile
TEST_INPUT = testInput

compileAndTest: compile test

compileAndRun: compile run

compile:
	@gcc -o $(NAME) $(SRC) $(CFLAGS)

test:
	@./$(NAME) $(TEST_INPUT)

run:
	@./$(NAME) $(INPUT)

clean:
	@rm -f $(NAME)
