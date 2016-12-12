#include	<curses.h>
#include	<sys/ioctl.h>
#include	<string.h>

#define KEYBAR "_______________________________"
#define BLANK  "                               "

typedef struct {
	char str[25];
	int x;
	int y;
} WORD;

void drawBoard();
void drawMenu();
void printWord(WORD word);
void clearWord(WORD word[],char buf[]);


struct winsize *getSize();
char *wordset[] = {"apple", "banana", "kiwi","cloud","football","zokbal","messy","over","watch","league", "chicken", "happy", "pizza"};

int main(void) {
	char ch;
	WORD word[13];
	int i = 25;
	char buf[20]={'0'};

	for(i=0; i<13; i++) {
		strcpy(word[i].str,wordset[i]);
		word[i].x = 15 + (i%3) * 20;
		word[i].y = 3 + (i/3)*2;	
	} 
	i=25;	
	drawMenu();
	for(i=0;i<13;i++)
		printWord(word[i]);
	move(17,25);
	refresh();
	while(ch = getchar()) {
		if(ch==127) {
			if(i>25) {
				move(17,i-1);
				addch(' ');
				move(17,i-1);
				i--;
			}
		} else if (ch==' ') {
			buf[i-25]='\0';
			clearWord(word,buf);
			move(17,25);
			i=25;
			addstr(BLANK);
			move(17,25);
		} else if(i<56){
			buf[i-25]=ch;
			addch(ch); 
			i++;
		}
		refresh();
	}
	endwin();
}

void clearWord(WORD word[],char buf[]) {
	int i;
	for(i=0;i<13;i++){
		if(strcmp(buf,word[i].str)==0){
			move(word[i].y,word[i].x);
			addstr("          ");
		}
	}
}
void printWord(WORD word) {
	move(word.y,word.x);
	addstr(word.str);
	refresh();
}
struct winsize *getSize() {
	static struct winsize wbuf;
	if(ioctl(0,TIOCGWINSZ, &wbuf)!=-1) 	return &wbuf;
	else					return 0;
}

void drawMenu() {
	drawBoard();
	move(18,25);
	addstr(KEYBAR);
	refresh();
}

void drawBoard() {
	int i;
	initscr();
	
	for(i=0;i<getSize()->ws_col;i++)
		if(i%2==0)	addstr("*");
		else		addstr(" ");
	for(i=1;i<getSize()->ws_row-1;i++) {
		move(i,0);
		addstr("*");
		move(i,getSize()->ws_col-1);
		addstr("*");
	}
	for(i=0;i<getSize()->ws_col;i++)
		if(i%2==0)	addstr("*");
		else		addstr(" ");	
}
