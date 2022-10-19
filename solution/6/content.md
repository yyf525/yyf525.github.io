# 题目
### 题目描述

小 $Y$ 最近喜欢上了一个棋盘游戏，这个棋盘游戏提供一个 $n\times m$ 大小的棋盘和一种棋子——守卫，其攻击范围为其所在行、所在列以及其周围的 $8$ 个格子。

游戏的目标是通过合理摆放棋子，使得任意两个守卫之间都不能攻击到对方。

显然这个游戏实在是太简单了，于是小 $Y$ 又想到了这样一个问题：在一个合法方案的基础上，均匀随机地选择一个空格子作为起点，再均匀随机地选择一个空格子作为终点，那么这两个格子间不经过任意守卫的最短路的期望长度是多少
（如果起终点相同，那么这个长度视为 $0$ ）。

### 输入格式

第一行输入一个正整数 $T$，表示数据组数。
接下来 $T$ 组数据，每组数据的第一行有两个整数 $n,m$，表示棋盘的大小。接下来 $n$ 行，每行 $m$ 个字符，描述这个棋盘，字符为 `#` 则表示该位置为空，为 `G` 则表示该位置有守卫，保证这个棋盘状态合法。

### 输出格式

对每组数据单独的一行表示答案，你的最终答案请使用 `printf` 的保留 $4$ 位小数形式进行输出，建议对所有路径求和完再进行除法。

### 样例输入 #1

```
2
2 2
##
G#
2 5
###G#
#G###
```

### 样例输出 #1

```
0.8889
2.6250
```

## 【样例解释】
第一组数据中，$3$ 个空位一共有 $9$ 种可能性，其中 $3$ 种情况最短路径长度为 $0$，$4$ 种情况长度为 $1$，$2$ 种情况长度为 $2$，因此期望值为 $\frac{8}{9}$。

### 【数据规模与约定】

本题一共 $10$ 个测试点，每个测试点 $10$ 分。

对于测试点 $1\sim3$，有 $n,m≤30$。

对于测试点 $1,4,5$，棋盘上守卫数量不超过 $1$。

对于测试点 $6\sim10，有2≤n,m≤1000, 1≤T≤50$, 单个测试点的 $n\cdot m$ 之和不超过 $3000000$。

# 思路

对于此题有结论：

结论一：对于任意两个没有守卫的格子，之间的最短路长度为它们的哈密顿距离 $l$ 或哈密顿距离 $l+2$。

结论二：若这两点之间的行编号差大于其列编号差，且一个偏左上，一个偏右下，则最短路长度为它们的哈密顿距离 $l+2$ 的充分必要条件是这两个点所在列以及之间的所有列都有守卫，且从左到右每个守卫的行编号递增。

**【证明】**

不妨设两个格子一个偏左上，一个偏右下，且行编号差不小于其列编号差。

构造一条路线：

若起点行在起点与终点的列区间内没有守卫，那么从左上角先向右走直到与另一个格子位于同一列，再向下走，若遇到守卫就向左走一格、向下走两格再向右走一格（因为守卫会控制周围的 $8$ 个格子，所以这些格子必然是能走的）。因为每一列至多有一个守卫，所以这样的路线构造长度至多为 $l+2$。

若起点行在起点与终点的列区间内有一个守卫，那么从左上角向右走到该守卫的前一格，向下走一格再向右走一格，接着向下走直到与右下角位于同一行，最后向右走，遇到守卫就绕开即可。这样的路线构造长度也至多为 $l+2$。

最短路径长度不小于哈密顿距离 $l$，这是显然的。又有染色法，长度奇偶性必然与哈密顿距离相同，故第一条结论得证。

对于第二条结论：先证充分性。如图所示，容易得到左上角的点一定在画出来的格子的上方，而右下角的点一定在画出来的格子的下方。将守卫按如图所示连法连成一条折线，那么若要从左上角走到右下角，必须经过这条折线，也就是必然会向左走，那么长度必然超过了哈密顿距离。

<img src="https://molmin.github.io/problem/43/1.png" width=180px>

再证必要性。若有一列没有守卫，那么直接向右走到该列，向下走直到到达与右下角格子所在行，再向右走，那么长度就是哈密顿距离，故所有列都有守卫是最短路长度为它们的哈密顿距离 $l+2$ 的必要条件。

