#include <ncurses.h>

#define MR 1
#define MV 2
#define MH 4
#define MJ 8
#define MK 16
#define ML 32
#define fto1(x) ((x)?1:0)
#define F(x, y) fto1(x&y)
#define R(x) fto1(x&MR)
#define V(x) fto1(x&MV)
#define H(x) fto1(x&MH)
#define J(x) fto1(x&MJ)
#define K(x) fto1(x&MK)
#define L(x) fto1(x&ML)
#define setf(x, y) x|y
#define unsetf(x, y) x&~y
#define switchf(x,y) (F(x,y)?unsetf(x,y):setf(x,y))

unsigned char	to_binary(char *str){
unsigned char	b = 0, pow;
for (int i=0; i<8; i++){
	if (str[i] == '1'){ pow = 1;
		for (int j=0; j<i; j++) pow*=2;
		b += pow;}} return b;}

unsigned char	to_binary2(char *str){
unsigned char	b = 0;
for (int i=0; i<8; i++){
	if (str[7-i] == '1') b++;
	if (i!=7) b = b<<1;} return b;}

void	print_mov_mod(unsigned char mf){
//printw("%i: R%i V%i H%i J%i K%i L%i\n", mov_mod, mov_mod&1, (mov_mod&2)>>1, (mov_mod&4)>>2, (mov_mod&8)>>3,
//		(mov_mod&16)>>4, (mov_mod&32)>>5); refresh();
//printw("%i: R%i V%i H%i J%i K%i L%i\n", mov_mod, mov_mod&2, mov_mods%4); refresh();
printw("%i: R%i V%i H%i J%i K%i L%i\n",
	mf, R(mf), V(mf), F(mf, MH), J(mf), K(mf), L(mf));
//fto1(mflags&R));
return;}


int	main(int ac, char **av){
initscr(); noecho(); curs_set(0);
cbreak(); //nodelay(stdscr, TRUE);

unsigned char	mov_mod;
char	c;

mov_mod = to_binary2("11110100");

// === PRINTING ===
print_mov_mod(mov_mod);

// === KEY INPUT ===
while ((c=getch())!='q'){ switch(c){
	case 'r':
		mov_mod = switchf(mov_mod, MR);
		print_mov_mod(mov_mod);
		break;
	default: break;}}

refresh();

//getch();
endwin(); return 0;}
