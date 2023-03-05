给定 $N,K\in N^*$，求有多少个 $X$ 使得 $X\le N~ \&~X=a^b;a,b\in N^*;b\ge K;$。

观察易发现，在 $a\ge2$ 时，$b$ 不会很大（起码没 $100$），那么就把所有的方幂数给踢掉。

依次踢掉 $2,3,\cdots,\log_2^n$ 次方数。

为了防止在踢掉 $2$ 次方数时顺便踢掉 $4$ 次方数，我们重新定义 $x$ 次方数：

1. 方幂数：若 $X$ 是方幂数，那么 $X=a^b;a,b\in N^*;b>1$
2. $x$ 次方数：若 $X$ 是 $x$ 次方数，那么 $X=a^x;a,x\in N^*;$ 且 $\sqrt[x]{X}$ 不是方幂数

那么我们现在要快速求得 $x$ 次方数的个数。

首先我们可以预处理出小于 $x,x\le 10^7$ 的非方幂数个数。可以把每个数的方幂数硬搞出来，然后前缀和。

那么对于 $K\ge3$ 的情况就秒掉了，因为 $\sqrt[3]{10^{18}}\le10^6$，我们只需枚举 $b$，把 $\le N$ 的 $b$ 次方数个数求出来。

显然是 $\left \lfloor \sqrt[b]{N} \right \rfloor$ 以下的非方幂数个数。 

那么我们现在要较快速求出在 $\sqrt{N}_{\max}=10^9$ 以下非方幂数个数。

求 $\sqrt{N}_{\max}$ 以下方幂数可以模仿 $K\ge3$ 的做法，减一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10, M = 1e7 + 10;

int s[M], w[M];
//1很特殊，开方后还是方幂数，另类考虑

bool pw(__int128 a, __int128 b, __int128 c)
{
	if(a==1) return 1;
	__int128 tp = 1;
	while(b--)
	{
		tp *= a;
		if(tp>c) return 0;
	}
	return 1;
}

int kaifang(int a, int b)//给b开方 
{
	int l = 1, r = 1e9, mid, ans=1;
	while(l <= r)
	{
		mid = l + r >> 1; 
		if(pw(mid,a,b))//mid^a<=b
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return ans;
}

signed main()
{
	int n, k, i, cnt, j, tmp, ans=0;
	cin>>n>>k;
	if(k==1)
	{
		cout<<n;
		return 0;
	}
	for(i=1;i<=M-10;i++) s[i] = 1;
	s[1] = 0;
	for(i=2;i<=M-10;i++)
	{
		j = i * i;
		while(j<=M-10)
		{
			s[j] = 0;
			j *= i;
		}
	}
	for(i=1;i<=M-10;i++) s[i] += s[i-1];
	for(i=max(k,3ll);pw(2,i,n);i++)
	{
		ans += s[kaifang(i,n)];
	}
	if(k==2)
	{
		n = kaifang(2,n);
		tmp = n;
		for(i=2;pw(2,i,n);i++) tmp -= s[kaifang(i,n)];
		ans += tmp - 1;
	}
	cout<<ans+1;//勿忘1
	return 0;
}
```



注：此篇文章由 $\texttt{yinweizhen}$ 编写。