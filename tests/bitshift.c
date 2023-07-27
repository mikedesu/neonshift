#include <ncurses.h>

char	to_binary(char *str){
unsigned char	b = 0, pow;

for (int i=0; i<8; i++){
	if (str[i] == '1')
		{pow = 1; for (int j=0; j<i; j++) pow*=2;
		b += pow;}
}
return b;}

int	main(int ac, char **av){
initscr(); noecho(); curs_set(0);
cbreak(); //nodelay(stdscr, TRUE);

unsigned char	mov_mod;

mov_mod = to_binary("10110100");

printw("%i: R%i V%i H%i J%i K%i L%i\n", mov_mod, mov_mod&1, (mov_mod&2)>>1, (mov_mod&4)>>2, (mov_mod&8)>>3,
		(mov_mod&16)>>4, (mov_mod&32)>>5); refresh();
//printw("%i: R%i V%i H%i J%i K%i L%i\n", mov_mod, mov_mod&2, mov_mods%4); refresh();

getch(); endwin(); return 0;}
