#include	<curses.h>
#include	<sys/ioctl.h>
#include	<string.h>
#include	<sys/time.h>
#include	<signal.h>
#include	<stdlib.h>
#include        <unistd.h>
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
int ticker(int );
void timer();
void timercount(); 
void MenuScreen();
void menuItem();
int minute=60;
struct winsize *getSize();
char *wordset[] = {"apple", "banana", "kiwi","cloud","football","zokbal","messy","over","watch","league", "chicken", "happy", "pizza"};

int main(void) {
	char ch;
	WORD word[13];
	int i = 25;
	char buf[20]={'0'};
	MenuScreen();
	timer();
	for(i=0; i<13; i++) {
		strcpy(word[i].str,wordset[i]);
		word[i].x = 15 + (i%3) * 20;
		word[i].y = 3 + (i/3)*2;	
	} 
	i=25;	
	drawMenu();
	for(i=0;i<13;i++)
		printWord(word[i]);
//	move(17,25);
//	refresh();
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
//	initscr();
	
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


int ticker(int n_msecs){
struct itimerval new_timeset;
long n_sec,n_usecs;
n_sec=n_msecs/1000;
n_usecs=(n_msecs %1000) *1000L;
new_timeset.it_interval.tv_sec = n_sec;
new_timeset.it_interval.tv_usec = n_usecs;
new_timeset.it_value.tv_sec = n_sec;
new_timeset.it_value.tv_usec = n_usecs;
return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

void timer() {
        signal(SIGALRM,timercount);
        if(ticker(100)==-1)
                perror("set_ticker");
}

void timercount() {
        char c[10];
        move(2,60);
        addstr("  ");
        move(2,60);
        minute--;
	if(minute==0)
	{
	clear();
	endwin();
	exit(0);
	}
        sprintf(c, "%d", minute);
        //addstr("aa");
        addstr(c);
        refresh();

}
void MenuScreen() {
        char ch;
        initscr();
        drawBoard();
        menuItem();
        move(14,44);
        refresh();
        while(ch=getchar()){
                if(ch=='1') {
                        clear();
                        break;
                }
                else if(ch=='2') {
                        clear();
                        endwin();
                        exit(0);

                }
        }

}
void menuItem() {
        move(10,20);
        addstr("1.game start");
        move(12,20);
        addstr("2.game exit");
        move(14,20);
        addstr("please typing word : (     ) ");

}
