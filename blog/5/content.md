# 零、前置知识

## 1. 积性函数

积性函数的定义：若 $(a,b)=1$，则 $f(a\cdot b) = f(a) \cdot f(b)$。

常见的积性函数有：$\varphi$ 函数，$\mu$
 函数等。

积性函数有以下性质：

若 $f(x),g(x)$ 均为积性函数，则 $h(x)=f(x)\cdot g(x)$ 也为积性函数。
# 一、介绍

## 1.狄利克雷卷积

定义 $f*g(n)$ （读作：$f$ 卷 $g$，$n$ 为大小）为：$\sum\limits_{i | n} f(i)\cdot g\left(\dfrac{n}{i}\right)$。

狄利克雷卷积有着交换律、结合律，请读者自证。

下面是一些常见函数：

$$

\varphi(n)\\

\mu(n)\\

id(n)\\

I(n)\\

\varepsilon(n)

$$

其中 $id(n)=n$，$I(n)=1$，$\varepsilon(n)$ 在 $n=1$ 时为 $1$，否则为 $0$。

现在来计算一下：$\varphi*I(n)$

下面为计算过程：

$$
\begin{aligned}
  & \varphi*I(n)\\
= & \sum\limits_{i|n} \varphi(i)\\
= & n\\
= & id
\end{aligned}
$$

还有一个常见的卷积：$\mu*I(n)=\varepsilon$

下面为证明：

在 $n=1$ 时，显然成立

不妨设：$n=\alpha_1^{p_1}\cdot \alpha_2^{p_2}\cdots \cdot \alpha_k^{p_k}$

$LHS=\sum\limits_{i|n}\mu(i)$

由于 $\mu(i)$ 只有在不包含平方因子的时候才不是 $0$，所以：

$$
\begin{aligned}
  & LHS\\
= & \dbinom{n}{0}-\dbinom{n}{1}+\dbinom{n}{2}-\cdots\\
= & \sum\limits_{i=0}^{k}(-1)^i\cdot 1^{k-i}\cdot \dbinom{n}{i}\\
= & 0
\end{aligned}
$$

与 $\varepsilon$ 的定义正好符合。

证毕。

相信你已熟知狄利克雷卷积，接下来我们进入杜教筛部分。

## 2.杜教筛

杜教筛是在高效的复杂度内求出一个积性函数的前缀和。

不妨设该函数为 $f(n)$，其前缀和为 $S(n)$，我们构造了另一个积性函数 $g(n)$。

接下来我们推一个式子：

$$
\begin{aligned}
  & \sum\limits_{i=1}^n g*f(i)\\
= & \sum\limits_{i=1}^n\sum_{j|i} g(i)\cdot f\left(\dfrac{n}{i}\right)\\
= & \sum_{j=1}^n\sum_{i=1}^{\lfloor\frac{n}{j}\rfloor}g[j]\cdot f(i)\\
= & \sum_{i=1}^n g(i)\cdot S(\lfloor\frac{n}{i}\rfloor)
\end{aligned}
$$

接下来考虑 $g(1)\cdot S(n)$，即得到：

$$
\begin{aligned}
  & g(1)\cdot S(n)\\
= & \sum_{i=1}^n g(i)\cdot S(\lfloor\frac{n}{i}\rfloor)- \sum_{i=2}^n g(i)\cdot S(\lfloor\frac{n}{i}\rfloor)\\
= & \sum_{i=1}^n g*f(i) - \sum_{i=2}^n g(i)\cdot S(\lfloor\frac{n}{i}\rfloor)
\end{aligned}
$$

所以，如果我们构造的 $g$ 满足如下条件：

+ 可以快速得到 $g(n)$
+ 可以快速得到 $g*f$ 的前缀和

然后注意到后面所减去的 $S(\lfloor\frac{n}{i}\rfloor)$ 是可以数论分块的，可以直接递归求得，这样复杂度为 $n^{\frac{3}{4}}$。

考虑到当我们要求的 $S(x)$ 小于阙值时，可以通过线性筛预处理出，大于等于阙值时，通过上述方式递归即可。

当阙值取 $n^\frac{2}{3}$ 时，复杂度最优，为 $n^\frac{2}{3}$。

# 二、习题

## 1.[模板杜教筛](https://www.luogu.com.cn/problem/P4213)

