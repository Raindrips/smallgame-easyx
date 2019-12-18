#include<iostream>
#include<cstdio>
#include<windows.h>
#include<time.h>
#include<conio.h>

using namespace std;
const int LF_up_x = 13;
bool vis[100][100]; // 用于标记坐标
int Cor[100][100]; // 坐标的颜色
void color(int x);
void get_coord(int x, int y);
class Coord
{
public:
  int x;
  int y;
  int Col;
}G[10][10][10];
class T_Box
{
  static int Score;
  static int Rank;
private:
  int x, y; // 坐标
  int type; // 类型
  int fg; // 某个图形的第 fg 个变化的图形
public:
  T_Box(int sx = 31, int sy = 3, int st = 0, int f = 0);
  static void StaticNum(int num);
  void set(int sx = 31, int sy = 3, int st = 0, int f = 0);
  void Move(int stepA, int stepB);
  bool Stop();
  void print_Box();
  void erase_Box();
  void Mark();
  void Pause();
  void Next_Box(T_Box temp);
  void Transform();
  bool Judge();
};
int T_Box::Score = 0;
int T_Box::Rank = 0;
T_Box::T_Box(int sx, int sy, int st, int f)
{
  x = sx;  y = sy;  type = st;  fg = f;
}
void T_Box::StaticNum(int num)
{
  Score += num;
  Rank = Score / 10;
  color(5);
  get_coord(62, 19); cout << Score;
  get_coord(62, 21); cout << Rank;
}
void T_Box::set(int sx, int sy, int st, int f)
{
  st = rand() % 6;  f = rand() % 4;
  x = sx; y = sy; type = st; fg = f;
}
void T_Box::Next_Box(T_Box temp)
{
  for (int i = 0; i < 4; ++i)
  {
	int sx = G[temp.type][i][temp.fg].x + 59;
	int sy = G[temp.type][i][temp.fg].y + 6;
	get_coord(sx, sy);
	cout << " ";
  }
  for (int i = 0; i < 4; ++i)
  {
	int sx = G[type][i][fg].x + 59;
	int sy = G[type][i][fg].y + 6;
	color(G[type][i][fg].Col);
	get_coord(sx, sy);
	cout << "■";
  }
}
void T_Box::print_Box()  // 输入图形
{
  for (int i = 0; i < 4; ++i)
  {
	int  sx = G[type][i][fg].x + x;  // 第几种图形/第几个方格/第几种图形的第几种表示形式
	int  sy = G[type][i][fg].y + y;
	color(G[type][i][fg].Col);  // 颜色
	get_coord(sx, sy);   // 坐标
	cout << "■";   // 图形
  }
}
void T_Box::erase_Box() // 擦除图形
{
  for (int i = 0; i < 4; ++i)
  {
	int  sx = G[type][i][fg].x + x;
	int  sy = G[type][i][fg].y + y;
	get_coord(sx, sy);
	cout << " ";
  }
}
void T_Box::Move(int stepA, int stepB)
{
  bool flag = true;// 检查是否超出边界,默认没出边界
  for (int i = 0; i < 4; ++i)
  {
	int sx = x + G[type][i][fg].x + stepA;
	int sy = y + G[type][i][fg].y + stepB;
	if (sx <= 13 || sx >= 51 || sy >= 23 || sy <= 0 || vis[sx][sy])
	{
	  flag = false;  break;
	}
  }
  if (flag) { x += stepA; y += stepB; }
}
bool T_Box::Stop()
{
  for (int i = 0; i < 4; ++i)
  {
	int  sx = G[type][i][fg].x + x;
	int  sy = G[type][i][fg].y + y;
	if (vis[sx][sy + 1])  return true;
  }
  return false;
}
void T_Box::Mark()
{
  for (int i = 0; i < 4; ++i)
  {
	int  sx = G[type][i][fg].x + x;
	int  sy = G[type][i][fg].y + y;
	vis[sx][sy] = true;
	Cor[sx][sy] = G[type][i][fg].Col;
  }
}
bool T_Box::Judge()
{
  for (int i = 0; i < 4; ++i)
  {
	int sx = G[type][i][fg].x + x;
	int sy = G[type][i][fg].y + y;
	if (vis[sx][sy])  return false;
  }
  return true;
}
void T_Box::Transform() //先消除先前的图形然后再输出变化的图形
{
  erase_Box();// 擦除先前的图形
  int temp = fg;
  fg = (fg + 1) % 4;
  if (Judge())
	print_Box();
  else
  {
	fg = temp;
	print_Box();
  }
}
void get_coord(int x, int y)
{
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void color(int a)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void Tt_Fram()  //设置框架
{
  color(5);
  get_coord(30, 1);
  cout << "< 欢迎使用 >";
  color(10);
  int x = LF_up_x, y = 3; // 主要框架
  for (int i = 0; i < 30; ++i)
  {
	get_coord(x, 2);  vis[x][2] = true;  cout << "□";
	get_coord(x, 23); vis[x][23] = true; cout << "□";
	x += 2;
  }
  for (int i = 0; i < 21; ++i)
  {
	get_coord(LF_up_x, y); vis[LF_up_x][y] = true; cout << "□";
	get_coord(71, y);      vis[71][y] = true; cout << "□";
	get_coord(51, y);      vis[51][y] = true; cout << "□";
	y += 1;
  }//小框架内容
  for (int i = 53; i <= 69; i += 2)
  {
	get_coord(i, 11); vis[i][11] = true;
	cout << "□";
  }
  color(10);  get_coord(53, 3);  cout << " Next Block : ";
  color(11);
  get_coord(54, 13); cout << "开始 :  Enter 键";
  get_coord(54, 15); cout << "暂停 :   T 键";
  get_coord(54, 17); cout << "退出 :   Q 键";
  get_coord(54, 19);  cout << "Score :";
  get_coord(54, 21); cout << "Rank :";
  T_Box::StaticNum(0);
}
void Mark_init() // 初始化边界，标记数组
{
  for (int j = 2; j <= 23; ++j)
	for (int i = 0; i <= 12; ++i)
	  vis[i][j] = true;
  for (int j = 23; j <= 25; ++j)
	for (int i = 0; i <= 50; ++i)
	  vis[i][j] = true;
}
void set_Box()  // 设置各种图形
{
  for (int i = 0; i < 4; ++i)// 1 正方形
  {
	G[0][0][i].x = 0;  G[0][0][i].y = 0;  G[0][0][i].Col = 14;
	G[0][1][i].x = 0;  G[0][1][i].y = 1;  G[0][1][i].Col = 14;
	G[0][2][i].x = 2;  G[0][2][i].y = 0;  G[0][2][i].Col = 14;
	G[0][3][i].x = 2;  G[0][3][i].y = 1;  G[0][3][i].Col = 14;
  }// 2  竖条
  G[1][0][0].x = 0; G[1][0][0].y = 0; G[1][0][0].Col = 3;
  G[1][1][0].x = 0; G[1][1][0].y = 1; G[1][1][0].Col = 3;
  G[1][2][0].x = 0; G[1][2][0].y = 2; G[1][2][0].Col = 3;
  G[1][3][0].x = 0; G[1][3][0].y = 3; G[1][3][0].Col = 3;
  G[1][0][1].x = 0; G[1][0][1].y = 0; G[1][0][1].Col = 3;
  G[1][1][1].x = 2; G[1][1][1].y = 0; G[1][1][1].Col = 3;
  G[1][2][1].x = 4; G[1][2][1].y = 0; G[1][2][1].Col = 3;
  G[1][3][1].x = 6; G[1][3][1].y = 0; G[1][3][1].Col = 3;
  G[1][0][2].x = 0; G[1][0][2].y = 0; G[1][0][2].Col = 3;
  G[1][1][2].x = 0; G[1][1][2].y = 1; G[1][1][2].Col = 3;
  G[1][2][2].x = 0; G[1][2][2].y = 2; G[1][2][2].Col = 3;
  G[1][3][2].x = 0; G[1][3][2].y = 3; G[1][3][2].Col = 3;
  G[1][0][3].x = 0; G[1][0][3].y = 0; G[1][0][3].Col = 3;
  G[1][1][3].x = 2; G[1][1][3].y = 0; G[1][1][3].Col = 3;
  G[1][2][3].x = 4; G[1][2][3].y = 0; G[1][2][3].Col = 3;
  G[1][3][3].x = 6; G[1][3][3].y = 0; G[1][3][3].Col = 3;
  // 3
  G[2][0][0].x = 0; G[2][0][0].y = 0; G[2][0][0].Col = 4;
  G[2][1][0].x = 0; G[2][1][0].y = 1; G[2][1][0].Col = 4;
  G[2][2][0].x = 2; G[2][2][0].y = 1; G[2][2][0].Col = 4;
  G[2][3][0].x = 2; G[2][3][0].y = 2; G[2][3][0].Col = 4;
  G[2][0][1].x = 0; G[2][0][1].y = 0; G[2][0][1].Col = 4;
  G[2][1][1].x = 2; G[2][1][1].y = 0; G[2][1][1].Col = 4;
  G[2][2][1].x = 0; G[2][2][1].y = 1; G[2][2][1].Col = 4;
  G[2][3][1].x = -2; G[2][3][1].y = 1; G[2][3][1].Col = 4;
  G[2][0][2].x = 0; G[2][0][2].y = 0; G[2][0][2].Col = 4;
  G[2][1][2].x = 0; G[2][1][2].y = 1; G[2][1][2].Col = 4;
  G[2][2][2].x = 2; G[2][2][2].y = 1; G[2][2][2].Col = 4;
  G[2][3][2].x = 2; G[2][3][2].y = 2; G[2][3][2].Col = 4;
  G[2][0][3].x = 0; G[2][0][3].y = 0; G[2][0][3].Col = 4;
  G[2][1][3].x = 2; G[2][1][3].y = 0; G[2][1][3].Col = 4;
  G[2][2][3].x = 0; G[2][2][3].y = 1; G[2][2][3].Col = 4;
  G[2][3][3].x = -2; G[2][3][3].y = 1; G[2][3][3].Col = 4;
  // 4
  G[3][0][0].x = 0; G[3][0][0].y = 0; G[3][0][0].Col = 5;
  G[3][1][0].x = 0; G[3][1][0].y = 1; G[3][1][0].Col = 5;
  G[3][2][0].x = -2; G[3][2][0].y = 1; G[3][2][0].Col = 5;
  G[3][3][0].x = 2; G[3][3][0].y = 1; G[3][3][0].Col = 5;
  G[3][0][1].x = 0; G[3][0][1].y = 0; G[3][0][1].Col = 5;
  G[3][1][1].x = 0; G[3][1][1].y = 1; G[3][1][1].Col = 5;
  G[3][2][1].x = 2; G[3][2][1].y = 1; G[3][2][1].Col = 5;
  G[3][3][1].x = 0; G[3][3][1].y = 2; G[3][3][1].Col = 5;
  G[3][0][2].x = 0; G[3][0][2].y = 0; G[3][0][2].Col = 5;
  G[3][1][2].x = 2; G[3][1][2].y = 0; G[3][1][2].Col = 5;
  G[3][2][2].x = 2; G[3][2][2].y = 1; G[3][2][2].Col = 5;
  G[3][3][2].x = 4; G[3][3][2].y = 0; G[3][3][2].Col = 5;
  G[3][0][3].x = 0; G[3][0][3].y = 0; G[3][0][3].Col = 5;
  G[3][1][3].x = 0; G[3][1][3].y = 1; G[3][1][3].Col = 5;
  G[3][2][3].x = -2; G[3][2][3].y = 1; G[3][2][3].Col = 5;
  G[3][3][3].x = 0; G[3][3][3].y = 2; G[3][3][3].Col = 5;
  // 5
  G[4][0][0].x = 0; G[4][0][0].y = 0; G[4][0][0].Col = 6;
  G[4][1][0].x = 0; G[4][1][0].y = 1; G[4][1][0].Col = 6;
  G[4][2][0].x = 0; G[4][2][0].y = 2; G[4][2][0].Col = 6;
  G[4][3][0].x = 2; G[4][3][0].y = 2; G[4][3][0].Col = 6;
  G[4][0][1].x = 0; G[4][0][1].y = 0; G[4][0][1].Col = 6;
  G[4][1][1].x = 0; G[4][1][1].y = 1; G[4][1][1].Col = 6;
  G[4][2][1].x = 2; G[4][2][1].y = 0; G[4][2][1].Col = 6;
  G[4][3][1].x = 4; G[4][3][1].y = 0; G[4][3][1].Col = 6;
  G[4][0][2].x = 0; G[4][0][2].y = 0; G[4][0][2].Col = 6;
  G[4][1][2].x = 2; G[4][1][2].y = 0; G[4][1][2].Col = 6;
  G[4][2][2].x = 2; G[4][2][2].y = 1; G[4][2][2].Col = 6;
  G[4][3][2].x = 2; G[4][3][2].y = 2; G[4][3][2].Col = 6;
  G[4][0][3].x = 0; G[4][0][3].y = 0; G[4][0][3].Col = 6;
  G[4][1][3].x = 0; G[4][1][3].y = 1; G[4][1][3].Col = 6;
  G[4][2][3].x = -2; G[4][2][3].y = 1; G[4][2][3].Col = 6;
  G[4][3][3].x = -4; G[4][3][3].y = 1; G[4][3][3].Col = 6;
  // 6
  G[5][0][0].x = 0; G[5][0][0].y = 0; G[5][0][0].Col = 9;
  G[5][1][0].x = 0; G[5][1][0].y = 1; G[5][1][0].Col = 9;
  G[5][2][0].x = 0; G[5][2][0].y = 2; G[5][2][0].Col = 9;
  G[5][3][0].x = -2; G[5][3][0].y = 2; G[5][3][0].Col = 9;
  G[5][0][1].x = 0; G[5][0][1].y = 0; G[5][0][1].Col = 9;
  G[5][1][1].x = 0; G[5][1][1].y = 1; G[5][1][1].Col = 9;
  G[5][2][1].x = 2; G[5][2][1].y = 1; G[5][2][1].Col = 9;
  G[5][3][1].x = 4; G[5][3][1].y = 1; G[5][3][1].Col = 9;
  G[5][0][2].x = 0; G[5][0][2].y = 0; G[5][0][2].Col = 9;
  G[5][1][2].x = 2; G[5][1][2].y = 0; G[5][1][2].Col = 9;
  G[5][2][2].x = 0; G[5][2][2].y = 1; G[5][2][2].Col = 9;
  G[5][3][2].x = 0; G[5][3][2].y = 2; G[5][3][2].Col = 9;
  G[5][0][3].x = 0; G[5][0][3].y = 0; G[5][0][3].Col = 9;
  G[5][1][3].x = 2; G[5][1][3].y = 0; G[5][1][3].Col = 9;
  G[5][2][3].x = 4; G[5][2][3].y = 0; G[5][2][3].Col = 9;
  G[5][3][3].x = 4; G[5][3][3].y = 1; G[5][3][3].Col = 9;
}
void Check() // 检查是否可以消除
{
  int Incr = 0;
  for (int j = 22; j >= 4; --j) //检查每一行// y -> 1 ~~~ 20   x -> 15 ~~ 52
  {
	bool flag = true;       // 假设可以消除
	for (int i = 15; i <= 49; i += 2)
	  if (!vis[i][j])
	  {
		flag = false; break;
	  }
	if (flag) // 当前行可以消除
	{
	  Incr++;// 加分操作
	  for (int i = 15; i <= 49; i += 2)  // 先消除当前的满行标记
	  {
		vis[i][j] = false;
		get_coord(i, j);
		cout << " ";
	  }// 将上面的行移动下来
	  for (int c_j = j - 1; c_j >= 5; --c_j)
		for (int c_i = 15; c_i <= 49; c_i += 2)
		  if (vis[c_i][c_j]) // 如果已经标记
		  {
			vis[c_i][c_j] = false;
			vis[c_i][c_j + 1] = true;
			Cor[c_i][c_j + 1] = Cor[c_i][c_j];
			Cor[c_i][c_j] = 0;
			get_coord(c_i, c_j);
			cout << " ";
			color(Cor[c_i][c_j + 1]);
			get_coord(c_i, c_j + 1);
			cout << "■";
		  }
	  j++;
	}
  }
  T_Box::StaticNum(Incr * 2);
}
void Exit()
{
  Sleep(20000);
  exit(0);
}
void T_Box::Pause()
{
  Move(0, -1);
  print_Box();
  while (1)
  {
	char ch = _getch();
	if (ch == 13)  break;
  }
}
void Tetris()  // 主程序
{
  srand(time(0)); // 取系统时间
  //Tt_Fram() ;     // 设置框架
  set_Box();    // 设置各种图形
  T_Box  cd, tempA, tempB;   // 每个下降的方块的初始值
  tempB.set();
  tempB.Next_Box(tempA);
  for (int i = 0; ; ++i)
  {
	if (!(i % 2))   tempA.set();
	else         tempB.set();
	if (i % 2)      tempB.Next_Box(tempA), cd = tempA;
	else         tempA.Next_Box(tempB), cd = tempB;
	while (1)
	{
	  cd.print_Box(); // 输出图形
	  if (cd.Stop())
	  {
		color(6);
		get_coord(20, 10);
		cout << "   T_T    游戏结束    T_T";
		Exit();
	  }
	  Sleep(350);
	  cd.erase_Box(); //擦除图形
	  cd.Move(0, 1);
	  if (_kbhit()) // 判断是否有按键按下，如果有则可能是旋转或者加速按键
	  {
		char ch = _getch();
		switch (ch)
		{
		case 'a':   cd.Move(-2, 0); break;    //  向左移动一格
		case 'd':   cd.Move(2, 0);  break;    //  向右移动一格
		case 'w':   cd.Transform(); break;                   //  变换方格
		case 's':   cd.Move(0, 2); break;  //  急降方格
		case 'T':   cd.Pause(); break;
		case 'Q':   Exit();  break;
		default:    break; // 如果都不是则不执行
		}
	  }
	  if (cd.Stop())  break;
	}
	cd.print_Box();
	cd.Mark();
	Check(); // 检查是否可以消除
  }
}
void HideCursor()  // 隐藏光标
{
  CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
int main()
{
  HideCursor(); // 隐藏光标
  bool flag = true;
  memset(vis, false, sizeof(vis)); // 标记
  memset(Cor, 0, sizeof(Cor)); // 用于记录颜色
  Mark_init();   // 标记外围不可访问
  Tt_Fram(); // 设置框架
  while (1)
  {
	if (flag)
	{
	  while (1)
	  {
		char ch = _getch();
		if (ch == 13) break;
	  }
	  Tetris();
	  flag = false;
	}
	else    Tetris();
  }
  return 0;
}