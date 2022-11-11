#include<bits/stdc++.h>//输入输出用的 
#include<ctime>//计算时间用的 colok() 
#include<conio.h>//_getch()用的 
#include<fstream>//存档用的
#include<windows.h>//SLeep等函数 
using namespace std;
namespace _game_sb
{
	const int sb_z=VK_LBUTTON,sb_y=VK_RBUTTON;
	struct hl{
		int h;
		int l;
	};
	void ycgb(){
		CONSOLE_CURSOR_INFO cciCursor;
		HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
		if(GetConsoleCursorInfo(hStdOut,&cciCursor)) {
			cciCursor.bVisible=FALSE;
			SetConsoleCursorInfo(hStdOut,&cciCursor);
		}
		return;
	}
	void ycbj(){
		HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin,&mode);
		mode &=~ENABLE_QUICK_EDIT_MODE;
		SetConsoleMode(hStdin, mode);
		return;
	}
	void ydgb(int x,int y) {
		COORD pos={y-1,x-1};
		HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut,pos);
	}
	bool sbax(char c){
		if(c=='l')return GetKeyState(sb_z)<0;
		if(c=='r')return GetKeyState(sb_y)<0;
		if(c=='m')return GetKeyState(sb_y)<0||GetKeyState(sb_z)<0;
	}
	hl sbwz(){
		hl hl;
		POINT p;
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_FONT_INFO consoleCurrentFont;
		HWND h=GetForegroundWindow();
		GetCursorPos(&p);
		ScreenToClient(h,&p);
		GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont);
		hl.h=p.x/consoleCurrentFont.dwFontSize.X;
		hl.l=p.y/consoleCurrentFont.dwFontSize.Y;
		return hl;
	}
	bool pdsb(char c,int hx,int hd,int lx,int ld){//判断鼠标是否在位置内
		hl hl=sbwz();
		if(hl.h>=hx&&hl.h<=hd&&hl.l>=lx&&hl.l<=ld)return 1;
		return 0;
	}
}
using namespace _game_sb;
int main()
{
	
	return 0;
}
