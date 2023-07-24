#include <ncurses.h>

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak();
noecho();
//nodelay(stdscr, TRUE);
curs_set(0); // ================

refresh();
WINDOW	*win = newwin(22, 72, 3, 7);
box(win, 0, 0);
wrefresh(win);
getch();
delwin(win);

win = newwin(20, 70, 4, 8);


delwin(win);
endwin();
return 0;}
