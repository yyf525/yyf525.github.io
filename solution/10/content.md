## A：标题统计

[题目链接](https://www.luogu.com.cn/problem/P5015)

### 题意

给你一个可能含空格和换行符的字符串。让你求出其中不包含空格和换行的字符数量。

### 思路

大水题，直接根据题意一次判断每个字符，然后统计答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
string s;
signed main(){
	getline(cin,s);
	for(int i=0;i<s.size();i++){
		if(s[i]!=' '&&s[i]!='\n')
			ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

## B：龙虎斗

[题目链接](https://www.luogu.com.cn/problem/P5016)

### 题意

有 $n$ 个兵营，开始时第 $i$ 个兵营里面有 $a_i$ 个兵。然后第 $p_1$ 号兵营里面多出了 $s_1$ 个兵。现在定义龙的气势和为所有在 $m$ 号兵营左侧的兵营的兵数与与 $m$ 号军营之间的距离的乘积的和。即 $\sum\limits_{i=1}^{m-1} a_i\cdot (m-i)$。虎的气势和同理，只不过在 $m$ 号兵营的右侧。现在你手里有 $s_2$ 个兵。你可以将他们派入任何一个兵营，求派入哪个兵营能取得最少的龙虎气势差。

### 思路

先把龙和虎的气势和算出来，然后枚举派到每一个兵营，计算龙虎气势只差，统计答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read();
int n;
int a[N];
int m,p1,s1,p;
int sum1,sum2;
int wz,ans;
int get(int x){//计算龙虎气势差
	int s1=sum1,s2=sum2;
	if(x<m)s1+=p*(m-x);
	else s2+=p*(x-m);
	return abs(s1-s2);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	m=read(),p1=read(),s1=read(),p=read();
	a[p1]+=s1;
	for(int i=1;i<m;i++)
		sum1+=a[i]*(m-i);
	for(int i=m+1;i<=n;i++)
		sum2+=a[i]*(i-m);
	wz=1,ans=get(1);
	for(int i=2;i<=n;i++){
		if(get(i)<ans)
			ans=get(i),wz=i;
	}
	printf("%d\n",wz);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

[题目链接](https://www.luogu.com.cn/problem/P5017)

## C：摆渡车（by YYF）

### 题意

有 $n$ 个人，第 $i$ 个人会在第 $a_i$ 分钟取等车。已知大巴**来回**一趟所需 $m$ 分钟。求最少的这 $n$ 个人的**等待时间总长**。

### 思路

看到题目，应该一眼的 `DP` 裸题。

我们定义两个数组：`cnt` 和 `sum`

其中 $cnt_i$ 表示第 $0$ 分钟到第 $i$ 分钟到车站的同学数。

$sum_i$ 表示第 $0$ 分钟到第 $i$ 分钟到车站等车的同学的**到达时间之和**。

那么我们考虑怎么计算：一辆大巴从第 $r$ 分钟开出，等车时间在 $l\sim r$ （含 $l$）的同学所对应的**等待时间总长**。

我们不妨设这些同学的等车时间分别为：$b_1,b_2,\ldots,b_t$，则总长应该是：$\sum\limits_{i=1}^t r-b_i$。化简一下，原式可变为：$\sum\limits_{i=1}^t r-\sum_{i=1}^t b_i=t\cdot r-\sum\limits_{i=1}^t b_i$

首先，显然同学的数量 $t$ 是等于 $cnt_r-cnt_{l-1}$ 的。而 $\sum b_i$ 是等于 $sum_r-sum_{l-1}$ 的。

所以原式可化简为：$r\cdot (cnt_r-cnt_{l-1})-(sum_r-sum_{l-1})$。

我们记它为 `calc(l,r)`。

我们现在定义 $f_i$ 表示第 $i$ 分钟发车，前面时刻所有同学都上车所需花费的**最小等车时间之和**。

如果之前都没法过车，那么 $f_i=i\cdot cnt_i-sum_i$。

如果之前发过车，那么我们枚举 $j$ 从 $1\sim i-m$，表示它上一辆大巴是从 $j$ 时刻发车的。

那么可以得出转移式：$f_i=\min\limits_{j=1}^{i-m} (f_j+calc(j+1,i))$

**注意**：这里从 $j+1$ 开始枚举，因为第 $j$ 分钟上车的人已经被第 $j$ 分钟发车的大巴带走了。

**还有一点**：我们这里的 $i$ 要枚举到 $maxt+m-1$ （ $maxt$ 表示读入时间的最大值），因为倒数第二辆大巴可能在 $[maxt-m,maxt-1]$ 之间发车

这样的时间复杂度是 $\theta(T^2)$ 的，期望得分： $50~\text{pts}$。

接下来我们考虑如何优化。

我们在对于 $f_i$ 的转移中，我们枚举的 $j$ 的复杂度是 $\theta(n)$，但是真正能起到有效转移的，应该只有 $i-2\cdot m+1\sim i-m$ 之间的 $j$。因为你考虑到，在 $i-2\cdot m$ 发出的车，一定没有 $i-m$ 优。

这样，我们的转移式即变为：

$f_i=\min\limits_{j=i-2\cdot m+1}^{i-m} (f_j+calc(j+1,i))$ 。

这样的时间复杂度变为了 $\theta(m\cdot T)$，期望得分：$70~\text{pts}$。

注意到 $n$ 和 $m$ 只有 $500$ 的大小，说明会有很多段长度为 $m$，但中间却没有人等车。

判定条件就是 $i\geqslant m$ 且 $cnt_i=cnt_{i-m}$。

那么我们可以直接将 $f_i$ 赋值成 $f_i-m$。

### 代码

#### 50分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=601,M=5e6;
inline int read();
int n,m;
int t[N];
int cnt[M];//1~i中等车的人数 
int sum[M];
int f[M];
int maxT,ans=1e9+7;
int calc(int l,int r){
	return (cnt[r]-cnt[l-1])*r-(sum[r]-sum[l-1]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		t[i]=read();
		maxT=max(maxT,t[i]);
		cnt[t[i]]++;
		sum[t[i]]+=t[i];
	}
	for(int i=1;i<=maxT+m-1;i++){
		cnt[i]+=cnt[i-1];
		sum[i]+=sum[i-1];
	}
	for(int i=1;i<=maxT+m-1;i++){
		f[i]=i*cnt[i]-sum[i];
		for(int j=0;j<=i-m;j++){
			f[i]=min(f[i],f[j]+calc(j+1,i));
		}
	}
	for(int i=maxT;i<=maxT+m-1;i++)
		ans=min(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

#### 70分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=601,M=5e6;
inline int read();
int n,m;
int t[N];
int cnt[M];//1~i中等车的人数 
int sum[M];
int f[M];
int maxT,ans=1e9+7;
int calc(int l,int r){
	return (cnt[r]-cnt[l-1])*r-(sum[r]-sum[l-1]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		t[i]=read();
		maxT=max(maxT,t[i]);
		cnt[t[i]]++;
		sum[t[i]]+=t[i];
	}
	for(int i=1;i<=maxT+m-1;i++){
		cnt[i]+=cnt[i-1];
		sum[i]+=sum[i-1];
	}
	for(int i=1;i<=maxT+m-1;i++){
		f[i]=i*cnt[i]-sum[i];
		for(int j=max(i-2*m+1,0);j<=i-m;j++){
			f[i]=min(f[i],f[j]+calc(j+1,i));
		}
	}
	for(int i=maxT;i<=maxT+m-1;i++)
		ans=min(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

#### 100分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=601,M=5e6;
inline int read();
int n,m;
int t[N];
int cnt[M];//1~i中等车的人数 
int sum[M];
int f[M];
int maxT,ans=1e9+7;
int calc(int l,int r){
	return (cnt[r]-cnt[l-1])*r-(sum[r]-sum[l-1]);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		t[i]=read();
		maxT=max(maxT,t[i]);
		cnt[t[i]]++;
		sum[t[i]]+=t[i];
	}
	for(int i=1;i<=maxT+m-1;i++){
		cnt[i]+=cnt[i-1];
		sum[i]+=sum[i-1];
	}
	for(int i=1;i<=maxT+m-1;i++){
		f[i]=i*cnt[i]-sum[i];
		if(i>=m&&cnt[i]==cnt[i-m]){
			f[i]=f[i-m];
			continue;
		} 
		for(int j=max(i-2*m+1,0);j<=i-m;j++){
			f[i]=min(f[i],f[j]+calc(j+1,i));
		}
	}
	for(int i=maxT;i<=maxT+m-1;i++)
		ans=min(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

## C：摆渡车（ by YWZ）

记 $cnt_i$ 为第 $i$ 分钟前（含）等车的人数。

记 $sum_i$ 为第 $i$ 分钟前（含）等车的人等待时刻之和。

那么如果在第 $i$ 分钟发一辆车，第 $j$ ~ $i$ 分钟等车的人坐那一辆，共需多少分钟？

设他们来的时间分别为 $a_{1,\cdots,n}$，则总等待时间为$\sum(i-a_x)=\sum i-\sum a_x=i(cnt_i-cnt_{j-1})-(sum_i-sum_{j-1})$。

用前缀和求出 $cnt$ 和 $sum$，就能快速求出那么如果在第 $i$ 分钟发一辆车，第 $j$ ~ $i$ 分钟等车的人坐那一辆共需的时间，极大地优化了本题。



设 $f_i$ 表示让前 $i$ 分钟（含）等车的人坐上车最少所需的等待时间。

易知 $\large f_i=\min\limits_{0\le j\le i-m}(f_j+i(cnt_i-cnt_j)-(sum_i-sum_j))$，

且有 $\large \texttt{answer}=\min\limits_{t\le i<t+m}f_i$。

记 $t$ 为最后一个等车同学来到的时刻，则对于每个 $f_i$，复杂度是 $O(i)$，故总复杂度为 $O(t^2)$。

那么怎么优化呢？

1. 排除冗余转移

   如果第 $i$ 时刻前那辆车在第 $j$ 时刻发车且 $j\le i-2m$，那么可以在 $j+m$ 时发一辆车，且总时间不会变多。

   所以转移中的 $\large\min\limits_{0\le j\le i-m}$ 可以变为  $\large\min\limits_{\max(0,j-2m)<j\le i-m}$ 。

2. 排除冗余状态

   进行了 1.排除冗余转移 后计算每个 $f_i$ 的时间为 $O(m)$，总复杂度为 $O(tm)=\text{4e6}\times\text{5e2}=2e9$，会超时。

   但是 $n \le 100$，这又应该如何去利用呢？

   显然，当 $t$ 足够大时，两个同学等车时间的间隔也逐渐增大。

   那么，对于状态 $f_i$，在时间段 $i-2m+1$ 到 $i$ 时没有同学，即 $cnt_i=cnt_{i-2m}$ ，那么这辆车是不必发的。

   令 $\texttt{pre}$ 表示时刻 $i$ 之前第一个等车的同学来到的时间。

   那么，上一趟车发车时间必然为 $\texttt{pre},\texttt{pre+1}，\cdots,\texttt{pre+m-1}$。

   容易发现，$f_{i-1}$ 涵盖了里面每一种状态，故 $f_i=f_{i-1}$

总时间复杂度：一个同学顾及到前后 $2m$ 个时刻，且每个时刻要一一枚举，故为 $O(t+nm)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[4000010], cnt[4000010], sum[4000010];
int main()
{
  int n, m, i, j, t, mt=0, pre;
  cin>>n>>m;
  for(i=1;i<=n;i++)
  {
    cin>>t;
    t++;
    cnt[t]++;
    sum[t] += t;
    if(t>mt) mt = t;
  }
  for(i=1;i<mt+m;i++)
  {
    cnt[i] += cnt[i-1];
    sum[i] += sum[i-1];
  }
  for(i=1;i<mt+m;i++)
  {
    if(i>=2*m&&cnt[i]==cnt[i-2*m])
    {
			f[i] = f[i-1];
      continue;
    }
    f[i] = cnt[i] * i - sum[i];
    for(j=max(i-m*2,0);j+m<=i;j++)
      f[i] = min(f[i],f[j]+(cnt[i]-cnt[j])*i-(sum[i]-sum[j]));
  }
  int ans = 1e9;
  for(i=mt;i<mt+m;i++)
    ans = min(ans,f[i]);
  cout<<ans;
  return 0;
}
```

## D：对称二叉树

[题目链接](https://www.luogu.com.cn/problem/P5018)

### 题意

你有一颗 $n$ 个节点的二叉树，每个节点有一个权值 $val$，若称一个节点是好的，当且仅当这以这个节点为根的二叉树对于**每个节点**都将**左右子树调换**后所形成的新树与原树同一位置的点点权**全部相同**。求出最大的好的节点的子节点个数。

### 思路

这里介绍两种思路。

#### 第一种：暴力判断

你对于每一个节点，都以它为根。暴力判断一下是否可行，然后统计答案。时间复杂度 $\theta(可过)$.

#### 第二种：树哈希

你求出这棵树的两种遍历方式（根左右和根右左），放在一个哈希里面。然后对于每一个节点，若它的两种遍历形式所对应的哈希值都相同，则说明以它为根的子树满足题目所述条件，更新答案即可。时间复杂度 $\theta(n)$。

### 代码

#### 第一种：暴力判断

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,hs1=1e9+1,hs2=1e9+7,hs3=1e9+9;
inline int read();
int n,rt,ans;
int l[N],r[N],val[N],sum[N];
bool b[N];
void getroot(){
	for(int i=1;i<=n;i++)
		b[l[i]]=1,b[r[i]]=1;
	for(int i=1;i<=n;i++)
		if(!b[i]){
			rt=i;
			return;
		}
}
void getsum(int x){//求子数大小
	sum[x]=1;
	if(l[x])getsum(l[x]),sum[x]+=sum[l[x]];
	if(r[x])getsum(r[x]),sum[x]+=sum[r[x]];
	return;
}
bool check(int rt1,int rt2){
	if(val[rt1]!=val[rt2]||sum[rt1]!=sum[rt2])return 0;
	if(l[rt1]&&!r[rt2]||r[rt1]&&!l[rt2])return 0;
	if(!l[rt1]&&!l[rt2])return 1;
	return check(l[rt1],r[rt2])&&check(r[rt1],l[rt2]);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		val[i]=read();
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		l[i]+=(l[i]==-1),r[i]+=(r[i]==-1);
	}
	getroot();
	getsum(rt);
	for(int i=1;i<=n;i++){
		if(check(l[i],r[i])){
			ans=max(ans,sum[i]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```



#### 第二种：树哈希

我的代码用了保险一点的三哈希。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,hs1=1e9+1,hs2=1e9+7,hs3=1e9+9;
inline int read();
int n,rt,ans;
int l[N],r[N],val[N],sum[N];
bool b[N];
void getroot(){
	for(int i=1;i<=n;i++)
		b[l[i]]=1,b[r[i]]=1;
	for(int i=1;i<=n;i++)
		if(!b[i]){
			rt=i;
			return;
		}
}
struct sa{
	int hs1,hs2,hs3;
}ans1[N],ans2[N];
int getlen(int x){
	int c=0;
	while(x)
		x/=10,c++;
	return c+10;
}
int qow(int a,int b,int c){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%c;
		b>>=1,a=a*a%c;
	}
	return ans;
}
int calc(int x,int y,int op){
	if(op==1)op=hs1;
	if(op==2)op=hs2;
	if(op==3)op=hs3;
	return (x*qow(10,getlen(y),op)%op+y%op)%op;
}
void glr(int x){//根左右
	if(!l[x]&&!r[x]){
		ans1[x].hs1=ans1[x].hs2=ans1[x].hs3=val[x];
		return; 
	}
	if(l[x])glr(l[x]);
	if(r[x])glr(r[x]);
	ans1[x].hs1=calc(calc(val[x],ans1[l[x]].hs1,1ll),ans1[r[x]].hs1,1ll);
	ans1[x].hs2=calc(calc(val[x],ans1[l[x]].hs2,2ll),ans1[r[x]].hs2,2ll);
	ans1[x].hs3=calc(calc(val[x],ans1[l[x]].hs3,3ll),ans1[r[x]].hs3,3ll);
	return;
}
void grl(int x){//根右左
	if(!l[x]&&!r[x]){
		ans2[x].hs1=ans2[x].hs2=ans2[x].hs3=val[x];
		return; 
	}
	if(r[x])grl(r[x]);
	if(l[x])grl(l[x]);
	ans2[x].hs1=calc(calc(val[x],ans2[r[x]].hs1,1ll),ans2[l[x]].hs1,1ll);
	ans2[x].hs2=calc(calc(val[x],ans2[r[x]].hs2,2ll),ans2[l[x]].hs2,2ll);
	ans2[x].hs3=calc(calc(val[x],ans2[r[x]].hs3,3ll),ans2[l[x]].hs3,3ll);
	return;
}
void getsum(int x){//求子数大小
	sum[x]=1;
	if(l[x])getsum(l[x]),sum[x]+=sum[l[x]];
	if(r[x])getsum(r[x]),sum[x]+=sum[r[x]];
	return;
}
bool check(int x){//判断是否可行
	return (ans1[x].hs1==ans2[x].hs1&&ans1[x].hs2==ans2[x].hs2&&ans1[x].hs3==ans2[x].hs3);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		val[i]=read();
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		l[i]+=(l[i]==-1),r[i]+=(r[i]==-1);
	}
	getroot();
	glr(rt),grl(rt);
	getsum(rt);
	for(int i=1;i<=n;i++)
		if(check(i))
			ans=max(ans,sum[i]);
	printf("%lld\n",ans);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```