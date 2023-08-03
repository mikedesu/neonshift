all:
	gcc -o neonshift src/main.c src/modes.c -Isrc -lncurses
