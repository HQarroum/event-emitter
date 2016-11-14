examples:
	$(MAKE) -C examples/

test:
	$(MAKE) -C examples/ test

all: tests examples

clean:
	$(MAKE) -C examples/ clean

fclean:
	$(MAKE) -C examples/ fclean

re: fclean all

.PHONY: all examples tests fclean
