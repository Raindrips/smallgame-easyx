#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <easyx.h>
#include <time.h>

int map[4];//地图
int n;        //统计消除的数量

void init()
{
  for (int i = 0; i < 4; i++)
  {
	map[i] = rand() % 4;
  }
  n = 0;
}

bool play()//鼠标消息获取   bool类型  c++的 返回0（假）或1（真）
{
  MOUSEMSG msg = GetMouseMsg();//鼠标消息初始化
  switch (msg.uMsg)
  {
  case WM_LBUTTONDOWN:
	int x = msg.y / 120;//竖
	int y = msg.x / 100;//横
	//获取鼠标点下去的位子
	if (map[3] == y && 3 == x)//判断点的是不是最下面一行 如果点的是不最下面一行会直接结束游戏
	{
	  for (int i = 3; i > 0; i--)
	  {
		map[i] = map[i - 1];//把上面一行的数给下面赋值
	  }
	  map[0] = rand() % 4;
	  n++;//用来记录消除的个数
	}
	else
	  return true;//返回真
	break;
  }
  return false;//返回假
}

void drawMap()//贴图
{
  BeginBatchDraw();//开始批量绘图
  cleardevice();
  /*设置背景*/
  setlinecolor(RGB(255, 0, 0));//当前画线的颜色     红色
  setfillcolor(RGB(255, 255, 255));//当前颜色的填充色    白色
  for (int i = 0; i < 4; i++)
  {
	for (int j = 0; j < 4; j++)
	{
	  fillrectangle(j * 100, i * 120, (j + 1) * 100, (i + 1) * 120);//有边框的矩形
	}
  }
  /*设置方块的颜色*/
  setfillcolor(RGB(0, 0, 0));//黑色
  for (int i = 0; i < 4; i++)
  {
	fillrectangle(map[i] * 100, i * 120, (map[i] + 1) * 100, (i + 1) * 120);
  }
  EndBatchDraw();//结束批量绘图
}

int main()
{
  //创建窗口
  initgraph(4 * 100, 4 * 120);//初始化窗口
  srand((unsigned)time(NULL));//随机数种子
  init();//初始化游戏
  while (1)
  {
	drawMap();
	if (play() == true)
	{
	  TCHAR strBuff[128];
	  swprintf(strBuff, L"总共消除的了%d个方块", n);
	  MessageBox(GetHWnd(), strBuff, L"游戏结束", MB_OK);
	  break;
	}
  }
  //关闭窗口
  closegraph();
  return 0;
}