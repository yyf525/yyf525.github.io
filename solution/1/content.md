[题目传送门](https://www.luogu.com.cn/problem/P5766)

## 题目大意

给你一个整点集 $V$，让你求出它的一个子集 $B$，使得 $B$ 中任意两个整点都联通，且 $B$ 的点权和最大。

## 题目思路

因为题目中说了需要 $B$ 联通，所以我们不妨把所有相邻的点以父子关系存进一张图中，这样当我们取到以 $u$ 为根的子树时，可以保证它和下面每一个点联通。

接下来就是树形 $\texttt{DP}$ 了，我们设 $f_{x}$ 表示以 $x$ 为根的子树中，选取 $x$ 所得到的最大值。则转移方程为（设 $y_1,y_2\cdots y_t$ 为 $x$ 的子节点） 对于它的所有子节点 $f_{y_i}(1\le i\le x$) 若 $f_{y_i}>=0$，则加上 $f_{y_i}$，最后加上 $val_{x}$，即可得出转移式。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define ll long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline int read();
inline void write(int ans);
inline void put(int x,char c);
const int N=2e5;
int n;
struct sa{
	int nxt;
	int to;
}e[N];
struct node{
	int x,y,val;
	void in(){
		x=read();
		y=read();
		val=read();
	}
};
node a[N];
bool check(int u,int v){
	if(abs(a[u].x-a[v].x)+abs(a[u].y-a[v].y)==1)return true;
	return false;
}
int f[N];
int h[N],cnt,maxn;
void add(int u,int v){
	e[++cnt]=(sa){h[u],v};h[u]=cnt;
	return;
}
void dfs(int x,int fa){
	f[x]=a[x].val;
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa)continue;
		dfs(y,x);
		if(f[y]>0)f[x]+=f[y];
	}
	return;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].in();
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(check(i,j))add(i,j),add(j,i);
		}
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)maxn=max(maxn,f[i]);
	put(maxn,'\n');
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}

```