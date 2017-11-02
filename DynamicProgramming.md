# Dynamic Programming
## 优化
### 四边形不等式
如果对于任意的$ a \leqslant b \leqslant c \leqslant d $，有$ m[a, c] + m[b, d] \leqslant m[a, d] + m[b, c] $，那么$ m[i, j] $满足四边形不等式。
对于转移方程如如下形式的动态规划问题：$ m[i, j] = opt\{[i, k - 1] + m[k, j] + w[i, j]\} $
其中w是m的附属量
首先证明w满足四边形不等式，然后再证明m满足四边形不等式。最后证明$ s[i, j - 1] \leqslant s[i, j] \leqslant s[i + 1, j] $（其中$ s[i, j] $是$ m[i, j] $的最优决策点）


