#include <ncurses.h>

int	main(int ac, char **av){
initscr(); // = NCURSES INIT ===
cbreak(); noecho();
//nodelay(stdscr, TRUE);
//curs_set(0);
start_color(); // ==============

printw("hello\n");
refresh();
getch();

endwin();
return 0;}
