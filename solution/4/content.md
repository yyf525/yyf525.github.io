# 题目
### 题目描述

有一个 $1\sim n$ 的排列 $a_1,a_2,\cdots,a_n$ ，每次操作可以删去其中的一个数，并选择一个当前与这个数相邻的数记录到一个初始为空的序列 $b$ 的末尾，删去之后剩下的部分按顺序拼接在一起成为一个新的序列，这样进行 $k$ 次操作可以得到一个长度为 $k$ 的序列 $b_1,b_2, \cdots, b_k$。比如排列 $3~1~2$ 上，可以删除 $1$ 记录 $2$，得到 $a$ 序列 $3~2$，再删除 $2$ 记录 $3$；两次操作后 $b$ 序列为 $2~3$。

给定一个元素互不相同的序列 $b$，求有多少种可能的操作序列，两个操作序列不同，当且仅当某一步删除的元素不同，输出总方案数模 `998244353` 的结果。

### 输入格式

第一行一个正整数 $T$，表示数据组数。

接下来 $T$ 组数据，每组数据第一行两个正整数 $n,k$ ，含义如题目所示，接下来一行 $n$ 个整数，表示排列 $a$，再接下来一行 $k$ 个整数表示序列 $b$。

### 输出格式

对每组数据输出一行表示答案。

### 样例输入 #1

```
3
5 3
1 2 3 4 5
3 2 5
4 3
4 3 2 1
4 3 1
7 4
1 4 7 3 6 2 5
3 2 4 5
```

### 样例输出 #1

```
2
0
4
```


### 【样例解释】

第一组数据中，第一次操作只能删除 $4$，第二次操作可以删除 $1$ 或者 $3$，第三次操作只能删除 $5$ 旁边的那个数，所以一共 $2$ 种操作序列。

第三组数据的可能的操作序列：删除$7~6~1~2，7~6~3~2，6~3~1~2，6~3~7~2$。

### 【数据规模与约定】
本题一共 $10$ 个测试点，每个测试点 $10$ 分。

对于测试点 $1\sim 3$，有 $2 ≤ T,n ≤ 9$

对于测试点 $4\sim 6$，$b$ 排列中的元素在 $a$ 中的位置下标为递增序列

所有测试点均满足 $1 ≤ T ≤ 100 ; 1 ≤ k < n ≤ 200000 ; 1 ≤ a_i, b_j ≤ n$，每组数据中序列 $a,b$ 的元素各互不相同，每个测试点中 $n$ 的和不超过 $200000$。

# 思路

当一个数在 $a$ 序列中的 $x$ 在 $b$ 序列中，设 $y$ 在它 $a$ 序列中 $x$ 的左边，$z$ 在 $a$ 序列中 $x$ 的右边。若要删 $y$ 记录 $x$ 则必须 $y$ 不在 $b$ 序列中，或者 $y$ 在 $b$ 序列中的位置比 $x$ 在 $b$ 序列前面才可以（显然），$z$ 同理。

接下来我们考虑证明删掉一个数，对于后面的数没有影响。

假设这个数是 $x$，它左边是 $x_1$，$x_1$ 左边是 $x_2$，$x_2$ 左边是 $x_3,\cdots,x_{p-1}$ 左边是 $x_p$，其中 $x,x_1,\cdots,x_p$ 都是 $b$ 序列中的数。

那么命题等价于证明在删除 $x$ 前删除 $x_1$ 没有影响。

证：首先删除 $x_1​$ 一定是为了标记 $x​$，而为了标记 $x_1​$ 只能删除 $x2​$，$\cdots​$ 为了标记 $x_{p-1}​$ 只能删除 $x_p​$，那么 $x_p​$肯定是由 $x_p​$ 前面的数删除而标记。且 $x_p​$ 前面一定会有数。

故我们的策略是：对于一个在 $b$ 序列中的数 $a_i$，则我们记一个 $s\gets 0$，当 $a_{i-1}$ 不在 $b$ 序列中或者 $a_{i-1}$ 在 $b$ 序列中的位置比 $a_i$ 在$b$ 序列中的位置小时， $s\gets s+1$；当 $a_{i+1}$ 不在 $b$ 序列中或者 $a_{i+1}$ 在 $b$ 序列中的位置比 $a_i$ 在 $b$ 序列中的位置小时，$s\gets s+1$,然后让 $ans\times s$ 即可。

于是我们就解决了本题。

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
const int N=2e5+20,mod=998244353;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int T;
int n,k;
int a[N];
int b[N];
int rnk[N];
int ans;
signed main(){
	T=read();
	while(T--){
		n=read(),k=read();
		memset(rnk,0,sizeof rnk);
		ans=1;
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int i=1;i<=k;i++)
		{
			b[i]=read();
			rnk[b[i]]=i;
		}
		for(int i=1;i<=n;i++){
			if(!rnk[a[i]])
				continue;
			int xs=0;
			if(i>1&&rnk[a[i-1]]<rnk[a[i]])xs++;
			if(i<n&&rnk[a[i+1]]<rnk[a[i]])xs++;
			ans=ans*xs%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

[about me](https://www.github.com/yyf525)