#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include "stdlib.h"
#define BulletNum 15
#define EnemyNum 10

//保存图片
IMAGE bk;
IMAGE image_gamer[2];
IMAGE image_bullet[2];
IMAGE Enemy[2][2];

enum My
{

	WIDTH= 475,
	HEIGHT = 697,
	BIG,
	SMALL

};

//按键控制
//玩家数据结构体
struct plane 
{
	int x;
	int y;
	bool live;
	int width;
	int height;
	int hp;
	int type;

}player, bullet[BulletNum], enemy[EnemyNum];

//子弹移动函数
void BulletMove()
{
	for (int i=0; i < BulletNum; i++)
	{
		if (bullet[i].live)
		{
			bullet[i].y -= 1;
			if (bullet[i].y < 0)
			{
				bullet[i].live = false;
			}
		}
	}
}

//敌机血量函数
void Enemyhp(int i)

{
	if (rand() % 10==0)//0-9
	{
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 69;
		enemy[i].height = 95;
	}
	else 
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 57;
		enemy[i].height = 43;
	}
}

//初始化游戏
void Initgame()
{
	player.x = WIDTH / 2 - 50;
	player.y = HEIGHT - 120;
	player.live = true;
	//初始化子弹
	for (int i = 0;i < BulletNum; i++)
	{
		
		bullet[i].x = 0;
		bullet[i].y = 0;
		bullet[i].live = false;
	}
	//初始化敌机
	for (int i = 0; i < EnemyNum; i++)
	{
		enemy[i].x;
		enemy[i].y;
		enemy[i].live = false;
		Enemyhp(i);
	}
	enemy[1].x = 50;
	enemy[1].y = 50;
	enemy[1].live = true;
}

/*void CreateEnemy()
{
	for (int i = 0; i < EnemyNum; i++)
	{
		if (!enemy[i].live )

	}
}*/

void CreateBullet()
{
	for (int i = 0; i < BulletNum; i++)
	{
		if (!bullet[i].live)
		{
			bullet[i].x = player.x + 50;
			bullet[i].y = player.y;
			bullet[i].live = true;
			break;
		}
	}
}

void keycontrol(int speed)
{
#if 0

	//先判断是否有按键，有了按键后才能移动
	//kbhit函数需要包含头文件 C++语言包含头文件： include <conio.h>。
	if(_kbhit())
		switch (_getch())
		{
		case 'w':
		case 'W':
			player.y -= speed;
			break;
		case 'a':
		case 'A':
			player.x -= speed; break;
		case 'S':
		case 's':
			player.y += speed; break;
		case 'd':
		case 'D':
			player.x += speed; break;

		}
#elif 1//2 要是用windows 函数获取键盘输入getasynckeystate //非阻塞函数 ，  会非常的流畅
	//如果要用字母必须要写大写  小写检测不了
	if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'))
	{
		if (player.y > 0)
		{
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN)||GetAsyncKeyState('S'))
	{
		if (player.y < HEIGHT - 120)
		{
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState('A'))
	{
		if (player.x +50> 0)
		{
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState('D'))
	{
		if (player.x -50< WIDTH - 100)
		{
			player.x += speed;
		}
	}
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 250)
	{
		CreateBullet();
		t1 = t2;
	}
	t2 = GetTickCount();
#endif //0	
}

//图形库加载函数
void LoadImage()
{
	//加载475*697背景
	loadimage(&bk,"./images/background.png");//可能报错，因为字符集不对  unicode   into   多字节字符集
	loadimage(&image_gamer[0],"./images/plane1.png");
	loadimage(&image_gamer[1],"./images/plane2.png");
	loadimage(&image_bullet[0], "./images/bullet1.png");
	loadimage(&image_bullet[1], "./images/bullet2.png");
	//加载敌机图片
	loadimage(&Enemy[0][0], "./images/enemy1.png");
	loadimage(&Enemy[0][1], "./images/Enemy_2.png");
	loadimage(&Enemy[1][0], "./images/enemy2.png");
	loadimage(&Enemy[1][1], "./images/Enemy_1.png");
}

//游戏图像绘制函数
void GameDraw()
{	
	
	//加载背景图片
	LoadImage();
	putimage(0, 0, &bk);
	putimage(player.x, player.y, &image_gamer[0], NOTSRCERASE);
	putimage(player.x, player.y, &image_gamer[1], SRCINVERT);
	for (int i = 0; i < BulletNum; i++)
	{
		if (bullet[i].live)
		{
			putimage(bullet[i].x, bullet[i].y, &image_bullet[0], NOTSRCERASE);
			putimage(bullet[i].x, bullet[i].y, &image_bullet[1], SRCINVERT);
		}
	}
	//绘制敌机
	for (int i = 0; i < EnemyNum; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BIG)
			{
				putimage(enemy[i].x, enemy[i].y, &Enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &Enemy[0][1], SRCINVERT);
			}
			else
			{
				putimage(enemy[i].x, enemy[i].y, &Enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &Enemy[1][1], SRCINVERT);
			}
		
		}
	}
}


int main()
{
	//create a 475*697 windows  创建窗口

	initgraph(WIDTH,HEIGHT,0);
	BeginBatchDraw();
	Initgame();
	while (1)
	{
		GameDraw();
		FlushBatchDraw();
		keycontrol(5);
		BulletMove();

	}
	EndBatchDraw();
	return 0;
}