#include <iostream>
#include <easyx.h>		//Í¼ÐÎ¿â
#include <vector>
#include <stack>
#include <conio.h>

using namespace std;

const int length = 700;
const int MAXSIZE = 13;

int pos = length / (MAXSIZE + 1);
vector<vector<int>> chessPieces(MAXSIZE, vector<int>(MAXSIZE, 0));

stack<vector<vector<int>>> chessManual;	//ÆåÆ×

bool isBlackDown = true;

void initChessGame()
{
	initgraph(length, length,SHOWCONSOLE);
	chessManual.push(chessPieces);
}

void drawChessBoard()
{
	
	//»­±³¾°
	setbkcolor(0x20a5da);		//DAA520
	cleardevice();
	//»­Ïß
	setlinecolor(0x0);
	for (int i = 1; i <= MAXSIZE; i++)
	{
		line(pos*i, pos, pos*i, length - pos);
		line(pos, pos*i, length - pos, pos*i);
	}
	int cen = MAXSIZE / 2 + 1;
	//»­ÆåÅÌµã
	setfillcolor(0x0);
	solidcircle(cen*pos, cen*pos, pos / 8);

	int dot[][2] = { { 4 * pos, 4 * pos }, { 4 * pos, (MAXSIZE - 3) * pos },
	{ (MAXSIZE - 3) * pos, 4 * pos }, { (MAXSIZE - 3)* pos, (MAXSIZE - 3) * pos } };

	for (int i = 0; i < 4; i++)
	{
		solidcircle(dot[i][0], dot[i][1], pos / 8);
	}
	
}

void drawPiece(int x, int y, bool isBlack)
{
	if (isBlack)
	{
		setfillcolor(0x0);
	}
	else
	{
		setfillcolor(0xeeeeee);
	}
	solidcircle(x*pos, y*pos, pos / 3);
}

//»æÖÆÆåÅÌ
void drawPieces()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			switch (chessPieces.at(i).at(j))
			{
			case 1:	//ºÚÆå
				drawPiece(i, j, true);
				break;
			case 2:	//°×Æå
				drawPiece(i, j, false);
				break;
			}
		}
	}
}

void draw()
{
	BeginBatchDraw();
	drawChessBoard();
	drawPieces();
	EndBatchDraw();
}

//³·Ïú
void cancel()
{
	int c=0;
	if (c=GetAsyncKeyState(VK_SPACE))
	{
		printf("%d\n", c);
		if (c == 1&&chessManual.size()>1)
		{
			chessManual.pop();
			vector<vector<int>> temp = chessManual.top();
			chessPieces.assign(temp.begin(), temp.end());
			isBlackDown = !isBlackDown;
		}
	}
}


bool isWin(int x, int y)
{
	int dir[][2] = { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, -1 } };
	for (int i = 0; i < 4; i++)
	{
		int count = 1;
		for (int j = 1; j < 5; j++)
		{

			int mx = x - dir[i][0] * j;
			int my = y - dir[i][1] * j;
			if (mx >= 0 && mx < MAXSIZE&&my >= 0 && my < MAXSIZE
				&& chessPieces[mx][my] == chessPieces[x][y])
			{
				count++;
			}
			mx = x + dir[i][0] * j;
			my = y + dir[i][1] * j;
			if (mx >= 0 && mx < MAXSIZE&&my >= 0 && my < MAXSIZE
				&&chessPieces[mx][my] == chessPieces[x][y])
			{
				count++;
			}
		}
		if (count >= 5)
		{
			return true;
		}
	}
	return false;
}



void downChess(int x, int y)
{
	if (x <= 0 || y >= MAXSIZE)
	{
		return;
	}
	if (chessPieces[x][y] == 0)
	{
		chessPieces[x][y] = isBlackDown ? 1 : 2;
		vector<vector<int>> temp(chessPieces);
		chessManual.push(temp);
		isBlackDown = !isBlackDown;
		if (isWin(x, y))
		{
			char buf[20];

			sprintf_s<20>(buf, "%s", !isBlackDown ? "ºÚÆåÊ¤Àû" : "°×ÆåÊ¤Àû");
			drawPieces();
			MessageBox(GetForegroundWindow(), TEXT(buf), NULL, MB_OK);
			closegraph();
		}
	}
}


//Êó±êµã»÷ÊÂ¼þ
void onMouseClickEvent()
{
	MOUSEMSG mouse = GetMouseMsg();

	if (mouse.uMsg == WM_LBUTTONDOWN)
	{
		int x = (mouse.x + pos / 4) / pos;
		int y = (mouse.y + pos / 4) / pos;
		downChess(x, y);

	}
}


void runChessGame()
{
	initChessGame();
	drawChessBoard();
	while (true)
	{

		onMouseClickEvent();
		cancel();
		draw();
		Sleep(4);
	}

}

int main()
{
	runChessGame();
	closegraph();
}