若从左到右每个守卫的行编号不为递增，即存在两列 $x_0$ 和 $x_0+1$，这两列的守卫行编号中，$x_0$ 列上的较大。那么构造如下路径：从左上角开始，向右走到 $x_0$ 列，再向下走到该列守卫的上面一格，又由于这个守卫控制了周围 $8$ 个格子，故可以向右走一格，再向下走直到与右下角格子位于同一行，最后向右走即可。

故**这两个点所在列以及之间的所有列都有守卫，且从左到右每个守卫的行编号递增**是最短路长度为它们的哈密顿距离 $l+2$ 的必要条件。

**证毕。**

为方便描述，我们不考虑两点顺序，在输出时将答案乘 $2$。

首先假设任意两个没有守卫的格子 $A,\ B$ 最段路均为它们的哈密顿距离。那么距离之和可以分为两部分求：

我们枚举 $A$，设 $A$ 的行编号为 $x_0$，列编号为 $y_0$。那么这部分的答案为

**第一部分、$\bf{A}$ 的行编号比 $\bf{B}$ 的大，列编号比 $\bf{B}$ 的小。**
$$
\begin{aligned}
  & \sum_{x=1}^{x_0-1}\sum_{y=y_0+1}^{m}(x_0-x+y-y_0) \\
= & (x_0-y_0)(x_0-1)(m-y_0)-\sum_{x=1}^{x_0-1}\sum_{y=y_0+1}^{m}(x-y).
\end{aligned}
$$

我们考虑二维前缀和。记

$$
sum1_{x,\ y}=\sum_{a=1}^{x}\sum_{b=y}^{m}(a-b).
$$

则答案为
$$
(x_0-y_0)(x_0-1)(m-y_0)-sum1_{x_0-1,\ y_0+1}
$$


那么这部分的答案就可以 $\Theta(nm)$ 解决。

**第二部分、$\bf{A}$ 的行编号和列编号都比 $\bf{B}$ 的大。**

枚举 $A$，设 $A$ 的行编号为 $x_0$，列编号为 $y_0$。那么这部分的答案为

$$
\begin{aligned}
  & \sum_{x=1}^{x_0-1}\sum_{y=1}^{y_0-1}(x_0-x+y_0-y) \\
= & (x_0+y_0)(x_0-1)(y_0-1)-\sum_{x=1}^{x_0-1}\sum_{y=1}^{y_0-1}(x+y).
\end{aligned}
$$

我们考虑二维前缀和。记

$$
sum2_{x,\ y}=\sum_{a=1}^{x}\sum_{b=1}^{y}(a+b).
$$

则答案为
$$
(x_0+y_0)(x_0-1)(y_0-1)-sum2_{x_0-1,\ y_0-1}
$$


那么这部分的答案也可以 $\Theta(nm)$ 解决。

**第三部分、$\bf{A}$的行编号与列编号中有一个与$\bf{B}$相等**

$\texttt{I.}$ 行编号相等

则答案就是
$$
\begin{aligned}
  & \sum_{i=1}^{y_0-1}i+\sum_{i=1}^{m-y_0}i \\
= & \frac{y_0\cdot (y_0-1)+(m-y_0)\cdot (m-y_0+1)}{2}
\end{aligned}
$$
$\texttt{II.}$ 列编号相等

则答案就是
$$
\begin{aligned}
  & \sum_{i=1}^{x_0-1}i+\sum_{i=1}^{n-x_0}i \\
= & \frac{x_0\cdot (x_0-1)+(n-x_0)\cdot (n-x_0+1)}{2}
\end{aligned}
$$


**第四部分、剩余的贡献**

然后考虑如何统计多出 $2$ 的长度的点对数量。因为这两点之间的行编号差小于其列编号差与这两点之间的行编号差大于其列编号差是类似的，所以下面只讨论这两点之间的**行编号差大于其列编号差**的情况。

从左到右枚举列编号较小的点的列编号 $y_0$，显然 $y_0$ 列上必须有守卫。再从 $y_0$ 列开始向右枚举列编号较大的点的列编号 $y_1$。考虑每遇到一个新的列，可以作为结果的条件：这一列必须有守卫，并且守卫的行坐标与之前列守卫的行坐标同为增长（可以为负增长）趋势。所以如果新的列不符合这个条件，就可以直接结束 $y_1$ 的枚举。

