CC = g++

APP_NAME = example

OUTPUT_FILE = example_output.txt

SRC = main.cpp

CFLAGS = -std=c++11 -I../../includes -W -Wall -Werror

OBJ = $(SRC:.c=.o)

assert = $(if $(filter whatever,${CROSS_COMPILE}),$(if ${VARIABLE},,$(error Urk! Variable problem)))

%.o: %.c
	$(CC) -o $@ -c $<

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(APP_NAME) $^

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(APP_NAME) $(OUTPUT_FILE)

run: all
	$(shell ./$(APP_NAME) > $(OUTPUT_FILE))

test: run
	${assert}diff $(OUTPUT_FILE) output.txt

.PHONY: clean fclean re run
