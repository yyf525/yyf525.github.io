## 一：定义

若在一张图中存在一个路径，它经过了所有的边，则称它为原图的**欧拉路径**，若这个路径是一个回路，那么它也叫作原图的**欧拉回路**。

+ 若一张图有**欧拉路径**却没有**欧拉回路**，则称它为**半欧拉图**。
+ 若一张图有**欧拉回路**，则称它为**欧拉图**。

如图：![](https://cdn.luogu.com.cn/upload/image_hosting/ib3nl5no.png)

那么根据之前的定义：图1是半欧拉图，图2是欧拉回路。

## 二：欧拉路的求法

首先对于欧拉路，我们有一些结论：

### 一：对于欧拉路径

+ 有向图：起点的**入度比出度少1**，终点的**入度比出度多1**，其余点**入度和出度相同**。

+ 无向图：起点和终点的**度数为奇数**，其余点的**度数为偶数**。

### 二：对于欧拉回路

+ 有向图：所有点的**入度出度相同**。

+ 无向图：所有点的**度数皆为偶数**。

### 三：程序

我们目前常用的就是 `Hierholzer` 算法。它的算法主要思路就是：

+ 从一个可行的起点开始 `dfs`
+ 枚举它的每一条出边，递归下去，并将那条边删除
+ 递归完后，将点压入一个栈
+ 把栈里的数据输出即是欧拉路径

### 四：示例

$\texttt{I.}$ **邻接矩阵版**

```cpp
void dfs(int now){
    for(int i=1;i<=n;i++){
        if(g[now][i]){
            g[now][i]=g[i][now]=0;//删边
            dfs(i);
		}
    }
    ans.push(now);
    return;
}
void print(){
    do{
        printf("%d->\n",ans.top());
    }while(ans.pop(),ans.size());
    return;
}
```

时间复杂度 $\Theta(n^2)$

$\texttt{II.}$ **链式前向星版**

```cpp
//注：无向图，链式前向星从1开始编号，即1对应2,4对应3
bool vis[N];
int Tot[N],ns;
void dfs(int now){
    Tot[now]++;
    int Tnow=Tot[now];
    for(int i=h[now];i;i=e[i].nxt){
        h[now]=e[i].nxt;
        int y=e[i].to;
        if(vis[i])continue;
        vis[i]=vis[i+i%2*2-1]=1;
        dfs(y);
        if(Tot[now]>Tnow)break;//递归后面的时候已经做好了，不需要再做了
    }
    ans.push(now);
    return;
}
void print(){
    do{
        printf("%d->\n",ans.top());
    }while(ans.pop(),ans.size());
    return;
}
```

时间复杂度临近 $\Theta(m)$

## 三：例题部分

### 1.P1341 无序字母对  

#### 题目

[题目链接](https://www.luogu.com.cn/problem/P1341)

题目大意就是给你 $n$ 个无序字母对（大小写不同，但是位置可以调换），让你构造一个 $n+1$ 长的字符串，使得任意相邻两个字母都在无序字母对中出现过，并求出字典序最小的答案。

#### 做法

思路：主体思路就是对于每一个字母对的两个字母连一条无向边，然后跑一边欧拉回路即可。

注意事项：

+ 此题要判联通，这里介绍两种方式：①并查集，②跑完欧拉回路之后看点数是否符合。

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5,C=137;
inline int read();
int f[C],du[C],ans[N];
bool G[C][C];
int top,s,cnt,n,sum,p1,p2;
char c1,c2;
int get(int x){
	if(f[x]==x)return x;
	return f[x]=get(f[x]);
}
void hb(int x,int y){
	int fx=get(x),fy=get(y);
	f[fx]=fy;
	return;
}
char Got(){
	char c=getchar();
	while(c<'A'||c>'Z'&&c<'a'||c>'z')c=getchar();
	return c;
}
void add(int u,int v){
	G[u][v]=1;
	return;
}
void dfs(int u){
	for(int i=1;i<C;i++)if(G[u][i]){
			G[u][i]=G[i][u]=0;
			dfs(i);
		}
	ans[++top]=u;
	return;
}
signed main(){
	n=read();
	for(int i=1;i<C;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		c1=Got(),c2=Got(),p1=c1,p2=c2;
		du[p1]++,du[p2]++;
		add(p1,p2);add(p2,p1);hb(p1,p2);
	}
	for(int i=1;i<C;i++)if(du[i]&&f[i]==i)
		sum++;                         
	for(int i=C-1;i>=0;i--)if(du[i]&1)
		s=i,cnt++
	if(sum!=1||cnt!=0&&cnt!=2){
		cout<<"No Solution\n";
		return 0;
	}
	dfs(s);
	while(top--)cout<<(char)ans[top+1];
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

### 2.Plays on words

#### 题目

[题目链接](http://poj.org/problem?id=1386)

题目大意就是给你 $n$ 个字符串，若两个字符串头尾相同即可拼在一起，问是否能把这 $n$ 个字符串拼在一起？

#### 思路

我们可以考虑到：一个字符串，只有它最**前面的字符和最后面的字符有用**，其余的字符我们可以不用考虑，因为两个字符串头尾相同即可拼在一起，所以我们对于每个字符串的最前和最后两个字符连一条**有向边**，最后判断是否存在**欧拉路径**即可。接下来我们回顾一下**有向图**判断**欧拉路径**的条件：

①：该图联通。

②：只有 $0$ 个或 $2$ 个点的入度出度相差 $1$，其余入度出度全部相同。

那么本题就做完了。

#### 代码：

主体代码：

①：并查集部分

```cpp
struct ASS{//并查集 
	int fa[C];
	void init(){
		for(int i=1;i<C;i++)
			fa[i]=i;
	}
	int find(int x){
		return (fa[x]==x?x:(fa[x]=find(fa[x])));
	}
	void merge(int x,int y){
		int fx=find(x),fy=find(y);fa[fx]=fy;
	}
	bool check(){
		int sum=0;
		for(int i=1;i<C;i++)if(in[i]+out[i]>0&&fa[i]==i)sum++;
		return (sum==1);
	}
}ASS;
```

②：判断部分

```cpp
bool core(){
	if(!ASS.check()){
		return 0;
	}
	for(int i=1;i<C;i++){
		if(in[i]!=out[i]){
			if(in[i]!=out[i]+1&&in[i]!=out[i]-1)return 0;
			sum++;
		}
	}
	if(sum!=0&&sum!=2){
		return 0;
	}
	return 1;
}
```

[ about me ](https://github.com/yyf525)
