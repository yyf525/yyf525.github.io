# 题目
### 题目描述

帝企不擅长玩石头剪刀布，因为他只能出布。因此，他们想了一个办法，就是在卡片上画上石头剪刀和布来代替。

但是，每只帝企只有一张卡片。

他们排成一行，进行$k$轮冒泡赛。

每轮冒泡赛类似于一轮冒泡排序，帝企按照位置递增顺序$(1, 2, ..., n-1)$进行比赛，如果第$i$只赢了第$i+1$只，那么他们俩会交换顺序。注意，如果发生了交换，新的第$i+1$只帝企会继续参加下一次比赛。

帝企想知道，经过$k$轮冒泡赛后，站在第$i$个位置的帝企手中的卡片是什么。

### 输入格式

第一行两个整数$n, k$。

第二行一个长度为$n$的仅由'R'、'S'、'P'组成字符串。

其中，'R'代表石头，'S'代表剪刀，'P'代表布。

### 输出格式

一行一个长度为$n$的字符串，表示$k$轮冒泡赛后每个位置的帝企手中的卡片。

### 样例输入 #1

```
5 1
RSPSP
```

### 样例输出 #1

```
SRPPS
```

### 样例输入 #2

```
10 3
RSRRRRRRSR
```

### 样例输出 #2

```
SRRRRSRRRR
```

### 【数据规模与约定】

对于$10\%$的数据，$1 \leq n, k \leq 5000$。

对于$20\%$的数据，$1 \leq n \leq 5000$。

对于另外$20\%$的数据，字符串中不含有'P'字符。

对于$100\%$的数据，$1 \leq n \leq 500000, 1 \leq k \leq 10^{9}$。

<div STYLE="page-break-after: always;"></div>

# 思路

我们先考虑子任务 $3$，也就是只有 $R$ 和 $S$。

我们可以知道，因为只有两种颜色，那么在每一次操作后，对于每一个 $S$，只要它前面不是 $S$，那么它都会往前移一个，那么我们就可以得到我们的算法：我们从前往后考虑每一个 $S$，都把它移动到它能移动的最小位置，我们记位置为 $p_i$，那么就是移动到 $p_i=\max(\max(1,i-k),p_{i-1})$，于是这个子任务就完成了。

接下来我们考虑 $3$ 中颜色的情况。

我们将整个字符串分成多个段，其中每个段都是级长的且只有两种颜色。

那么我们有一个结论：每次操作后，任意两个块之间都不会发生数的溢出，证明的话自己手推一遍即可。

那么我们可以对于每一个块，都做一遍子任务 $3$，那么这道题就做完了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read();
int n,k;
int a[N];//0 石头，1 剪刀，2 布 
bool win(int x,int y){
	if(x==0&&y==1||x==1&&y==2||x==2&&y==0)return 1;
	return 0;
}
int tonum(char c){
	if(c=='S')return 1;
	if(c=='P')return 2;
	return 0;
}
char tochar(int c){
	if(c==1)return 'S';
	if(c==2)return 'P';
	return 'R'; 
}
void work(){
	for(int j=1;j<n;j++){
		if(win(a[j],a[j+1])){
			swap(a[j],a[j+1]);
		}
	}
	return;	
}
void Done(int k){
	for(int i=1;i<=k;i++)
		work();
	for(int i=1;i<=n;i++){
		cout<<tochar(a[i]);
	}
	return;
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		char c=getchar();
		while(c!='R'&&c!='S'&&c!='P')c=getchar();
		a[i]=tonum(c);
	}
	if(n<=5000&&k<=5000)
		Done(k);
	else{
		int M=10000000;
		Done(min(M/n,k));
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

[about me](https://www.github.com/yyf525)