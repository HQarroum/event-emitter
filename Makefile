examples:
	$(MAKE) -C examples/

tests:
	$(MAKE) -C examples/ run

all: tests examples

clean:
	$(MAKE) -C examples/ clean

fclean:
	$(MAKE) -C examples/ fclean

re: fclean all

.PHONY: all examples tests fclean
