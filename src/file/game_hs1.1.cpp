#include<bits/stdc++.h>//输入输出用的 
#include<ctime>//计算时间用的 colok() 
#include<conio.h>//_getch()用的 
#include<fstream>//存档用的
#include<windows.h>//SLeep等函数 
using namespace std;
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
using namespace _game_hs;
using namespace _game_hs;
int main()
{
	
	return 0;
}
