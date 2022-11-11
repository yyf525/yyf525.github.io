#ifndef game
#define game
#include<bits/stdc++.h>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<fstream>
using namespace std;
typedef unsigned long long ull;
namespace _game_cl
{
	const int ESC=27,Enter=13,Back=8,Tab=9,
	Shang=72,Xia=80,Zuo=75,You=77,
	Shift=VK_SHIFT,Shift_z=VK_LSHIFT,Shift_y=VK_RSHIFT,
	sb_z=VK_LBUTTON,sb_y=VK_RBUTTON,
	Ctrl=VK_CONTROL,Ctrl_z=VK_LCONTROL,Ctrl_y=VK_RCONTROL,
	Alt=VK_MENU,Alt_z=VK_LMENU,Alt_y=VK_RMENU;
}
namespace _game_sb
{
	const int sb_z=VK_LBUTTON,sb_y=VK_RBUTTON;
	struct hl{
		int h;
		int l;
	};
	void ycgb() {
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
		COORD pos={x,y};
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
namespace _game_hs{
	typedef unsigned long long ull;
	bool axj(int a){
		return GetKeyState(a)<0;
	}
	void color(int c)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
		return;
	}
	void colorout(string s,int c){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
		cout<<s;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		return;
	}
	void out(string s,int q){
		for(int i=0;i<s.size();i++){
			cout<<s[i];
			Sleep(q);
		}
		return;
	}
	void zk(string s,char c,string cd){
		int n=s.size(),n1=cd.size();
		if(cd=="长度")n1=100;
		int tot=n1-n;
		for(int i=0;i<tot/2;i++)
		cout<<c;
		cout<<s;
		if(tot%2==1)tot++;
		tot/=2;
		for(int i=0;i<tot;i++)
		cout<<c;
		return;
	}
	void zc(string s,char t,string cd){
		cout<<s;
        int n1=cd.size();
        if(cd=="长度")n1=100;
		for(int i=s.size();i<n1;i++)
		cout<<t;
		return;
	}
	ull szi(string s){
		ull tot=0;
		for(int i=0;i<s.size();i++)
		tot=tot*10+s[i]-'0';
		return tot;
	}
	string izs(int a){
		string s="",s1="";
		while(a){
			s+=a%10+'0';
			a/=10;
		}
		for(int i=s.size()-1;i>=0;i--)
		s1+=s[i];
		return s1;
	}
	bool pdzf(char c){ 
		if(c>=32&&c<=127)return 1;
		return 0;
	}
	void zt(){
		cout<<"请按任意键继续. . .";
		char c;
		c=_getch();
		return;
	}
	void zt(int x){
		Sleep(x);
		return;
	}
}
#endif
