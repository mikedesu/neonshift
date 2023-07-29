#include <ncurses.h>
#include "../struct.h"

unsigned char	to_binary(char *str);
unsigned char	to_binary2(char *str);
void	print_mov_mod(unsigned char mf);
void	print_edt_mod(unsigned char ef);
void	print_mov_v(struct vect v);

#define MV 1
#define MR 2
#define MP 4
#define MH 8
#define MJ 16
#define MK 32
#define ML 64
#define EZ 1
#define E1 2
#define EI 4

#define fto1(x) ((x)?1:0)
#define F(x, y) fto1(x&y)
#define V(x) fto1(x&MV)
#define R(x) fto1(x&MR)
#define P(x) fto1(x&MP)
#define H(x) fto1(x&MH)
#define J(x) fto1(x&MJ)
#define K(x) fto1(x&MK)
#define L(x) fto1(x&ML)
#define Z(x) fto1(x&EZ)
#define O(x) fto1(x&E1)
#define I(x) fto1(x&EI)

#define setf(x, y) x|y
#define unsetf(x, y) x&~y
#define switchf(x,y) (F(x,y)?unsetf(x,y):setf(x,y))

struct vect	get_mov_v(unsigned char *mov_mod){
struct vect	v;
	if (H(*mov_mod)){
		switchf(*mov_mod, MH);
		v.y = 0; v.x = -1;}
	else if (J(*mov_mod)){
		switchf(*mov_mod, MJ);
		v.y = 1; v.x = 0;}
	else if (K(*mov_mod)){
		switchf(*mov_mod, MK);
		v.y = -1; v.x = 0;}
	else if (L(*mov_mod)){
		switchf(*mov_mod, ML);
		v.y = 0; v.x = 1;}
	else if (P(*mov_mod)){
		v.y = 0; v.x = 0;}
	else if (!V(*mov_mod) && !R(*mov_mod)){
		v.y = 0; v.x = 1;}
	else if (!V(*mov_mod) && R(*mov_mod)){
		v.y = 0; v.x = -1;}
	else if (V(*mov_mod) && !R(*mov_mod)){
		v.y = 1; v.x = 0;}
	else if (V(*mov_mod) && R(*mov_mod)){
		v.y = -1; v.x = 0;}
return v;}


int	main(int ac, char **av){
initscr(); noecho(); curs_set(0);
cbreak(); //nodelay(stdscr, TRUE);

unsigned char	mov_mod, edt_mod;
struct vect	mov_v;
char	c;

mov_mod = to_binary2("00000000");
edt_mod = to_binary2("00000000");

print_mov_mod(mov_mod);
print_edt_mod(edt_mod);

while ((c=getch())!='q'){ switch(c){
	case 'g': mov_mod = switchf(mov_mod, MV); break;
	case 'b': mov_mod = switchf(mov_mod, MR); break;
	case ' ': mov_mod = switchf(mov_mod, MP); break;
	case 'h': mov_mod = switchf(mov_mod, MH); break;
	case 'j': mov_mod = switchf(mov_mod, MJ); break;
	case 'k': mov_mod = switchf(mov_mod, MK); break;
	case 'l': mov_mod = switchf(mov_mod, ML); break;

	case 'z': edt_mod = switchf(edt_mod, EZ); break;
	case 'p': edt_mod = switchf(edt_mod, E1); break;
	case ';': edt_mod = switchf(edt_mod, EI); break;
	default: break;}

	mov_v = get_mov_v(&mov_mod);

	move(0, 0);
	print_mov_mod(mov_mod);
	print_edt_mod(edt_mod);
	print_mov_v(mov_v);
	refresh();
}

refresh();

//getch();
endwin(); return 0;}



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
printw("MF  %i:  V%i R%i P%i H%i J%i K%i L%i\t0\n",
	mf, V(mf), R(mf), P(mf), H(mf), J(mf), K(mf), L(mf));
//fto1(mflags&R));
return;}

void	print_edt_mod(unsigned char ef){
printw("EF  %i:  Z%i 1%i I%i\t\t0 0 0 0 0\n",
	ef, Z(ef), O(ef), I(ef));
return;}

void	print_mov_v(struct vect v){
printw("vector:  [%i;%i]\n", v.y, v.x);
return;}
