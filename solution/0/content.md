题目传送门：[CF568A](https://www.luogu.com.cn/problem/CF568A)

# 题意分析：

定义 $\pi(n)$ 为 $n$ 以内的素数个数，$\text{rub}(n)$ 为 $n$ 以内的回文数个数，并输入两个数 $p$ 和 $q$，让你求最大的 $n$ 使得 $\pi(n)\le \frac{p}{q}\times \text{rub}(n)$。

# 思路：

我们为式子移个项：

 $$\pi(n)\le \frac{p}{q}\times \text{rub}(n) \Rightarrow q\times\pi(n)\le p\times \text{rub}(n)$$

我们只需要求出一到N中所有的 $\pi(i)$ 和 $\text{rub}(i)$ 即可。

又因为题目中给出 $p,q\le 10^4,\frac{1}{42}\le\frac{p}{q}\le42$  ,再经过打表测试可知，最大范围N在 $2e6$ 左右。

# 算法分析

 $\pi(i)$ 我们是可以用线性筛 $O(N)$ 求出的，而 $\text{rub}(i)$ 我们之间暴力枚举即可，复杂度 $O( \log N)$ 。所以，总时间复杂度为 $O( \log N)$ 。

而 $N=2\times10^6$ ，且这个 $\log$ 是以 $10$ 为底数的，所以不会超时。

# AC code:

我们用 $sum_i$ 记录 $\le i$ 的质数数量，$tot_i$ 记录 $\le i$ 的回文数数量。

然后预处理出 $1 \sim N$ 中所有的回文数数量和质数数量，然后找出最大答案即可。

若没有，则输出 `Palindromic tree is better than splay tree` 。
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int p,q,cnt;
int prime[N],b[N];
int sum[N],tot[N];
void primes()
{
	for(int i=2;i<=N;i++)
	{
		if(!b[i])prime[++cnt]=i,sum[i]=sum[i-1]+1;	
		else sum[i]=sum[i-1];
	    for(int j=1;j<=cnt&&i*prime[j]<=N;j++)
		{
			b[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	return;
}
void hws()
{
    for(int i=1;i<=N;i++)
	{
	    int x=i,x1=0;
		while(x)
		{
			x1=x1*10+x%10;
			x/=10;
		}
	    tot[i]=tot[i-1];
	    if(x1==i)tot[i]++;
	}
}
int main()
{
	primes();
	hws();
	cin>>p>>q;
	for(int i=N;i>=1;i--)
	{
		if(p*tot[i]>=q*sum[i])
		{
			cout<<i;
			return 0;
		}
	}
	cout<<"Palindromic tree is better than splay tree";
	return 0;
}
```

[about me](https://www.github.com/yyf525)
