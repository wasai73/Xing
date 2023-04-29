#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#pragma comment(lib,"Winmm.lib")

using namespace std;

#define Width 1080
#define High 840

int Character_x, Character_y;
int Character_direction;
int i, j;
int bg[18][14];
int gameStatus = 0;

IMAGE img_zheng1, img_zheng11,
      img_zuo1, img_zuo11,
	  img_you1, img_you11,
	  img_bei1, img_bei11,
	  img_xiaowu1,img_xiaowu11,
	  img_bk,img_chushi,img_jinru,img_tuichu,
	  img_logo,img_logo1;

void startmenu();
void startup()
{
	initgraph(Width, High);
	loadimage(&img_bk, _T("D:\\background.png"));
	loadimage(&img_bei1, _T("D:\\beimian1.png"));
	loadimage(&img_bei11, _T("D:\\beimian11.png"));
	loadimage(&img_you1, _T("D:\\xiangyou1.png"));
	loadimage(&img_you11, _T("D:\\xiangyou11.png"));
	loadimage(&img_zuo1, _T("D:\\xiangzuo1.png"));
	loadimage(&img_zuo11, _T("D:\\xiangzuo11.png"));
	loadimage(&img_zheng1, _T("D:\\zhengmian1.png"));
	loadimage(&img_zheng11, _T("D:\\zhengmian11.png"));
	loadimage(&img_xiaowu1, _T("D:\\xiaowu.png"));
	loadimage(&img_xiaowu11, _T("D:\\xiaowu1.png"));
	loadimage(&img_chushi, _T("D:\\±³¾°.png"));
	loadimage(&img_jinru, _T("D:\\´´½¨.jpg"));
	loadimage(&img_tuichu, _T("D:\\ÍË³ö.jpg"));
	loadimage(&img_logo, _T("D:\\logo.png"));
	loadimage(&img_logo1, _T("D:\\logo1.png"));

	Character_x = Width / 2;
	Character_y = High / 2;
	Character_direction = 0;
	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 14; j++)
		{
			bg[i][j] = 0;
		}
	}
	BeginBatchDraw();

	mciSendString("open D:\\backmusic.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	while (gameStatus == 0)
	{
		startmenu();
	}
}

void startmenu()
{
	putimage(-200, 0, &img_chushi);
	putimage(250, 50, &img_logo1, NOTSRCERASE);
	putimage(250, 50, &img_logo, SRCINVERT);
	putimage(300, 600, &img_jinru);
	putimage(600, 600, &img_tuichu);
	FlushBatchDraw();
	Sleep(2);

	MOUSEMSG m;
	if (MouseHit())
	{
		m = GetMouseMsg();
		if ((m.x >= 300) && (m.x <= 508) && (m.y >= 600) && (m.y <= 762) && (m.uMsg == WM_LBUTTONDOWN))
		{
			gameStatus = 1;
		}
		else if ((m.x >= 600) && (m.x <= 514) && (m.y >= 600) && (m.y <= 760) && (m.uMsg == WM_LBUTTONDOWN))
		{
			gameStatus = 2;
			exit(0);
		}
	}
}
void show()
{
	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (bg[i][j] == 0)
			{
				putimage(i * 60, j * 60, &img_bk);
			}
		}
	}
	putimage(840, 0, &img_xiaowu11, NOTSRCERASE);
	putimage(840, 0, &img_xiaowu1, SRCINVERT);
	if (Character_direction == 0)
	{
		putimage(Character_x, Character_y, &img_zheng11, NOTSRCERASE);
		putimage(Character_x, Character_y, &img_zheng1, SRCINVERT);
	}
	else if (Character_direction == 1)
	{
		putimage(Character_x, Character_y, &img_bei11, NOTSRCERASE);
		putimage(Character_x, Character_y, &img_bei1, SRCINVERT);
	}
	else if (Character_direction == 2)
	{
		putimage(Character_x, Character_y, &img_you11, NOTSRCERASE);
		putimage(Character_x, Character_y, &img_you1, SRCINVERT);
	}
	else if (Character_direction == 3)
	{
		putimage(Character_x, Character_y, &img_zuo11, NOTSRCERASE);
		putimage(Character_x, Character_y, &img_zuo1, SRCINVERT);
	}
	FlushBatchDraw();
	Sleep(50);
}

void updateWithoutInput()
{

}

void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'a')
		{
			if (Character_x > 0)
			{
				Character_x -= 10;
			}
			else
			{
				Character_x = Character_x;
			}
			Character_direction = 3;
		}
		if (input == 'd')
		{
			if (Character_x < Width)
			{
				Character_x += 10;
			}
			else
			{
				Character_x = Character_x;
			}
			Character_direction = 2;
		}
		if (input == 'w')
		{
			if (Character_y > 0)
			{
				Character_y -= 10;
			}
			else
			{
				Character_y = Character_y;
			}
			Character_direction = 1;
		}
		if (input == 's')
		{
			if (Character_y < High)
			{
				Character_y += 10;
			}
			else
			{
				Character_y = Character_y;
			}
			Character_direction = 0;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}
int main()
{
	startup();
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();
	return 0;
}