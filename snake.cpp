#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string>
using namespace std;
class Snake
{
private:
	struct Node
	{
		int x;
		int y;
		Node *next;
		Node(int x1,int y1,Node *p=NULL)
		{
			x=x1;
			y=y1;
			next=p;
		}
		Node(Node *p=NULL)
		{
			next=p;
		}
	};
	Node *head;
	Node *tail;
	int length;
public:
	int food_x;
	int food_y;
	int y_run;
	int x_run;
	int tail_x;
	int tail_y;
	int t;
	int r,g,b;
	int score;
	bool isx;
	bool isy;
	bool iseat;
	bool isrepeat;
	int repeat_x;
	int repeat_y;
	char ch;
	char p_c;
	int level;
	bool ispause;
	HWND hWnd;

	void UI();
	bool repeat();
	void Init(int width,int height);
	void _map(int width,int height,int w);
	void snake_init(int x,int y,int w);
	void snake_move();
	bool snake_death();
	void snake_eat();
	void food();
	void keydown();

};
void Snake::Init(int width,int height)
{
	ch='d';
	hWnd = GetHWnd();
	level=300;
	ispause=false;
	x_run=0;
	y_run=-20;
	food_x=210;
	food_y=210;
	score=0;
	isrepeat=false;
	t=0;
	iseat=false;
	isx=true;
	isy=false;
	length=0;
	head=tail=new Node();
	MessageBox(hWnd, L"STAR", L"GAME STAR", MB_OK);
	initgraph(width,height);
}
void Snake::_map(int width,int height,int w)
{
	for(int i=0;i<width/w;i++)
	{
		for(int j=0;j<height/w;j++)
		{
			if(i==0||j==0||j==height/w-1||i==width/w-1)
			{
				setfillcolor(YELLOW);
				solidrectangle(i*w,j*w,(i+1)*w,(j+1)*w);
			}
		}
	}
}
void Snake::snake_init(int x,int y,int w)
{
	Node *p;
	for(int i=0;i<5;i++)
	{
		p=new Node(x,y+i*w,NULL);
		tail->next=p;
		tail=p;
		solidcircle(p->x,p->y,8);
		length++;
	}
}
void Snake::snake_move()
{
	int x,y;
	while(snake_death()!=true)
	{
		snake_eat();
		UI();
		food();
		Node *p=head;


		double start=clock();
		while ((clock() - start)<level);//一秒后自动读取 或者直接有键入 
		{
			start = clock();
		}
		keydown();
		r=255;
		b=0;
		g=255;
		while(1)
		{
			if(p==head->next)
			{
				x=p->x;
				y=p->y;
				p->x+=x_run;
				p->y+=y_run;
				setfillcolor(RGB(r,g,b));
				solidcircle(p->x,p->y,8);
			}
			if(p->next==NULL)
			{
				clearcircle(p->x,p->y,9);
				break;
			}
			p=p->next;
			if(g!=0)
				g-=20;
			setfillcolor(RGB(r,g,b));
			solidcircle(p->x,p->y,8);

		}

		Node *q=head->next->next;
		while(q!=NULL)
		{
			int x1=x;int y1=y;
			x=q->x;y=q->y;
			q->x=x1;q->y=y1;
			repeat_x=x;repeat_y=y;
			tail_x=x;tail_y=y;
			q=q->next;
		}
		repeat();

	}

}	
bool Snake::snake_death()
{
	Node *p=head->next;
	int x2,y2;
	x2=p->x;
	y2=p->y;
	if(p->x>=580||p->y>=580||p->x<=20||p->y<=20)
	{
		x_run=0;
		y_run=0;
		t=1;

	}
	while(1)
	{	
		p=p->next;
		if(p->x==x2&&p->y==y2)
		{	
			t=1;
			break;
		}
		if(p->next==NULL)
			break;
	}
	if(t==1)
	{
		MessageBox(hWnd, L"GAME OVER!", L"Death", MB_OK);
		outtextxy(650,500,L"Death!");
		outtextxy(610,550,L"Anykey to close the graph!");
		_getch();
		closegraph();
		return true;
	}
	else
	{
		outtextxy(650,500,L"Life! ");
		return false;
	}
}
void Snake::snake_eat()
{
	Node *p=head->next;
	if(p->x==food_x&&p->y==food_y)
	{
		iseat=true;
		score+=10;
		level-=10;
		Node *p1=head->next;
			Node *p2;
			while(1)
			{
				if(p1->next==NULL)
				{
					break;
				}
				p1=p1->next;
			}
			p2=new Node(tail_x,tail_y,NULL);
			p1->next=p2;
			length++;
	}
	else
	{
		iseat=false;
	}

}
void Snake::food()
{
	if(iseat==false)
	{
		setfillcolor(WHITE);
		solidcircle(food_x,food_y,5);
		setfillcolor(YELLOW);
	}
	if(iseat==true)
	{
		food_x=(rand()%(28-2+1)+1)*20+10;
		food_y=(rand()%(28-2+1)+1)*20+10;
		while(food_x==head->next->x&&food_y==head->next->y)
		{
			food_x=(rand()%(28-2+1)+1)*20+10;
			food_y=(rand()%(28-2+1)+1)*20+10;
		}

	}
}
bool Snake::repeat()
{
	Node *p=head->next;
	int x=p->x;
	int y=p->y;
	if(x==repeat_x&&y==repeat_y)
	{
		setfillcolor(RGB(255,255,0));
		solidcircle(x,y,8);
		return true;
	}
	else
		return false;
}
void Snake::UI()
{
	TCHAR s[5];
	_stprintf(s, _T("%d"), score); 
	outtextxy(650,20,L"Score:");
	if(level>200)
		outtextxy(650,60,L"Level:Very simple");
	if(level<=200)
		outtextxy(650,60,L"Level:Easy            ");
	if(level<=100)
		outtextxy(650,60,L"Level:Difficult       ");
	if(level<=50)
		outtextxy(650,60,L"Level:Hell            ");
	outtextxy(700,20,s);
}
void Snake::keydown()
{
	if(x_run==0)
	{
		isx=true;
		isy=false;
	}
	if(y_run==0)
	{
		isy=true;
		isx=false;
	}
	if(kbhit())
	{
		ch=getch();
	}
	if(ch=='w'&&isy==true)
	{
		x_run=0;
		y_run=-20;
		p_c=ch;
	}
	if(ch=='s'&&isy==true)
	{
		x_run=0;
		y_run=20;
		p_c=ch;
	}
	if(ch=='a'&&isx==true)
	{
		x_run=-20;
		y_run=0;
		p_c=ch;
	}
	if(ch=='d'&&isx==true)
	{
		x_run=20;
		y_run=0;
		p_c=ch;
	}
	if(ch==' ')
	{
		outtextxy(650,100,L"Pause!");
		ch=getch();
		while(1)
		{
			if(ch==' ')
			{
				ch=p_c;
				outtextxy(650,100,L"Start!   ");
				break;
			}
			else
			{
				ch=getch();
			}
		}
	}
}


int main()
{
	Snake s;
	s.Init(800,600);
	s._map(600,600,20);
	s.snake_init(110,210,20);
	s.snake_move();
	return 0;
}