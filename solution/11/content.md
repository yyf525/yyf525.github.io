[题目链接](https://www.luogu.com.cn/problem/CF461B)

## 题目大意

给你一颗 $n$ 个点的树，每个节点是黑色或白色，你可以删去一些边，是的删完后每个连通块都有且仅有一个黑色节点。求符合条件的删边方法数，答案对 $10^9+7$ 取模。数据范围：$1\le n \le 10^5$。

## 思路

看到这种有关树的题目，自然想到动态规划。

我们设 $f_{x,0}$ 表示以 $x$ 为根的子树中，$x$ 所在的连通块没有黑点，$f_{x,1}$ 表示以 $x$ 为根的子树中，$x$ 所在的连通块有且仅有一个黑点，易得 $f_{1,1}$ 为最终答案。

我们不妨设 $son_x$ 表示 $x$ 的儿子的集合，$y$ 为 $x$ 的儿子。

先考虑 $f_{x,0}$ 的转移。

$\texttt{I.}x$  是一个白点：

若 $y$ 所处的连通块内   没有黑点，则一定要连向 $x$，若有黑点，则一定不能连向 $x$。

故方案数为 $\prod\limits_{y\in son_x} f_{y,0}+f_{y,1}$。

$\texttt{II.}x$ 是一个黑点：

不可能，直接跳过。

在考虑 $f_{x,1}$ 的转移。

$\texttt{I.}x$ 是一个白点。

则要求 $y$ 所处的连通块一定要有黑点，故方案数为 $\sum\limits_{y\in son_x} f_{x,0}\cdot f_{y,1}$。

$\texttt{II.}x$ 是一个黑点。

则 $y$ 所处的连通块有无黑点都可以：因为如果有黑点，那么就断开这条边；若没有黑点，那么就连上这条边。故方案数为 $\sum\limits_{y\in son_x} f_{x,1}\cdot (f_{y,0}+f_{y,1})$。

那么转移式就推完了，下面整理一下：

对于每个 $x$ 的儿子 $y$，都做如下转移：

$f_{x,1}=f_{x,1}\cdot (f_{y,0}+f_{y,1})+f_{x,0}\cdot f_{y,1}$。

$f_{x,0}=f_{x,0}\cdot (f_{y,0}+f_{y,1})$。

**注意**：一定要分好 $f_{x,0}$ 和 $f_{x,1}$ 的顺序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=1e9+7;
inline int read();
int n;
struct sa{
    int nxt;
    int to;
}e[N<<2];
int h[N],cnt,u;
void add(int u,int v){
    e[++cnt]=(sa){h[u],v};
    h[u]=cnt;
    return;
}
bool val[N];
int f[N][2];
void dfs(int x,int fa){
    for(int i=h[x];~i;i=e[i].nxt){
        int y=e[i].to;
        if(y==fa)continue;
        dfs(y,x);
        int tmp1=f[x][1]*((f[y][0]+f[y][1])%mod)%mod;
        int tmp2=f[x][0]*f[y][1];
        f[x][1]=(tmp1+tmp2)%mod;
        f[x][0]=f[x][0]*((f[y][0]+f[y][1])%mod)%mod;
    }
    return;
}
signed main(){
    memset(h,-1,sizeof h);
	n=read();
    for(int i=1;i<n;i++){
        u=read();
        add(u,i);
        add(i,u);
    }
    for(int i=0;i<n;i++){
        val[i]=read();
        f[i][val[i]]=1;
    }
    dfs(0,-1);
    printf("%lld\n",f[0][1]);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```
