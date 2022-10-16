[题目传送门](https://www.luogu.com.cn/problem/CF1305E)

## 题目大意

给你两个正整数 $n$ 和 $m$，让你构造一个长度为 $n$ 的序列 $a$，并满足以下条件：

$\texttt{1.}$ 所有 $a_i$ 都在 $1\sim 10^9$ 之间。

$\texttt{2.}$ 这个序列必须严格单调递增。

$\texttt{3.}$ 满足 $a_i+a_j=a_k(i<j<k)$ 的个数必须为 $m$。

## 题目思路

我们先考虑构造一个满足 $\texttt{3}$ 条件数量最多的序列，那么肯定就是  $1,2,3\cdots$，那么对于第 $x$ 个数作为 $a_k$，则它对答案的贡献就是 $\lfloor \frac{x-1}{2} \rfloor$，这应该是显然的。

如果这个序列 $1\sim n$ 的总贡献还是不到 $m$，那么就可以输出无解 ，毕竟这是满足个数最多的序列。

接下来我们就考虑当第一次第 $x$ 位填了 $x$，总个数超过或者等于了 $m$。设之前的方案数为 $sum$ （不包括第 $x$ 位），则我们要让第 $x$ 位的贡献为 $m-sum$，而如果这一位填 $x$ 的贡献为 $\lfloor \frac{x-1}{2} \rfloor$，接下来我们考虑让这一位的贡献减少。

这时，我们先考虑一个子问题：把一个数加 $\color{red}{2}$，它的贡献会减少多少？

我们知道，第 $x$ 为填 $x$，那么会有一种方案是 $x=1+(x-1)$，而 $x$ 加了 $2$，那么以 $1$ 作为第一位肯定不行，因为没有 $x+1$；同理，以 $2$ 作为第一位也不行，因为没有 $x$，它已经变成了 $x+2$。

而对于以 $t$ （ $2\leq t< \lceil \frac{x}{2} \rceil$ ）作为第一位，它的方案都可以对应到 $x+2$ 的一种方案。

而对于以 $\lceil \frac{x}{2} \rceil$ 做为第一位，它在 $x$ 的方案中是不行的，而在 $x+2$ 中的方案中是可以出现的。

所以贡献会减少 $(0+2-1=1)$ 个。

故我们得出结论：把一个数加 $2$，它的贡献会见少 $1$。

这样，我们的子问题就解决了。

这时我们回到原问题：要让第 $x$ 位的贡献为 $m-sum$，而原贡献为 $\lfloor \frac{x-1}{2} \rfloor$，怎么修改？

根据我们刚刚得出的结论，我们只需要让 $x$ 加上 $[\lfloor \frac{x-1}{2} \rfloor-(m-sum)]\times 2$ 即可。

现在，我们只需要让第 $x+1\sim n$ 位的贡献为 $0$ 就好了。我们只需让 $a[n]$ 为最大的 $10^9$，然后每次往下是都减去 $x+1$ 即可。

## CODE

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
const int N=10001;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int n,m,ls=1e9,sum;
int a[N];
bool ok;
signed main(){
	ios_base::sync_with_stdio(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=i;
		if(sum+(i-1)/2>=m){
			a[i]+=(sum-(m-(i-1)/2))*2;
			ok=1;
			for(int j=n;j>i;j--){
				a[j]=ls-(i+1),ls-=i+1;
			}
			break;
		}
		sum+=(i-1)/2;
	}
	if(ok){
		for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	}
	else{
		cout<<-1;
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

[about me](https://www.github.com/yyf525)