本题即求 $\varphi$ 和 $\mu$ 的前缀和。

下面介绍求 $\varphi$ 的前缀和，$\mu$ 同理，此处不分析。

我们取 $g(n)=I(n)$，上面已证：$\varphi*I=id$

所以，可得：

$$
\begin{aligned}
  & S(n)\\
= & \sum_{i=1}^n g*f(i)-\sum_{i=2}^n g(i)\cdot S(\lfloor\frac{n}{i}\rfloor)\\
= & \sum_{i=1}^n i - \sum_{i=2}^nS(\lfloor\frac{n}{i}\rfloor)\\
= & \frac{n\cdot (n+1)}{2}-\sum_{i=2}^nS(\lfloor\frac{n}{i}\rfloor)
\end{aligned}
$$

`AC code`：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3000300;
int T, n, B;
int a[N], cnt;
bool b[N];
int mu[N], phi[N], summu[N], sumphi[N];
unordered_map<int, int> smu, sphi;
void Get_Prime(int n) {
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!b[i]) {
            a[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && a[j] * i <= n; ++j) {
            b[a[j] * i] = 1;
            phi[a[j] * i] = phi[i] * (a[j] - 1);
            mu[a[j] * i] = -mu[i];
            if (i % a[j] == 0) {
                phi[a[j] * i] = phi[i] * a[j];
                mu[a[j] * i] = 0;
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        summu[i] = summu[i - 1] + mu[i], sumphi[i] = sumphi[i - 1] + phi[i];
    return;
}
int GetSphi(int n) {
    if (n <= B)
        return sumphi[n];
    if (sphi.count(n) > 0)
        return sphi[n];
    int ans = n * (n + 1) / 2;
    for (int l = 2, r; l <= n;) {
        int val = n / l;
        r = n / val;
        ans -= (r - l + 1) * GetSphi(val);
        l = r + 1;
    }
    sphi[n] = ans;
    return ans;
}
int GetSmu(int n) {
    if (n <= B)
        return summu[n];
    if (smu.count(n) > 0)
        return smu[n];
    int ans = 1;
    for (int l = 2, r; l <= n;) {
        int val = n / l;
        r = n / val;
        ans -= (r - l + 1) * GetSmu(val);
        l = r + 1;
    }
    smu[n] = ans;
    return ans;
}
signed main() {
    scanf("%lld", &T);
    Get_Prime(N - 1);
    for (int __ = 1; __ <= T; ++__) {
        scanf("%lld", &n);
        B = pow(n, 2.0 / 3);
        printf("%lld %lld\n", GetSphi(n), GetSmu(n));
    }
    return 0;
}
```

## 2.[四元组计数](https://www.luogu.com.cn/problem/P4213)

### 题意
给定一个 $n$，求出有多少个整数 $a,b,c,d \in [1,n]$，满足：$a\cdot b = c\cdot d$。

数据范围：$1 \le n \le 10^{11}$。

### 思路

注意到原式等价于：$\frac{a}{c}=\frac{b}{d}$，考虑将这一类分数约分后归为一类：$\frac{p}{q} (p,q)=1$。那么方案数：

$$
\begin{aligned}
&\sum_{p=1}^n\sum_{q=1}^n[(p,q)=1]\cdot {\frac{n}{\max(p,q)}^2}\\
=&2\cdot \sum_{p=1}^n\sum_{q=1}^p[(p,q)=1]\cdot \left\lfloor\frac{n}{p}\right\rfloor^2-n^2\\
=&2\cdot \sum_{p=1}^n\left\lfloor\frac{n}{p}\right\rfloor^2\cdot \varphi(p)-n^2
\end{aligned}
$$

我们记 $k=\sum_{p=1}^n\left\lfloor\frac{n}{p}\right\rfloor^2\cdot \varphi(p)$，则答案为 $2\cdot k-n^2$

$$
\begin{aligned}
k\\
=&\sum_{i=1}^n\varphi(i)\cdot \left\lfloor\frac{n}{i}\right\rfloor^2\\
=&\sum_{i=1}^n\varphi(i)\sum_{j=1}^{\left\lfloor\dfrac{n}{i}\right\rfloor}(2j - 1)\\
=&2\cdot\sum_{i\cdot j\le n}\varphi(i)\cdot j -\sum_{i\cdot j\le n} \varphi(i)\\
=&2\cdot\sum_{T=1}^n\sum_{d|T}\varphi(d)\cdot \frac{T}{d} - \sum_{T=1}^n\sum_{d|T}\varphi(d)\\
=&2\cdot\sum_{i=1}^n\varphi*id(i)-\sum_{i=1}^n i
\end{aligned}
$$

现在已经很明朗了。

我们再记 $ans=\sum_{i=1}^n\varphi*id(i)$，在 $k=2\cdot ans - \frac{n*(n+1)}{2}$。

那么 $ans$ 也就是积性函数 $f(n)=\varphi*id(n)$ 的前缀和。

我们考虑给他卷上一个 $I$，注意到狄利克雷卷积具有交换律，所以其等价于 $\varphi*I*id(n)$，即 $id*id(n)=\sum_{d|n} d\cdot \frac{n}{d}=n$，所以它的值就是 $n\cdot p(n)$，$p(n)$ 为 $n$ 的约数个数。考虑如何快速求出 $id*id(n)$，继续推式子。

$$
\begin{aligned}
&\sum_{i=1}^nid*id(i)\\
=&\sum_{i=1}^n\sum_{j=1}^{\lfloor\dfrac{n}{i}\rfloor}i\cdot j\\
=&\sum_{i=1}^n i \frac{\lfloor\dfrac{n}{i}\rfloor\cdot (\lfloor\dfrac{n}{i}\rfloor+1)}{2}
\end{aligned}
$$

这个可以通过整除分块，根号复杂度内求得，剩下的就是直接杜教筛即可。

式子：

$$
sum_n=\sum_{i=1}^nid*id(i)-\sum_{i=2}^nsum_n/i
$$

前半部分和后半部分皆用整除分块，复杂度还是 $\theta(n^\frac{2}{3})$。

`Warning`：此题数据范围有点大，需要 `__int128`。

`AC code`：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int __int128
const int N = 4000010, M = 400010;
int T, B, n;
int a[M], cnt;
int v[N];
int pwr[N];
int tim[N];
int pid[N];
map<int, int> mp;
void Get_Prime(int n) {
    for (int i = 1; i <= n; ++i)
        v[i] = i;
    pid[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (v[i] == i) {
            a[++cnt] = i;
            pwr[i] = 1;
            tim[i] = i;
            pid[i] = 2 * i - 1;
        }
        for (int j = 1; j <= cnt && a[j] * i <= n; ++j) {
            v[a[j] * i] = a[j];
            pwr[a[j] * i] = 1;
            tim[a[j] * i] = a[j];
            pid[a[j] * i] = pid[a[j]] * pid[i];
            if (i % a[j] == 0) {
                tim[a[j] * i] = tim[i] * a[j];
                pwr[a[j] * i] = pwr[i] + 1;
                int val = tim[a[j] * i], pval = val + pwr[a[j] * i] * (v[a[j] * i] - 1) * val / v[a[j] * i];
                pid[a[j] * i] = pid[a[j] * i / val] * pval;
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        pid[i] += pid[i - 1];
    return;
}
int ask(int n) {
    if (n <= B)
        return pid[n];
    if (mp.count(n) > 0)
        return mp[n];
    int ans = 0;
    for (int l = 1, r; l <= n;) {
        int val = n / l;
        r = n / val;
        ans += (r - l + 1) * (l + r) / 2 * val * (val + 1) / 2;
        l = r + 1;
    }
    for (int l = 2, r; l <= n;) {
        int val = n / l;
        r = n / val;
        ans -= (r - l + 1) * ask(val);
        l = r + 1;
    }
    mp[n] = ans;
    return ans;
}
__int128 readin() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0)
        puts("-"), x = -x;
    if (!x) {
        return;
    }
    print(x / 10);
    putchar(x % 10 + '0');
    return;
}
signed main() {
    Get_Prime(N - 1);
    B = N - 1;
    T = readin();
    for (int __ = 1; __ <= T; ++__) {
        n = readin();
        int ans = ask(n);
        ans = ans * 2 - n * (n + 1) / 2;
        ans = ans * 2 - n * n;
        print(ans);
        puts("");
    }
    return 0;
}
```