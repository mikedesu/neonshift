all:
	gcc -o neonshift main.c modes.c -lncurses


test_hello:
	gcc -o ./tests/test_hello ./tests/hello.c -lncurses

test_bitshift:
	gcc -o ./tests/test_bitshift ./tests/bitshift.c -lncurses
