#include<iostream>//输入输出用的 
#include<ctime>//计算时间用的 colok() 
#include<conio.h>//_getch()用的 
#include<fstream>//存档用的
#include<windows.h>//SLeep等函数 
using namespace std;
const int tms=10,pdh=45,pdj=362880;
double ksjs,jsjs;
string sdtm[tms+1][10]={
	{
		"          "
	},
	{//1
		"          ",
		"  61 3  2 ",
		"  5   81 7",
		"      7 34",
		"   9  6378",
		"   32795  ",
		" 57 3  9 2",
		" 19 76    ",
		" 8 24  76 ",
		" 64  1 25 "
	},
	{//
		"          ",
		" 1  83   2",
		" 57   1   ",
		"    5 9 64",
		" 7 4  859 ",
		"   3 1 4  ",
		"  514  3 6",
		" 36 7 4   ",
		"    6   79",
		" 8   52  3"
	},
	{
		"          ",
		"    4 9   ",
		"  8  2 7  ",
		"  2 5 71 6",
		" 3  8   6 ",
		" 76     31",
		"  1   6  2",
		" 2 59 8 4 ",
		"   9 7  1 ",
		"    6 5   "
	},
	{
		"          ",
		"       945",
		"   6      ",
		" 52 1 38 7",
		"  9 31    ",
		"   3 8 1  ",
		"     46 2 ",
		" 7 52 8 19",
		"       3  ",
		" 861      "
	},
	{
		"          ",
		"  7 1 3 6 ",
		"  5     7 ",
		" 3   5   1",
		" 5  3 4  8",
		" 4 7   1 2",
		" 9  7 2  4",
		" 2   7   3",
		"  3     4 ",
		"  6 5 9 2 "
	},
	{
		"          ",
		"  9    64 ",
		" 4        ",
		" 1  36  72",
		"   46    9",
		"    9 3   ",
		" 2    54  ",
		" 92  57  8",
		"         5",
		" 34    6  "
	},
	{
		"          ",
		"   7   9  ",
		" 2  5 7  6",
		"  8 1 4 7 ",
		"  4  1  3 ",
		" 6 1   8 9",
		"  9  8  6 ",
		"  5 8 9 1 ",
		"  1 6 3  2",
		"   6   3  ",
	},
	{
		"          ",
		"  1   84 7",
		" 95       ",
		"   8 1    ",
		"  82      ",
		" 7  4 6  8",
		"       62 ",
		"     5 7  ",
		"        82",
		" 5 32   1 ",
	},
	{
		"          ",
		" 75  9  46",
		" 9 1   3 2",
		"          ",
		" 2  6 1  7",
		"  8     2 ",
		" 1  3 8  5",
		"          ",
		" 3 9   2 4",
		" 84  3  79",
	},
	{
		"          ",
		"    89  2 ",
		"   9  5  7",
		"  5    3  ",
		"  935  1  ",
		"    1 7   ",
		"   1  684 ",
		"   8    6 ",
		" 9  6  4  ",
		"  1  28   ", 
	}
};
struct wj{
	bool b[tms+1];
	int time[tms+1];
	void cj(){
		for(int i=1;i<=tms;i++)
		b[i]=0,time[i]=0;
	}
}wj;
struct cd
{
	void out()
	{
		ofstream a("游戏进度");
		for(int i=1;i<=tms;i++)
		a<<wj.b[i]<<"\n";
		a.close();
		ofstream b("游戏时间");
		for(int i=1;i<=tms;i++)
		b<<wj.time[i]<<"\n";
		b.close();
		return;
	}
	void in()
	{
		ifstream a("游戏进度");
		for(int i=1;i<=tms;i++)
		a>>wj.b[i];
		a.close();
		ifstream b("游戏时间");
		for(int i=1;i<=tms;i++)
		b>>wj.time[i];
		b.close();
		return;
	}
}cd;
void sc(string s[],int b[10][10]);//输出 
bool pd1(string s[]);//判断是否通关 
void out(string s,int x);//输出字符串 
void zk(string s,char t);//中空输出 
//输出函数 
void zt();//暂停 
void color(int c);//染色 
//基本函数
void js1();//开始计时 
void js2();//结束计时 
//计时函数
void sdyx();//数独游戏主界面
void gzjs(); //规则介绍
void zzjs();//作者介绍
void yx();//游戏
void xy(int x);//游戏的分支 
void youxi();//总游戏 
void cgsc();//闯关输出
int zhzfc(string s);//将字符串转换为整数 
int kssc();//开始的时候输出
int main(){
	color(15);
	cd.in();
	sdyx();
	cd.out();
	return 0;
}
void js1(){
	ksjs=clock();
}
void js2(){
	jsjs=clock();
}
void sdyx(){
	wj.cj();
	cd.in();
	while(1){
		system("cls");
		int s=kssc();
		switch(s){
			case 0:{
				return;
				break;
			}
			case 1:{
				youxi();
				break;
			}
			case 2:{
				gzjs();
				break;
			}
			case 3:{
				zzjs();
				break;
			}
			case 4:{
				cd.out();
				break;
			}
		}
	}
	return;
}
void youxi(){
	system("cls");
	zk("欢迎来到游戏界面",'-');
	cout<<"\n\n";
	cout<<"0：退出     1：随机关卡     2：闯关\n";
	char s=_getch();
	while(s<'0'||s>'3')s=_getch();
	switch(s){
		case '0':{
			return;
			break;
		}
		case '1':{
			js1();
			yx();
			break;
		}
		case '2':{
			cgsc();
			cout<<"请输入需要游戏的关卡（1~"<<tms<<"）\n";
			string s1;
			int zss1;
			cin>>s1;
			zss1=zhzfc(s1);
			while(zss1<1||zss1>tms){
				system("cls");
				cout<<"输入的关卡数有误，请重新输入\n";
				Sleep(400);
				cout<<"按空格返回";
				char s2=_getch();
				while(s2!=32)s2=_getch();
				cgsc();
				cout<<"请输入需要游戏的关卡（1~"<<tms<<"）\n";
				cin>>s1;
				zss1=zhzfc(s1);
			}
			cout<<"\n输入成功\n正在努力加载游戏界面...";
			for(int i=0;i<4;i++){
				if(i%2==0){
					Sleep(1000);
					cout<<"...";
				}
				else{
					Sleep(1000);
					cgsc();
					cout<<"请输入需要游戏的关卡（1~"<<tms<<"）\n";
					cout<<zss1;
					cout<<"\n\n输入成功\n正在努力加载游戏界面...";
				}
			}
			Sleep(1000);
			cout<<"\n\n";
			color(12);
			cout<<"加载成功！！！";
			color(15);
			Sleep(890);
			js1();
			xy(zss1);
			break;
		}
	}
	return;
}
void xy(int x){
	int b[10][10];
	string a[10];
	for(int i=1;i<10;i++){
		a[i]=sdtm[x][i];
		for(int j=1;j<10;j++){
			b[i][j]=(sdtm[x][i][j]!=' ');
		}
	}
	while(1){
		system("cls");
		int tot=0;
		for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		if(a[i][j]!=' ')tot++;
		if(tot==81){
			if(pd1(a)){
				sc(a,b); 
				system("cls");
				out("恭喜您通关了这个数独\n",30); 
				js2();
				int ti=jsjs-ksjs;
				cout<<"用时："<<ti/1000<<"秒\n";
				if(b[x]==0||wj.time[x]>=ti){
					wj.b[x]=1;
					wj.time[x]=jsjs-ksjs;
					cd.out();
				}
				cout<<"\n";
				zt(); 
				return;
			}
			else{
				system("cls");
				out("很抱歉，您的填写有误，是否重新开始（y/n）",45);
				char qw=_getch();
				while(qw!='y'&&qw!='n')qw=_getch();
				if(qw=='y')
				{
					js1();
					xy(x);
				}
			}
			system("cls");
		}
		cout<<"您正在游戏的是"<<x<<"号数独\n"; 
		sc(a,b);
		Sleep(400);
		cout<<"0：退出     1：填写     2：帮助\n";
		char s=_getch();
		while(s<'0'||s>'2')s=_getch();
		s-='0';
		if(s==0){
			system("cls");
			out("已成功退出！！！",40);
			cout<<"\n";
			zt();
			return;
		}
		if(s==1){
			cout<<"请输入填写的坐标（先行再列）以及填写的数";
			int x,y,k;
			cin>>x>>y>>k;
			while(x<1||x>9||y<1||y>9||k<0||k>9||b[x][y]==1){
				Sleep(400);
				system("cls");
				if(b[x][y]==1){
					cout<<"这个格子是系统产生的数，不可以随意更改！！！";
				}
				else
				cout<<"输入错误，请重新输入！！！";
				zt();
				system("cls");
				sc(a,b);
				cout<<"0：退出     1：填写     2：删除\n";
				cout<<"请输入填写的坐标（先行再列）以及填写的数";
				cin>>x>>y>>k;
			}
			if(k==0){
				b[x][y]=0;
				a[x][y]=' ';
				out("删除成功！！！",20);
			}
			else{
				if(b[x][y]==2)
				out("更改成功！！！",20);
				else
				out("填写成功！！！",20);
				b[x][y]=2,a[x][y]=k+'0';
			}
		}
		if(s==2){
			system("cls");
			cout<<"当您需要删除您自己所填写的数字时，只需要填写坐标再输入0即可。\n";
			zt();
			continue;
		}
	}
}
void yx(){
	srand(time(0));
	int x=rand()%tms+1;
	xy(x);
}
void gzjs(){
	while(1){
		system("cls");
		cout<<"0：退出     1：数独介绍     2：玩法技巧\n";
		char s=_getch();
		while(s!='0'&&s!='1'&&s!='2')s=_getch();
		s-='0';
		if(s==0)return;
		if(s==1){
			system("cls");
			color(12);
			cout<<"介绍：";
			color(15);
			out("\n  数独 （英语：Sudoku）是一种逻辑性的数字填充游戏，玩家须以数字填进每一格，而每行、每列和每个宫（即3x3的大格）有齐1至9所有数字。游戏设计者会提供一部分的数字，使谜题只有一个答案。一个已解答的数独其实是一种多了宫的限制的拉丁方阵，因为同一个数字不可能在同一行、列或宫中出现多于一次。\n\n",20);
			Sleep(400);
			color(12);
			cout<<"规则：";
			color(15);
			out("\n  数独（九宫格）的规律是每一行、每一列、每一个粗线宫（3*3）内的数字均含1-9，不重复。玩家需要根据9×9盘面上的已知数字，推理出所有剩余空格的数字，并满足每一行、每一列、每一个粗线宫（3*3）内的数字均含1-9，不重复。数独盘面是个九宫，每一宫又分为九个小格。在这八十一格中给出一定的已知数字和解题条件，利用逻辑和推理，在其他的空格上填入1-9的数字。使1-9每个数字在每一行、每一列和每一宫中都只出现一次，所以又称“九宫格”。\n\n",20);
			Sleep(400);
			color(12);
			cout<<"好处：";
			color(15);
			out("\n  玩数独首先观察力的提升有好处，无容置疑，即使你看懂了再多，再难的技巧，若无版法观察，无权法应用也是白搭；第二，逻辑推理能力，数独本身就是一个逻辑推理类的游戏，在每一步出数的时候需要利用盘面的数字进行推导，在你做其他事的时候利用数独这种分析判断力，也会对问题的理解更为深刻；第三，心态，发现不少人说，觉得烦的时候，一道数独就能让心情平复下来，在解题的时候全神贯注，往往时间在不经意间流逝，同样的，当你被数独题难到时，也要保持平和的心态，过于浮躁则很难找到突破点。\n\n",20);
			Sleep(400);
			zt();
		}
		if(s==2){
			system("cls");
			color(12);
			cout<<"1：";
			color(15);
			out("先找数字最多的（观察整个表格，哪个数字出现最多），再利用游戏规则进行推内断填入，最容易容填。\n\n",20);
			Sleep(200);
			color(12);
			cout<<"2：";
			color(15);
			out("填的时候尽可能把一个数字（指1-9中其中一个）填完。\n\n",20);
			Sleep(100);
			color(12);
			cout<<"3：";
			color(15);
			out("对于则于数字少而二个数字无法直接确定的，只能先假设，然后往下推断，若无矛盾的，则原假设正确，不用改。而后来推断出现矛盾了，则原先假设不成立，位置对调即可。\n\n",30);
			Sleep(300);
			color(12);
			cout<<"4：";
			color(15);
			out("一行或一列、一个九宫格剩余数字不超过3个了，就可以利用前后左右行与列推断填写。\n\n",25);
			Sleep(250);
			color(12);
			cout<<"5：";
			color(15);
			out("当您需要删除您自己所填写的数字时，只需要填写坐标再输入0即可。\n\n",20);
			Sleep(150);
			zt();
		}
	}
	return;
}
void zzjs(){
	system("cls");
	cout<<"                                  作者介绍\n";
	cout<<"姓名：YYF     年龄：12     就读学校：湄小（601）班\n";
	cout<<"业余爱好：编程、下棋\n";
	zt();
	return;
}
bool pd1(string s[]){
	int H,J;
	for(int i=1;i<10;i++){
		H=0,J=1;
		for(int j=1;j<10;j++)
		H+=s[i][j]-'0',J*=s[i][j]-'0';
		if(H!=pdh||J!=pdj)return 0;
	}
	for(int i=1;i<10;i++){
		H=0,J=1;
		for(int j=1;j<10;j++)
		H+=s[j][i]-'0',J*=s[j][i]-'0';
		if(H!=pdh||J!=pdj)return 0;
	}
	for(int i=0;i<=6;i+=3){
		for(int j=0;j<=6;j+=3){
			H=0,J=1;
			for(int l=1;l<=3;l++){
				for(int k=1;k<=3;k++){
					int x=l+i,y=k+j;
					H+=s[x][y]-'0',J*=s[x][y]-'0';
				}
			}
			if(H!=pdh||J!=pdj)return 0;
		}
	}
	H=0,J=1;
	return 1;
}
void color(int c)//颜色 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return;
}
void sc(string s[],int b[10][10]){
	color(9);
	cout<<"┏━┳━┳━┳━┳━┳━┳━┳━┳━┓\n";
	color(15);
	for(int i=1;i<=9;i++){
		color(9);
		cout<<"┃";
		color(15);
		for(int j=1;j<=9;j++){
			if(b[i][j]==1){
				color(12);
				cout<<s[i][j];
				color(15);
			}
			else
			{
				cout<<s[i][j];
			}
			cout<<" ";
			if(j%3==0)color(9); 
			cout<<"┃";
			color(15);
		}
		if(i!=9)
		{
			if(i%3==0){
				color(9);
				cout<<"\n┠━╋━╋━╋━╋━╋━╋━╋━╋━┨";
				color(15);
			}
			else{
				color(9);
				cout<<"\n┠";
				color(15);
				cout<<"━╋━╋━";
				color(9);
				cout<<"╋";
				color(15);
				cout<<"━╋━╋━";
				color(9);
				cout<<"╋";
				color(15);
				cout<<"━╋━╋━";
				color(9);
				cout<<"┨";
				color(15);
			}
		}
		cout<<"\n";
	}
	color(9);
	cout<<"┗━┻━┻━┻━┻━┻━┻━┻━┻━┛\n";
	color(15);
	return;
}
void out(string s,int x){
	for(int i=0;i<s.size();i++)
	{
		cout<<s[i];
		Sleep(x);
	}
	return;
} 
void zt(){
	cout<<"请按任意键继续. . .";
	char a=_getch();
	return;
}
void zk(string s,char t){
	int tot=s.size();
	if(tot%2==1){
		s+=t;
		tot++;
	}
	tot=80-tot;
	tot/=2;
	for(int i=0;i<tot;i++)
	cout<<t;
	cout<<s;
	for(int i=0;i<tot;i++)
	cout<<t;
	return;
}
void cgsc(){
	system("cls");
	color(15); 
	int k=tms,ls=0;
	while(k>0){
		int cd[5];
		memset(cd,0,sizeof(cd));
		
		for(int i=1;i<=min(k,4);i++){
			cout<<"----------------";
			if(i!=min(k,4))cout<<"  ";
			else
			cout<<"\n";
		}
		for(int i=1;i<=min(k,4);i++){
			cout<<"|名称：关卡"<<ls*4+i<<" ";
			if(ls*4+i<10)cout<<" ";
			cout<<" |";
			if(i!=min(k,4))cout<<"  ";
			else
			cout<<"\n";
		}
		for(int i=1;i<=min(k,4);i++){
			cout<<"|状态：";
			if(wj.b[ls*4+i]==1){
				color(12);
				cout<<"已";
				color(15);
			} 
			else{
				color(12);
				cout<<"未";
				color(15);
			} 
			cout<<"通过  |";
			if(i!=min(k,4))cout<<"  ";
			else
			cout<<"\n";
		}
		for(int i=1;i<=min(k,4);i++){
			cout<<"|用时：";
			if(wj.b[ls*4+i]==0)
			cout<<"无记录  |";
			else
			{
				int k=wj.time[ls*4+i];
				k/=1000;
				int k1=k,ans=0;
				while(k1){
					ans++;
					k1/=10;
				}
				ans=14-8-ans-(ans==0);
				cout<<k<<"秒";
				while(ans--)cout<<' ';
				cout<<"|";
			}
			if(i!=min(k,4))cout<<"  ";
			else
			cout<<"\n";
		}
		for(int i=1;i<=min(k,4);i++){
			cout<<"----------------";
			if(i!=min(k,4))cout<<"  ";
			else
			cout<<"\n\n\n";
		}
		ls++;
		k-=4;
	}
	return;
}
int zhzfc(string s){
	int tot=0;
	for(int i=0;i<s.size();i++)
	tot=tot*10+s[i]-'0';
	return tot;
}
int kssc(){
	system("cls");
	color(11);
	zk("数独游戏",'-');
	cout<<"\n\n\n\n\n\n\n";
	color(10);
	cout<<"方向键的上下选择，Enter键确定\n\n";
	color(12);
	zk("退出游戏",' ');
	color(15);
	cout<<"\n";
	zk("开始游戏",' ');
	cout<<"\n";
	zk("规则介绍",' ');
	cout<<"\n";
	zk("作者介绍",' ');
	cout<<"\n";
	zk("游戏存档",' ');
	cout<<"\n"; 
	int E=0;
	char s=_getch();
	while(s!=13){
		if(s==72&&E!=0)E--;
		else
		if(s==72&&E==0)E=4;
		if(s==80&&E!=4)E++;
		else
		if(s==80&&E==4)E=0;
		system("cls");
		color(11);
		zk("数独游戏",'-');
		cout<<"\n\n\n\n\n\n\n";
		color(10);
		cout<<"方向键的上下选择，Enter键确定\n\n";
		color(15);
		if(E==0)color(12);
		zk("退出游戏",' ');
		color(15);
		cout<<"\n";
		if(E==1)color(12);
		zk("开始游戏",' ');
		color(15);
		cout<<"\n";
		if(E==2)color(12);
		zk("规则介绍",' ');
		color(15);
		cout<<"\n";
		if(E==3)color(12);
		zk("作者介绍",' ');
		color(15);
		cout<<"\n";
		if(E==4)color(12);
		zk("游戏存档",' ');
		color(15);
		cout<<"\n";
		s=_getch();
	}
	return E;
}
