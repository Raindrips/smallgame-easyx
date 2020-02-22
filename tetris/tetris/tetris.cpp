#include "tetris.h"

#include <time.h>
#include <conio.h>

const int G_SIZE = 20;
const int WIDTH = 10;
const int HEIGHT = 22;

//全局数组来表示游戏区域
short g_World[WIDTH][HEIGHT] = { 0 };

BlockInfo curB;/*当前格子*/
BlockInfo nextB;/*下一个格子*/

//所有格子的信息
Block g_Blocks[7] = {
  //{WORD,WORD,WORD,WORD,COLORREF}
  { 0x0F00, 0x4444, 0x0F00, 0x4444, RED },//I
  { 0x0660, 0x0660, 0x0660, 0x0660, YELLOW },//田
  { 0x4460, 0x02E0, 0x0622, 0x7400, BLUE },//L
  { 0x2260, 0x0E20, 0x0644, 0x4700, RED },//反L
  { 0xc600, 0x2640, 0xc600, 0x2640, BLUE },//Z
  { 0x3600, 0x4620, 0x3600, 0x4620, YELLOW },//反z
  { 0x4E00, 0X4C40, 0xE400, 0X4640, BLUE }//T
};

//初始话游戏
void loadGame() {
  //初始化窗口
  initgraph(640, 480);
  setbkmode(TRANSPARENT);//设置背景颜色为透明
  srand((unsigned)time(NULL));
}

//开始新游戏
void initGame() {
  setfillcolor(BLACK);//填充黑色  清空游戏区
  memset(g_World, 0, sizeof(g_World));  //初始化区域把值设置为0
  nextB.x = WIDTH + 1;
  nextB.y = HEIGHT - 1;
  newBlock();
}

//绘制单元格
void drawUnit(int x, int y, COLORREF co) {
  //计算单元方块的位置
  int left = x * G_SIZE;
  int right = (x + 1) * G_SIZE;
  int top = (HEIGHT - y - 1) * G_SIZE;
  int bottom = (HEIGHT - y) * G_SIZE;
  setfillcolor(co);
  setlinecolor(LIGHTGRAY);
  fillrectangle(left, top, right, bottom);//用于画填充矩形（有边框)
}

//绘制整体图形
void drawBlock(BlockInfo _block) {
  short b = g_Blocks[_block.id].dir[_block.style];
  //画 16个格子中的每一个
  for (int i = 0; i < 16; i++, b <<= 1) {
	if (b & 0x8000) {
	  int x = _block.x + i % 4;
	  int y = _block.y - i / 4;
	  if (y < HEIGHT) {
		//画一个小格子
		drawUnit(x, y, g_Blocks[_block.id].color);
	  }
	}
  }
}

//绘制UI界面
void drawGUI() {
  //显示文件
  setorigin(0, 0);
  settextstyle(14, 0, ("宋体"));
  outtextxy(20, 280, ("操作说明"));
  outtextxy(20, 300, ("上： 旋转"));
  outtextxy(20, 320, ("下： 下落"));
  outtextxy(20, 340, ("左： 左移"));
  outtextxy(20, 360, ("右： 右移"));
  outtextxy(20, 380, ("空格：快速下落"));
  outtextxy(20, 400, ("esc:退出程序"));
}

//所有绘制
void draw()
{
  BeginBatchDraw();
  cleardevice();
  //drawGUI();

  //设置坐标原点
  setorigin(220, 20);

  //绘制游戏区域
  rectangle(0, 0, WIDTH * G_SIZE, HEIGHT * G_SIZE + 1);

  //画右边矩形
  setfillcolor(BLACK);
  fillrectangle((WIDTH + 1) * G_SIZE, 0, (WIDTH + 5) * G_SIZE, 4 * G_SIZE);

  drawBlock(curB);
  drawBlock(nextB);

  for (int i = 0; i < WIDTH; i++)
  {
	for (int j = 0; j < HEIGHT; j++)
	{
	  if (g_World[i][j])
	  {
		drawUnit(i, j, DARKGRAY);
	  }
	}
  }
  EndBatchDraw();
}

//消除方块动画
void clearAnima(int y)
{
  //标记某一行即将发生消除操作的特性
  setfillcolor(LIGHTGREEN);//浅绿色
  setfillstyle(BS_HATCHED, HS_DIAGCROSS);//阴影线，水平垂直方向
  fillrectangle(0, (HEIGHT - y - 1) * G_SIZE + G_SIZE / 2 - 5, WIDTH * G_SIZE - 1, (HEIGHT - y - 1) * G_SIZE + G_SIZE / 2 + 5);
  setfillstyle(BS_SOLID);//实心画刷
  Sleep(300);
}

//生成新的图形
void newBlock() {
  curB = nextB;
  nextB.style = rand() % 4;
  nextB.id = rand() % 7;

  curB.x = WIDTH / 2 - 1;//中间位置
  curB.y = HEIGHT;

  WORD c = g_Blocks[curB.id].dir[curB.style];
  while ((c & 0x000F) == 0) {
	curB.y--;
	c >>= 4;
  }
}

clock_t m_oldTime = 0;   //初始化最开始的时间
void updata()
{
  clock_t newTime = clock();  //得到现在的时间
  if (newTime - m_oldTime > 500) {
	m_oldTime = newTime;
	onDown();
  }
}

