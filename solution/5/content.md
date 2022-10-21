# 题目
### 题目背景

在上古时代有一位长者，传说中，他的寿数几乎无穷无尽，居所在尘世之外。
他看过人生百态，看过世事变迁，拥有着常人不可及的大智慧。

有一天某个旅行者跌跌撞撞来到了他的居住之处……

### 题目描述

意外之余，这位旅行者想问问长者的年龄，于是同样处于意外的长者决定用一种方式来透露——选择一个进制 $b≥10$，将他真实的年龄 $y$ 转换成 $b$ 进制告诉这位旅行者，这个结果需要满足如下条件：

$1$、每一位的数码都必须在 $[0,9]$ 范围内，这样这个旅行者就会以为这是一个 $10$ 进制的结果，看起来长者的年龄就不会太大。

$2$、将这个结果看作一个 $10$ 进制数的时候，值不能小于 $l$ （比如长者跟别人说自己只有 $10$ 岁的话，显然可信度就不是那么高）。

在满足上述两个条件的同时，他希望报出来的年龄看作十进制尽可能小，也就是 $b$ 尽可能大，给定值 $y$ 和 $l$ ，你的任务就是帮这位长者（不要问为什么他能
联系到你）找到一个合法的条件下最大的 $b$，显然 $b=10$ 是一个平凡的合法解，但不一定最大。

### 输入格式

第一行一个正整数 $T$，表示数据组数。
接下来 $T$ 组数据。每组数据一行三两个正整数 $y, l$，含义如题目所示。

### 输出格式

对每组数据输出一行表示最大的 $b$。

### 样例输入 #1

```
3
32 20
2016 100
9006 96
```

### 样例输出 #1

```
16
42
1000
```

### 【数据规模与约定】
本题一共 $10$ 个测试点，每个测试点 $10$ 分

对于测试点 $1\sim2$，有 $l = 10$

对于测试点 $3\sim4$，有 $y ≤ 10^9$

对于测试点 $5\sim6$，有 $l ≥ 10000$

对于全部测试点，有 $1 ≤ T ≤ 50, 10 ≤ l, y ≤ 10^{18}$

# 思路

我们考虑枚举 $y$ 转成 $b$ 进制时的那个数（记为 $x$）。

首先考虑到 $x$ 不用枚举太多，因为当 $x$ 太大时， $b$ 会很小，那时只需要枚举 $b$ 就行了。

经过本人的多次测试： $x$ 只要枚举到 $1000$ ，剩下到靠枚举 $b$ 即可。
接下来我们考虑枚举 $x$ 怎么做：
①： $x$ 是一个两位数，设它是 $a_1\times 10+b_1$，则我们可以解一个一元一次方程： $a_1\cdot b+a_2=x$ ，可以轻松解出 $b$。

②： $x$ 是一个三位数，设它是 $a_1\times 10^2+a_2\times 10+a_3$，则我们可以解一个一元三次方程： $a_1\times b^2+a_2\times b+a_3=x$ ，即 $a_1\times b^2+a_2\times b+(a_3-x)=0$ ，利用求根公式 $b=\frac{-b±\sqrt{b^2-4\cdot a\cdot c}}{2\cdot a}$ ，可以快速求出根，但是注意要使用 `__int128` 或 `long double` 。

这样枚举 $x$ 就完成了。

接下来考虑枚举 $b$ 怎么做：

将 $b$ 从 `1e6` 开始往下枚举，每次都将 $y$ 转换成 $b$ 进制，然后判断是否有一位大于 $9$，最后再和 $l$ 比较一下即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Int __int128
inline int read();
int T;
int y,l;
int cc[1377];
int cct;
int ans;
inline void zhuan(int x){
	cct=0;
	int p=y;
	while(p){
		cc[++cct]=p%x;
		p/=x;
	}
	for(register int i=1;i<=cct/2;++i)
		swap(cc[i],cc[cct-i+1]);
	return;
}
inline bool check(){
	for(register int i=1;i<=cct;++i){
		if(cc[i]>9)
			return false;
	}
	return true;
}
inline bool cmp(){
	int ans=0;
	for(register int i=1;i<=cct;++i)
		ans=ans*10+cc[i];
	if(ans>=l)
		return true;
	else
		return false;
}
__int128 Sqrt(Int x){
	Int L=1,R=1000000000000000;
	while(L<R){
		Int mid=(L+R)/2;
		if(mid*mid<x)
			L=mid+1;
		else
			R=mid;
	}
	for(Int i=L-5;i<=L+5;++i)
		if(i*i<=x&&(i+1)*(i+1)>x)
			return i;
	return -1;
}
signed main(){
	freopen("age.in","r",stdin);
	freopen("age.out","w",stdout);
	T=read();
	while(T--){
		ans=0,y=read(),l=read();
		for(register int i=max(l,10ll);i<=99;++i){
			int a=i/10,b=i%10;
			if((y-b)%a==0)ans=max(ans,(y-b)/a);
		}
		for(register int i=max(l,100ll);i<=999;++i){
			Int a=i/100,b=i/10%10,c=i%10-y,nick=b*b-4*a*c;
			if(nick<0)continue;
			nick=Sqrt(nick);
			Int p1=(-b+nick)/(a*2),p2=(-b-nick)/(a*2);
			for(int pp=1;pp<=2;pp++)
			{
				Int L=p1-20,R=p1+20;
				if(L<10)L=10;
				for(Int xp=L;xp<=R;++xp){
					Int sum=a*xp*xp+b*xp+c;
					if(sum==0){
						if(xp>ans)ans=xp;
						break;
					}
				}
				swap(p1,p2);
			}
		}
		for(register int i=1e6;i>=10;--i){
			if(i<ans)break;
			zhuan(i);
			if(!check())continue;
			if(cmp()){
				ans=max(ans,i);
				break;
			}
		}
		printf("%llu\n",ans);
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

[about me](https://www.github.com/yyf525)
