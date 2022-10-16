# 题目

### 题目描述

小 $Z$ 要进行物理实验，需要 $T$ 个电阻，每个电阻所需要的电阻值都可以用一个分数进行表示。

但很不幸的是，物理实验室只有阻值为 $1$ 的电阻和电阻可以忽略不计的导线，好在这些物品有无限多个。

于是小 $Z$ 打算通过串并联的方式尝试构造自己所需要的每个电阻，对于每个电阻，小 $Z$ 都会从一个阻值为 $1$ 的电阻开始，每次在原有的电路基础上串联或者并联一个阻值为 $1$ 的电阻，他想知道对于自己所需要的每个阻值，最少需要使用多少个阻值为 $1$ 的电阻才能拼出来。

### 输入格式

第一行为一个正整数 $T$，表示数据组数，接下来 $T$ 组数据，每组数据一行两个整数 $A,B$ ，表示需要一个阻值为 $A/B$ 的电阻。

### 输出格式

对每组数据输出一行一个非负整数，表示答案。

### 样例输入 #1

```
2
2 3
5 2
```

### 样例输出 #1

```
3
4
```

### 【样例解释】
第一组数据中，从一个阻值为 $1$ 的电阻开始，并联一个阻值为 $1$ 的电阻，再串联一个阻值为 $1$ 的电阻即可。
### 【数据规模与约定】

本题一共 $10$ 个测试点，每个测试点 $10$ 分。

第 $1\sim 3$ 个测试点，满足 $T,A,B≤20$

所有测试点均满足 $1≤T ≤1000 ; 1 ≤ A,B ≤ 10^{18}$

# 思路

题意大概就是用一些阴值为 $1$ 的电阻，去串联或并联其余阴值为 $1$ 的电阻，求出操作后最终值为 $\frac{A}{B}$ 最少需要几个电阻。

我们设当前的阴值 $\frac{Q}{P}$，则串联一个阴值为 $1$ 的电阻后，阴值会变为 $\frac{Q+P}{P}$，并联一个阴值为 $1$ 的电阻后，阴值会变为 $\frac{Q}{P+Q}$，可以发现要么操作一次后要么是分母加分子，要么是分子加分母。

而且我们还可以发现一个性质：我们记 $f(\frac{A}{B})$ 表示让阴值成为 $\frac{A}{B}$ 所需的电阻数，则 $f(\frac{A}{B})=f(\frac{B}{A})(A>B)$。

证明：我们假设 $A$ 和 $B$ 满足上面的性质，则说明 $f(\frac{A}{B})=f(\frac{B}{A})$，那么 $f(\frac{A+B}{A})=f(\frac{B}{A})+1$，$f(\frac{A}{A+B})=f(\frac{A}{B})+1$，因为 $f(\frac{A}{B})=f(\frac{B}{A})$，所以 $f(\frac{A+B}{B})=f(\frac{A}{A+B})$。而数归的起点是 $A=1,B=1$。

所以我么就可以得出我们的算法：

$f(\frac{A}{B})=\begin{cases}B=0~~~~ ~~0\\A≥B~~~ \left \lfloor \frac{A}{B} \right  \rfloor+f(\frac{A\bmod B}{B}) \\A<B~~~~ f(\frac{B}{A})\end{cases}$

容易看出这是一个递归，即可实现。

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
const int N=2e5;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int T,a,b;
int get(int n,int m){
	if(m==0)
		return 0;
	if(n<m)
		return get(m,n);
	return n/m+get(n%m,m);
}
signed main(){
	T=read();
	while(T--){
		a=read(),b=read();
		int ss=__gcd(a,b);
		a/=ss;
		b/=ss;
		printf("%lld\n",get(a,b));
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}

```

[about me](https://www.github.com/yyf525)