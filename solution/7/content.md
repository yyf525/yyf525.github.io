# 题目
### 题目描述

白头鹰作为美丽国的国鸟，每天都会进行数学演算的工作。

今天，他得到了 $3$ 个整数$a, b, p$，其中 $p$ 是一个质数，以及一个函数 $f(x, y)$。

函数$f(x,y)$如下定义：

- 令整数$v = ab + xy$。
- 如果$v$是$p$的倍数，则$f(x, y) = 1$。
- 否则，令整数$u = ax + by$，$f(x, y) = u * inv_p(v) \% p$。其中$inv_p(v)$表示$v$在模$p$意义下的乘法逆元。

白头鹰获得了一个整数$k$，且需要计算一下式子：

$$f(f(...f(f(f(k, k-1), k-2), ..., 2), 1)$$

### 输入格式

一行四个整数$a, b, p, k$。

### 输出格式

一行一个整数，表示式子的值。

### 样例输入 #1

```
2 4 5 3
```

### 样例输出 #1

```
4
```

### 样例输入 #2

```
1 1 2 10
```

### 样例输出 #2

```
1
```

### 【数据规模与约定】

对于$20\%$的数据，$2 \leq k \leq 10^{6}$。

对于$50\%$的数据，$2 \leq p \leq 5000$。

对于$100\%$的数据：$2 \leq p \leq 10^{9}+7, 1 \leq a, b \leq min(p-1, 10^{5}), 2 \leq k \leq 10^{18}$。

# 思路

题目让我们求 $f(...f(f(k, k-1), ...1)$，但我们可以观察到：当 $y=a$ 时，$f(x,y)=1$，理由如下：

首先 $v=u=y\cdot (b+x)$，那么 $u$ 乘上自己的逆元肯定还是 $1$。

所以：$f(...f(f(k, k-1), ... 1)=f(\cdots f(f(1,a-1),a-2),\cdots 1)$，又因为 $a\le 10^5$，所以直接暴力算即可。



# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,B=50137;
inline int read();
int a,b,p,k,lstans=1;
int qow(int x,int y,int mod){
	int ans=1;
	while(y){
		if(y&1)
			ans=ans*x%mod;
		y>>=1,x=x*x%mod;
	}
	return ans;
}
int ny(int a){
	return qow(a,p-2,p);
}
int f(int x,int y){
	int v=a*b+x*y;
	if(v%p==0)return 1;
	else return (a*x%p+b*y%p)%p*ny(v%p)%p;
}
int work(int a,int b,int p,int k){
	for(int i=k-1;i>=1;i--){ 
		lstans=f(lstans,i);
	}
	return lstans;
}
signed main(){
	freopen("eglen.in","r",stdin);
	freopen("eglen.out","w",stdout);
	cin>>a>>b>>p>>k;
	printf("%lld\n",work(a,b,p,a));
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}

```

[about me](https://www.github.com/yyf525)