下面统计答案。对于每个合法的 $y_0$ 和 $y_1$，设守卫的最小行编号为 $x_0$，最大行编号为 $x_1$，则其中一个点的行编号必须小于 $x_0$，另一个点的行编号必须大于 $x_1$。由乘法原理可得这样的点对数量为

$$
(x_0-1)(n-x_1).
$$
注：本文原作者**milmon**，本人只是进行了一些修改。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define int long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=1e3+50;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
bool mp[N][N];
int sum1[N][N];
int sum2[N][N];
int hasx[N];
int hasy[N];
int s1[N][N];
int s2[N][N];
int T,n,m,ans,state,cnt;
char c;
int X0,Y0,X1,Y1,LX,LY,i,j;
int got1(int p1,int p2){
	if(state==1)return 4*(p1-1)*(n-p2);
	else return 4*(p2-1)*(n-p1);
}
int got2(int p1,int p2){
	if(state==1)return 4*(p1-1)*(m-p2);
	else return 4*(p2-1)*(m-p1);
}
void init(){
	for(int i=1;i<N;i++){
		hasx[i]=hasy[i]=0;
		for(int j=1;j<N;j++)
			s1[i][j]=s2[i][j]=sum1[i][j]=sum2[i][j]=mp[i][j]=0;
	}
}
void solve(){
	n=read(),m=read(),ans=0,cnt=n*m,init();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			c=getchar();while(c!='G'&&c!='#')c=getchar();
			if(c=='G')mp[i][j]=1,hasx[i]=j,hasy[j]=i,cnt--;
		}
	}
	for(i=1;i<=n;i++){
		for(j=m;j>=1;j--){
			s1[i][j]=s1[i][j+1]+s1[i-1][j]-s1[i-1][j+1]+1-mp[i][j],
			sum1[i][j]=sum1[i][j+1]+sum1[i-1][j]-sum1[i-1][j+1];
			if(!mp[i][j])sum1[i][j]+=i-j;
		}
		for(j=1;j<=m;j++){
			s2[i][j]=s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1]+1-mp[i][j],
			sum2[i][j]=sum2[i-1][j]+sum2[i][j-1]-sum2[i-1][j-1];
			if(!mp[i][j])sum2[i][j]+=i+j;
		}
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(!mp[i][j])
				ans+=(i-j)*s1[i-1][j+1]-sum1[i-1][j+1],ans+=(i+j)*s2[i-1][j-1]-sum2[i-1][j-1];
	ans*=2;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(mp[i][j])continue;
			ans+=((j*(j-1)+(m-j)*(m-j+1))+(i*(i-1)+(n-i)*(n-i+1)))/2;
			if(hasx[i])ans-=abs(hasx[i]-j);
			if(hasy[j])ans-=abs(hasy[j]-i);
		}
	}
	for(X0=1;X0<=n;X0++){
		if(!hasx[X0])continue;
		LY=Y0=hasx[X0],ans+=got2(Y0,Y0),state=0;
		for(X1=X0+1;X1<=n;X1++){
			if(!hasx[X1])break;
			Y1=hasx[X1];
			if(state==0)
				if(Y1>Y0)state=1;
				else state=-1;
			else
				if(state==1&&Y1<LY||state==-1&&Y1>LY)break;
			ans+=got2(Y0,Y1),LY=Y1;
		}
	}
	for(Y0=1;Y0<=m;Y0++){
		if(!hasy[Y0])continue;
		LX=X0=hasy[Y0],ans+=got1(X0,X0),state=0;
		for(Y1=Y0+1;Y1<=m;Y1++){
			if(!hasy[Y1])break;
			X1=hasy[Y1];
			if(state==0)
				if(X1>X0)state=1;
				else state=-1;
			else
				if(state==1&&X1<LX||state==-1&&X1>LX)break;
			ans+=got1(X0,X1),LX=X1;
		}
	}
	printf("%.4lf\n",ans*1.0/(1.0*cnt*cnt));
}
signed main(){
	T=read();
	while(T--){
		solve();
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

[about me](https://www.github.com/yyf525)