//检测指定的方块是否可以移动
bool CheckMove(BlockInfo _block) {
  short b = g_Blocks[_block.id].dir[_block.style];
  int x, y;
  for (int i = 0; i < 16; i++, b <<= 1)
	if (b & 0x8000) {
	  x = _block.x + i % 4;
	  y = _block.y - i / 4;
	  if ((x < 0) || (x >= WIDTH) || y < 0)
		return false;
	  if ((y < HEIGHT) && g_World[x][y])
		return false;
	}
  return true;
}

//移动方块
void OnMove(int x, int y)
{
  BlockInfo temp = curB;    //当前图形信息保存在temp 
  temp.x += x;
  temp.y += y;
  if (CheckMove(temp)) {  //是否可以移动		
	curB.x += x;
	curB.y += y;
  }
}

//下落
void onDown() {
  BlockInfo temp = curB;    //当前图形信息保存在temp 
  temp.y--;
  if (CheckMove(temp)) {  //是否可以移动
	curB.y--;
  }
  else
  {
	fixed();  //不可以下移 
  }
}

//移动至底部
void moveBotton() {
  // 连续下移方块
  BlockInfo tmp = curB;
  tmp.y--;
  while (CheckMove(tmp))
  {
	curB.y--;
	tmp.y--;
  }
}

//  固定方块  
void fixed()
{
  int i, x, y;
  moveBotton();
  // 固定方块在游戏区
  short b = g_Blocks[curB.id].dir[curB.style];
  for (i = 0; i < 16; i++, b <<= 1)
	if (b & 0x8000)  //对十六个格子分别进行处理
	{
	  if (curB.y - i / 4 >= HEIGHT - 1)
	  {
		// 如果方块的固定位置超出高度，结束游戏
		gameOver();
		return;
	  }
	  g_World[curB.x + i % 4][curB.y - i / 4] = 1;
	}

  // 检查是否需要消掉行，并标记
  char remove = 0;	// 4 位用来标记方块涉及的 4 行是否有消除行为
  for (y = curB.y; y >= max(curB.y - 3, 0); y--)
  {

	for (i = 0; i < WIDTH && g_World[i][y] == 1; i++);

	if (i == WIDTH)
	{
	  remove |= (1 << (curB.y - y));
	  clearAnima(y);
	}
  }
  if (remove) //如果产生整行消除
  {
	for (i = 0; i < 4; i++, remove >>= 1)
	{
	  if (remove & 1)
	  {
		for (y = curB.y - i + 1; y < HEIGHT; y++)
		{
		  for (x = 0; x < WIDTH; x++)
		  {
			g_World[x][y - 1] = g_World[x][y];
			g_World[x][y] = 0;
		  }
		}
	  }
	}
  }
  //产生新方块
  newBlock();
}

//旋转方块
void onRotate() {

  BlockInfo tmp = curB;
  tmp.style = (tmp.style + 1) % 4;
  static int d[5] = { 0,1,2, -1,-2 }; //可以旋转的x的偏移量
  for (int i = 0; i < 5; i++)
  {
	tmp.x = curB.x + d[i];
	if (CheckMove(tmp))
	{
	  curB.style = (curB.style + 1) % 4;
	  curB.x += d[i];
	  return;
	}
  }
}

//判断是否按键
CMD getCmd() {
  if (_kbhit()) { //检测是否有点击消息
	switch (_getch())
	{
	case 'w':
	case 'W': return  RITATE;
	case 'a':
	case 'A': return  LEFT;
	case 'd':
	case 'D': return  RIGHT;
	case 's':
	case 'S': return  DOWN;
	case 27:return  QUIT;
	case ' ': return  SINK;
	case 0:
	case 0xE0:  //方向键
	  switch (_getch())
	  {
	  case 72: return RITATE;
	  case 75: return LEFT;
	  case 77: return RIGHT;
	  case 80: return DOWN;
	  }
	}
  }
  Sleep(16);
  return NO;
}

//判断游戏是否结束
void quit() {
  closegraph();
  exit(0);
}

//处理按键信息
void dispatch(enum CMD cmd) {
  switch (cmd)
  {
  case RITATE: onRotate();
	break;
  case LEFT:  OnMove(-1, 0);
	break;
  case RIGHT: OnMove(1, 0);
	break;
  case DOWN: onDown();
	break;
  case QUIT://ESC
	if (MessageBox(GetHWnd(), ("退出游戏？"), ("提示"),
	  MB_OKCANCEL | MB_ICONASTERISK) == IDOK) {
	  quit();
	}
	break;
  case SINK: moveBotton();
	break;
  }
}

//判断是否有按键
void getkey()
{
  CMD c;
  c = getCmd();
  dispatch(c);  //判断用户按的什么键
}

//游戏结束
void gameOver() {
  if (MessageBox(GetHWnd(), ("游戏结束\n 再来一局？"), ("游戏结束"),
	MB_YESNO | MB_ICONASTERISK) == IDYES) {
	initGame();
  }
  else
	quit();
}

//开始游戏
void start() {
  loadGame();
  initGame();
  while (1)
  {
	getkey();
	updata();
	draw();
  }
}