# 一、介绍

`Trie` 字典树是一种数据结构，它可以维护关于字符串和01串的相关操作。

它的主体思路就是：对于每一个字符串，都将它分成若干个字符，其中第 $i$ 个字符位于第 $i$ 层，再对于每一个节点给它一个数值（方便统计），然后在一个单词结束的地方标记一下。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/64jmc42g.png)

这样，我们就建出了一颗包含单词（ $ab,abg,abf,acfel,abfetp,ac,acho$）的 `Trie` 字典树。

接下来是关于建树的代码：

```cpp
int p=0;
for(int i=0;i<len;i++){
	if(!Trie[p][tonum(s[i])])Trie[p][tonum(s[i])]=++now;
	p=Trie[p][tonum(s[i])];
}
ok[p]=1;
```

接下来我们考虑如何查询是否有这个字符串：

我们从一个根节点出发，然后一直遍历下去。如果字符串的对应字符没有出现，那么就直接返回不行。遍历完后，如果所到的节点不是尾节点，那么也返回不行，代码如下：

```cpp
int p=0;
for(int i=0;i<len;i++){
	if(!Trie[p][tonum(s[i])])
		return 0;
	p=Trie[p][tonum(s[i])];
}
return ok[p];
```

# 二、例题

## [P2580](https://www.luogu.com.cn/problem/P2580) 于是他错误的点名开始了

#### 分析

这道题，其实就是模板题，这不过需要多判断一下正确的时候是否被点过。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5,M=30,L=67;
inline int read();
int Trie[N][M];
int now;
int cnt[N];
char s[L];
int len;
int n,m;
int tonum(char x){
	return x-'a';
}
void insert(){
	int p=0;
	for(int i=0;i<len;i++){
		if(!Trie[p][tonum(s[i])])Trie[p][tonum(s[i])]=++now;
		p=Trie[p][tonum(s[i])];
	}
	cnt[p]++;
	return;
}
void search(){
	int p=0;
	for(int i=0;i<len;i++){
		if(!Trie[p][tonum(s[i])]){
			printf("WRONG\n");
			return;
		}
		p=Trie[p][tonum(s[i])];
	}
	if(cnt[p]==0){
		printf("WRONG\n");
		return;
	}
	if(cnt[p]==1)
		printf("OK\n");
	else
		printf("REPEAT\n");
	cnt[p]++;
	return;
}
void redin(){
	len=0;
	char c=getchar();
	while(c<'a'||c>'z')c=getchar();
	while(c>='a'&&c<='z'){
		s[len++]=c;
		c=getchar();
	}
	return;
}
signed main(){
	n=read();
	for(int i=0;i<n;i++){
		redin();
		insert(); 
	}
	m=read();
	for(int i=0;i<m;i++){
		redin();
		search();
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

[about me](www.github.com/yyf525)