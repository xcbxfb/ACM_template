// #include <iostream>
// #include <string>
// #include <cstring>
// #include <cmath>
// #include <ctime>
// #include <algorithm>
// #include <utility>
// #include <stack>
// #include <queue>
// #include <vector>
// #include <set>
// #include <math.h>
// #include <map>
// #include <sstream>
// #include <deque>
// #include <unordered_map>
// #include <unordered_set>
// #include <bitset>
// #include <stdio.h>
// #include <tuple>
#include<bits/stdc++.h>
using namespace std;
/*
ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
*/
// #define int long long
#define ld long double
//#define INT __int128
#define eb(x) emplace_back(x)
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const ld eps = 1e-12;
const int N = 10 + 10, M = N + 10, K = 10;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
//-----------------------------------------------#矩阵数据类型------------------------------
struct MATRIX {
	int l=2, r=2;
	LL a[2][2];
	void init(int b1, int b2, int b3, int b4) {
		a[0][0] = b1, a[0][1] = b2;
		a[1][0] = b3, a[1][1] = b4;
	}
	MATRIX operator*(MATRIX oth) {
		MATRIX ret;
		ret.init(0, 0, 0, 0);
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < r; j++) {
				for (int k = 0; k < l; k++) {
					(ret.a[i][j] += a[i][k] * oth.a[k][j] % mod) %= mod;
				}
			}
		}
		return ret;
	}
};


//-----------------------------------------------#离散化------------------------------
struct Discretization{
    vector<int>v;
    void init(int*a,int len){
        v.clear();
        for(int i=1;i<=len;i++){
            v.push_back(a[i]);
        }
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
    }
    int get(int u){
        int ret=lower_bound(v.begin(),v.end(),u)-v.begin();
        return ret+1;
    }
}D;

//-----------------------------------------#快读整数------------------------------------
// 快速读入整数
inline int read() {
    int x = 0;
    char y = '*', z = getchar();
    while (z < '0' || z > '9') // 跳过非数字字符
        y = z, z = getchar(); // 读取字符
    while (z >= '0' && z <= '9') // 读入数字
        x = (x << 3) + (x << 1) + (z ^ 48), z = getchar(); // 更新数字
    return y == '-' ? -x : x; // 返回负数
}

//---------------------------------------------#单调栈----------------------------------


// 定义一个结构体 MSTACK，用来解决问题
struct MSTACK{
	/*
		选择一个子数组，然后将该子数组中的所有元素修改为子数组中的最大值。求操作的最大次数
	*/
    int n;  // 用来存储序列长度
    int a[N];
    void solve(){
        cin >> n;  // 输入序列长度
        for(int i=1; i<=n; i++){
            scanf("%lld", &a[i]);  // 依次输入序列中的元素
        }

        a[0] = INF;  // 边界值设为无限大
        a[n+1] = INF;  // 边界值设为无限大
        int ans = 0;  // 初始化操作次数

        stack<int> st;  // 定义一个栈，便于处理

        // 单调递减栈
        for(int i=0; i<=n; i++){
            while(st.size() && a[st.top()] < a[i]){
                st.pop();  // 弹出栈顶元素，直到栈顶元素大于当前元素
            }
            if(st.size()){
                ans += i - st.top() - 1;  // 更新操作次数
            }
            st.push(i);  // 将当前元素的索引压入栈
        }

        while(st.size()){
            st.pop();  // 清空栈，准备下一次遍历
        }

        // 单调递减栈
        for(int i=n+1; i>0; i--){
            while(st.size() && a[st.top()] < a[i]){
                st.pop();  // 弹出栈顶元素，直到栈顶元素大于当前元素
            }
            if(st.size()){
                if(a[st.top()] != a[i]){
                    ans += st.top() - 1 - i;  // 更新操作次数
                }
            }
            st.push(i);  // 将当前元素的索引压入栈
        }

        cout << ans << endl;  // 输出操作次数
    }
} mstk;

//---------------------------------------------------#树状数组----------------------------------

struct Fenwick_Tree {
    int C[N];  // 树状数组，用于维护前缀和，C[i] 存储从 i 到下一个子树根节点的和
    
    // 更新树状数组，将位置 x 的值增加 d
    void add(int x, int d) {
        // 从 x 开始，逐层向上更新树状数组
        for (; x <= n; x += x & -x) {  // x & -x 计算出 x 的最低位的 1 表示的值
            C[x] += d;  // 将 d 加到 C[x] 上
        }
    }

    // 查询前缀和，求出从 1 到 x 的区间和
    int ask(int x) {
        int ret = 0;  // 保存结果
        // 从 x 开始逐层向上累加
        for (; x; x -= x & -x) {  // x & -x 计算出 x 的最低位的 1 表示的值
            ret += C[x];  // 将 C[x] 加入到结果 ret 中
        }
        return ret;  // 返回前缀和
    }
};


//----------------------------------------------------#线段树模板---------------------------------
/*
线段树是一种分治数据结构
*/
struct SEGMENT {
	char s[N];
	struct TREE {
		int l, r;
		int tg;
		LL L, O, OL, LO, LOL, OLO;
		LL sum;
		void init() {
			L = O = OL = LO = LOL = OLO = sum = 0;
		}
	}tr[N << 2];
#define ls u<<1
#define rs u<<1|1
	void cal(int u) {
		tr[u].tg ^= 1;
		swap(tr[u].L, tr[u].O);
		swap(tr[u].OL, tr[u].LO);
		swap(tr[u].OLO, tr[u].LOL);
		tr[u].sum = tr[u].LOL;
	}
	void cal2(TREE& u, TREE  l, TREE  r) {
		u.L = l.L + r.L;
		u.O = l.O + r.O;
		u.LO = l.LO + r.LO + l.L * r.O;
		u.OL = l.OL + r.OL + l.O * r.L;
		u.LOL = l.LOL + r.LOL + l.LO * r.L + l.L * r.OL;
		u.OLO = l.OLO + r.OLO + l.O * r.LO + l.OL * r.O;
		u.sum = u.LOL;
	}
	void up(int u) {
		cal2(tr[u], tr[ls], tr[rs]);
	}
	void down(int u) {
		if (tr[u].tg) {
			cal(ls);
			cal(rs);
			tr[u].tg = 0;
		}
	}
	void build(int u, int l, int r) {
		tr[u].l = l, tr[u].r = r;
		if (l == r) {
			if (s[l] == 'L')tr[u].L = 1;
			else {
				tr[u].O = 1;
			}
			return;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		up(u);
	}
	void modify(int u, int l, int r) {
		if (l <= tr[u].l && tr[u].r <= r) {
			cal(u);
			return;
		}
		down(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		if (l <= mid)modify(ls, l, r);
		if (r > mid)modify(rs, l, r);
		up(u);
	}
	TREE query(int u, int l, int r) {
		if (l <= tr[u].l && tr[u].r <= r) {
			return tr[u];
		}
		down(u);
		TREE ret;
		ret.init();
		int mid = (tr[u].l + tr[u].r) >> 1;
		if (l <= mid)cal2(ret, ret, query(ls, l, r));
		if (r > mid)cal2(ret, ret, query(rs, l, r));
		return ret;
	}
#undef ls
#undef rs
}seg;

//--------------------------------------#权值线段树动态开点（线段树上二分）-------------------------------

/*
代码功能概述：
1. 构建了一个权值线段树，用于处理一系列查询与更新操作。
2. 通过 modify 函数在树中插入、删除元素，并更新相应的区间和与元素个数。
3. query 函数则用于根据给定的权值和查询需要进行的更新次数（线段树上二分）。
4. solve 函数处理输入和查询，动态更新数组并输出相应结果。

*/

// 权值线段树结构
struct Weighted_SEGMENT {
    int n, Q;  // n 为元素数量，Q 为查询数量
    int A[N];  // 存储初始数组
    // 定义树节点结构
    struct TREE {
        int l, r;  // 区间左右端点
        LL sum;  // 区间内的权值和
        int cnt;  // 区间内的元素个数
        int ls, rs;  // 左右子树的索引
    } tr[M];  // 权值线段树的节点数组
    int idx;  // 用于标记当前节点的编号

    // 更新当前节点的信息
    void up(int u) {
        tr[u].l = tr[tr[u].ls].l;  // 左端点更新为左子树的左端点
        tr[u].r = tr[tr[u].rs].r;  // 右端点更新为右子树的右端点
        tr[u].sum = tr[tr[u].ls].sum + tr[tr[u].rs].sum;  // 区间和更新为左右子树的和
        tr[u].cnt = tr[tr[u].ls].cnt + tr[tr[u].rs].cnt;  // 区间元素个数更新为左右子树的元素个数之和
    }

    // 修改操作：在位置 pos 上增加 x
    void modify(int &u, int l, int r, int pos, int x) {
        if (!u) {
            u = ++idx;  // 如果当前节点不存在，分配新节点
            tr[u].l = l, tr[u].r = r;  // 初始化区间左右端点
        }
        if (l == r) {  // 叶子节点，直接更新 sum 和 cnt
            tr[u].sum += pos * x;
            tr[u].cnt += x;
            return;
        }
        int mid = (l + r) >> 1;  // 计算中点
        if (pos <= mid) {
            modify(tr[u].ls, l, mid, pos, x);  // 递归更新左子树
        } else {
            modify(tr[u].rs, mid + 1, r, pos, x);  // 递归更新右子树
        }
        up(u);  // 更新当前节点的信息
    }

    // 查询：根据权值和 x 查询需要多少次操作
    int query(int &u, int l, int r, int x) {
        if (l == r) {
            return (x <= 0 ? 0 : (x + l - 1) / l);  // 如果 x 为负或 0，返回 0，否则返回商
        }
        int mid = (l + r) >> 1;  // 计算中点
        if (tr[tr[u].rs].sum >= x) {
            return query(tr[u].rs, mid + 1, r, x);  // 递归右子树查询
        } else {
            return query(tr[u].ls, l, mid, x - tr[tr[u].rs].sum) + tr[tr[u].rs].cnt;  // 递归左子树并加上右子树的元素个数
        }
    }
    /*
		计算数组排序后的后缀和是否能大于等于 sum 值
    */
    // 处理主逻辑
    void solve() {
        cin >> n >> Q;  // 读取元素数量 n 和查询数量 Q
        LL sum = 0;  // 记录当前元素和
        int rt = 0;  // 初始化根节点
        // 初始化数组并构建线段树
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &A[i]);
            if (A[i] > 0) modify(rt, 1, inf, A[i], 1);  // 若 A[i] > 0，插入到线段树中
            sum += A[i];  // 累加元素和
        }

        int pos, val;  // 定义位置和更新值
        // 处理查询
        while (Q--) {
            scanf("%lld%lld", &pos, &val);  // 读取更新操作
            if (A[pos] > 0) modify(rt, 1, inf, A[pos], -1);  // 如果当前 A[pos] > 0，删除其贡献
            if (val > 0) modify(rt, 1, inf, val, 1);  // 插入新值
            sum += val - A[pos];  // 更新元素和
            A[pos] = val;  // 更新数组
            // 输出当前更新后的结果
            printf("%lld\n", tr[1].cnt - query(rt, 1, inf, sum) + 1);
        }
    }
} wseg;  // 定义权值线段树对象


//-------------------------------------------#线段树基础版2-------------------------------------------


// 线段树结构体
struct W_seg {
    #define ls u << 1 // 左子节点
    #define rs u << 1 | 1 // 右子节点

    // 定义线段树的节点结构
    struct TREE {
        LL mn; // 节点的最小值
        int pos; // 最小值的位置
        LL tg; // 懒标记
    } tr[N << 2]; // 线段树数组
    
    // 更新当前节点的信息
    void up(int u) {
        tr[u].mn = min(tr[ls].mn, tr[rs].mn); // 更新最小值
        // 记录最小值的位置
        if (tr[u].mn == tr[rs].mn) {
            tr[u].pos = tr[rs].pos;
        } else {
            tr[u].pos = tr[ls].pos;
        }
    }

    // 初始化线段树
    void init(int u,int l,int r) {
        tr[u].mn=tr[u].tg=0;
        if(l==r){
            return ;
        }
        int mid=l+r>>1;
        init(ls,l,mid),init(rs,mid+1,r);
        up(u);
    }

    // 下传懒标记
    void down(int u) {
        if (tr[u].tg) {
            tr[ls].mn += tr[u].tg; // 更新左子节点的最小值
            tr[ls].tg += tr[u].tg; // 更新左子节点的懒标记
            tr[rs].mn += tr[u].tg; // 更新右子节点的最小值
            tr[rs].tg += tr[u].tg; // 更新右子节点的懒标记
            tr[u].tg = 0; // 清空当前节点的懒标记
        }
    }

    // 修改操作：在区间 [L, R] 上增加 x
    void modify(int u, int l, int r, int L, int R, int x) {
        // 如果当前节点的区间在修改范围内
        if (L <= l && r <= R) {
            if (l == r) { // 如果是叶子节点
                tr[u].pos = l; // 记录位置
            }
            tr[u].mn += 1ll * x; // 更新最小值
            tr[u].tg += 1ll * x; // 更新懒标记
            return;
        }
        down(u); // 下传懒标记
        int mid = (l + r) >> 1; // 计算中点
        if (L <= mid) {
            modify(ls, l, mid, L, R, x); // 递归更新左子树
        }
        if (R > mid) {
            modify(rs, mid + 1, r, L, R, x); // 递归更新右子树
        }
        up(u); // 更新当前节点的信息
    }

    // 查询操作：查询区间 [L, R] 的最小值
    int ask(int u, int l, int r, int L, int R) {
        if (L <= l && r <= R) { // 如果当前节点的区间在查询范围内
            return tr[u].mn; // 返回最小值
        }
        down(u); // 下传懒标记
        int mid = (l + r) >> 1; // 计算中点
        int ret = inf; // 初始化最小值
        if (L <= mid) {
            ret = min(ret, ask(ls, l, mid, L, R)); // 递归查询左子树
        }
        if (R > mid) {
            ret = min(ret, ask(rs, mid + 1, r, L, R)); // 递归查询右子树
        }
        return ret; // 返回最小值
    }
    #undef ls
    #undef rs
} ; // 创建线段树实例

//-------------------------------------------#可持久化线段树（主席树）-------------------------------------
struct Persistent_SEG {
    static const int maxn = N * 60; // 最大节点数
    int rt[N]; // 记录每个版本的根节点
    int ch[maxn][2]; // 子节点
    int tg[maxn]; // 节点的标签（权重）
    int idx; // 当前节点索引

    // 构建线段树
    int build(int l, int r) {
        int c = ++idx; // 创建新节点
        tg[c] = 0; // 初始化标签
        if (l == r) return c; // 叶子节点返回
        int mid = (l + r) >> 1; // 中点
        ch[c][0] = build(l, mid); // 构建左子树
        ch[c][1] = build(mid + 1, r); // 构建右子树
        return c; // 返回根节点
    }

    // 修改操作
    int modify(int u1, int u2, int ql, int qr, int l, int r, int tg1, int tg2) {
        if (ql <= l && r <= qr) { // 完全覆盖
            int c = ++idx; // 创建新节点
            ch[c][0] = ch[u1][0]; // 继承左子树
            ch[c][1] = ch[u1][1]; // 继承右子树
            tg[c] = tg[u1] + tg1 + 1; // 更新标签
            return c;
        } else if (r < ql) { // 完全不在范围内，使用u1
            int c = ++idx;
            ch[c][0] = ch[u1][0];
            ch[c][1] = ch[u1][1];
            tg[c] = tg1 + tg[u1]; // 更新标签
            return c;
        } else if (l > qr) { // 完全不在范围内，使用u2
            int c = ++idx;
            ch[c][0] = ch[u2][0];
            ch[c][1] = ch[u2][1];
            tg[c] = tg2 + tg[u2]; // 更新标签
            return c;
        } else { // 部分重叠
            int mid = (l + r) >> 1;
            int c = ++idx; // 创建新节点
            ch[c][0] = modify(ch[u1][0], ch[u2][0], ql, qr, l, mid, tg1 + tg[u1], tg2 + tg[u2]); // 修改左子树
            ch[c][1] = modify(ch[u1][1], ch[u2][1], ql, qr, mid + 1, r, tg1 + tg[u1], tg2 + tg[u2]); // 修改右子树
            return c; // 返回新节点
        }
    }

    // 查询操作
    int ask(int u, int pos, int l, int r) {
        if (l == r) return tg[u]; // 到达叶子节点
        int mid = (l + r) >> 1; // 中点
        if (pos <= mid) return tg[u] + ask(ch[u][0], pos, l, mid); // 查询左子树
        else return tg[u] + ask(ch[u][1], pos, mid + 1, r); // 查询右子树
    }
};

//------------------------------------------------------#splay模板--------------------------------
struct SPLAY {
    //注意定义 inf 和 N
    int A[N];
    int node[N], idx, root;
    struct Node {
        int s[2];
        int pos, v, p, size;
        int sum, mx, ls, rs;
        int rev, sam;
        void init(int _v, int _p) {
            v = _v, p = _p;
            sum = v, mx = v, ls = rs = max((int)0, v);
            size = 1;
            rev = sam = 0;
            s[0] = s[1] = 0;
        }
    }tr[N];
    void init(int n, int N) {
        for (int i = 1; i < N; i++)node[++idx] = i;
        tr[0].mx = A[0] = A[n + 1] = -inf;
    }
    void up(int x) {
        auto& u = tr[x], & lu = tr[tr[x].s[0]], & ru = tr[tr[x].s[1]];
        u.mx = max({ lu.mx, ru.mx, lu.rs + ru.ls + u.v });
        u.ls = max(lu.sum + ru.ls + u.v, lu.ls);
        u.rs = max(ru.sum + lu.rs + u.v, ru.rs);
        u.size = lu.size + ru.size + 1;
        u.sum = u.v + lu.sum + ru.sum;
    }
    void down(int x) {
        auto& ls = tr[tr[x].s[0]], & rs = tr[tr[x].s[1]], & u = tr[x];
        if (u.rev) {
            ls.rev ^= 1;
            rs.rev ^= 1;
            u.rev = 0;
            swap(ls.s[0], ls.s[1]), swap(rs.s[0], rs.s[1]);
            swap(ls.ls, ls.rs), swap(rs.ls, rs.rs);
        }
        if (u.sam) {
            u.sam = u.rev = 0;
            if (u.s[0]) {
                ls.sam = 1;
                ls.v = u.v, ls.sum = u.v * ls.size;
            }
            if (u.s[1]) {
                rs.sam = 1;
                rs.v = u.v, rs.sum = u.v * rs.size;
            }
            if (u.v > 0) {
                if (u.s[0])ls.mx = ls.ls = ls.rs = ls.sum;
                if (u.s[1])rs.mx = rs.ls = rs.rs = rs.sum;
            }
            else {
                if (u.s[0])ls.mx = ls.v, ls.ls = ls.rs = 0;
                if (u.s[1])rs.mx = rs.v, rs.ls = rs.rs = 0;
            }
        }
    }

    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = tr[y].s[1] == x;
        tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
        tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y, tr[y].p = x;
        up(y), up(x);
    }
    void splay(int x, int r) {
        while (tr[x].p != r) {
            int y = tr[x].p, z = tr[y].p;
            if (z != r) {
                if ((tr[z].s[1] == y) ^ (tr[y].s[1] == x))rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        if (!r)root = x;
    }
    int build(int l, int r, int p) {
        int mid = l + r >> 1;
        int u = node[idx--];
        tr[u].init(A[mid], p);
        if (l < mid)tr[u].s[0] = build(l, mid - 1, u);
        if (r > mid)tr[u].s[1] = build(mid + 1, r, u);
        up(u);
        return u;
    }
    int get(int k) {
        int u = root;
        while (u) {
            down(u);
            if (tr[tr[u].s[0]].size + 1 > k)u = tr[u].s[0];
            else if (tr[tr[u].s[0]].size + 1 == k)return u;
            else if (tr[tr[u].s[0]].size + 1 < k)k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
        }
        return -1;
    }
    void dfs(int u) {
        if (tr[u].s[0])dfs(tr[u].s[0]);
        if (tr[u].s[1])dfs(tr[u].s[1]);
        node[++idx] = u;
    }
    void out(int u) {
        down(u);
        if (tr[u].s[0])out(tr[u].s[0]);
        cout << tr[u].v << " ";;
        if (tr[u].s[1])out(tr[u].s[1]);
    }
}bst;

//-------------------------------------------------#树链剖分-------------------------------------
/*
初始化函数
dfs1(1,0,1);
dfs2(1, 1);
build(1, 1, n);
*/
struct Link_Cut_Tree {
	// GRAHP 结构体用于表示图的邻接表表示法
	struct GRAHP {
		int h[N], e[M], ne[M], idx; // h存储头节点, e存储边, ne存储下一条边的索引, idx为边的编号
		// 添加一条边到图中，双向边 (a, b) 和 (b, a)
		void add(int a, int b) {
			e[idx] = b, ne[idx] = h[a], h[a] = idx++;
			e[idx] = a, ne[idx] = h[b], h[b] = idx++;
		}
		// 初始化图，将头节点的值设为-1（表示无边）
		void init() {
			memset(h, -1, sizeof h);
			idx = 0;
		}
	}G; // 定义图的实例 G

	int w[N], nw[N], id[N], fa[N], tot; // w：节点权重，nw：重编号后的权重，id：节点的DFS编号，fa：父节点，tot：计数器
	int dep[N], son[N], top[N], siz[N]; // dep：深度，son：重儿子，top：重链顶端，siz：子树大小

	struct TREE {
		int l, r; // 区间 [l, r]
		int fg, sum; // fg：延迟标记，sum：区间和
	}tr[N << 2]; // 线段树数组 tr，每个节点管理区间 [l, r]

	// DFS1：用于计算每个节点的子树大小、深度以及重儿子
	void dfs1(int u, int p, int d) {
		siz[u] = 1, fa[u] = p, dep[u] = d; // 初始化节点 u 的子树大小为 1，父节点 p，深度 d
		int mx = 0;
		for (int i = G.h[u]; i != -1; i = G.ne[i]) { // 遍历节点 u 的每个邻居
			int j = G.e[i];
			if (j == p) continue; // 如果邻居是父节点，则跳过
			dfs1(j, u, d + 1); // 递归处理子节点
			siz[u] += siz[j]; // 更新子树大小
			if (siz[son[u]] < siz[j]) son[u] = j; // 找到重儿子（子树最大）
		}
	}

	// DFS2：处理重链，给每个节点分配 DFS 序，并计算 top 节点
	void dfs2(int u, int link) {
		id[u] = ++tot, nw[tot] = w[u], top[u] = link; // 给节点 u 分配编号，更新权重和 top 节点
		if (son[u]) dfs2(son[u], link); // 继续处理重儿子，保持链的连接
		for (int i = G.h[u]; i != -1; i = G.ne[i]) { // 遍历其他子节点
			int j = G.e[i];
			if (j == fa[u] || j == son[u]) continue; // 跳过父节点和重儿子
			dfs2(j, j); // 新链处理子节点
		}
	}

	// 以下定义了线段树操作，ls 和 rs 是左右子节点的索引
#define ls u<<1
#define rs u<<1|1

// up：更新当前节点的 sum 为左右子树的和
	void up(int u) {
		tr[u].sum = tr[ls].sum + tr[rs].sum;
	}

	// down：延迟标记下推操作，将标记传播给左右子节点
	void down(int u) {
		if (tr[u].fg) { // 如果当前节点有标记
			tr[ls].fg += tr[u].fg;
			tr[ls].sum += tr[u].fg * (tr[ls].r - tr[ls].l + 1); // 更新左子树
			tr[rs].fg += tr[u].fg;
			tr[rs].sum += tr[u].fg * (tr[rs].r - tr[rs].l + 1); // 更新右子树
			tr[u].fg = 0; // 清除当前节点的标记
		}
	}

	// build：线段树的建立函数，初始化节点区间并赋值
	void build(int u, int l, int r) {
		tr[u].l = l, tr[u].r = r;
		if (l == r) {
			tr[u].sum = nw[l]; // 叶节点赋值
			return;
		}
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r); // 递归建立左右子树
		up(u); // 更新当前节点
	}

	// modify：修改区间 [l, r] 的值，增加 k
	void modify(int u, int l, int r, int k) {
		if (l <= tr[u].l && tr[u].r <= r) {
			tr[u].sum += k * (tr[u].r - tr[u].l + 1); // 更新区间和
			tr[u].fg += k; // 设置延迟标记
			return;
		}
		down(u); // 下推标记
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify(ls, l, r, k);
		if (r > mid) modify(rs, l, r, k);
		up(u); // 更新当前节点
	}

	// query：查询区间 [l, r] 的区间和
	int query(int u, int l, int r) {
		if (l <= tr[u].l && tr[u].r <= r) {
			return tr[u].sum;
		}
		down(u); // 下推标记
		int mid = tr[u].l + tr[u].r >> 1;
		int ret = 0;
		if (l <= mid) ret += query(ls, l, r);
		if (r > mid) ret += query(rs, l, r);
		up(u); // 更新当前节点
		return ret;
	}

	// path：处理两节点 u 和 v 之间的路径修改操作
	void path(int u, int v, int k) {
		while (top[u] != top[v]) { // 当 u 和 v 不在同一条链上时
			if (dep[top[u]] < dep[top[v]]) swap(u, v); // 确保 u 比 v 深
			modify(1, id[top[u]], id[u], k); // 修改 u 到 top[u] 的路径
			u = fa[top[u]]; // 跳到上一链的父节点
		}
		if (dep[u] < dep[v]) swap(u, v); // 确保 u 比 v 深
		modify(1, id[v], id[u], k); // 修改 v 到 u 的路径
	}

	// ask：查询两节点 u 和 v 之间路径的区间和
	int ask(int u, int v) {
		int ret = 0;
		while (top[u] != top[v]) { // 当 u 和 v 不在同一条链上时
			if (dep[top[u]] < dep[top[v]]) swap(u, v); // 确保 u 比 v 深
			ret += query(1, id[top[u]], id[u]); // 查询 u 到 top[u] 的路径
			u = fa[top[u]]; // 跳到上一链的父节点
		}
		if (dep[u] < dep[v]) swap(u, v); // 确保 u 比 v 深
		ret += query(1, id[v], id[u]); // 查询 v 到 u 的路径
		return ret;
	}

#undef ls
#undef rs
}ctr;
//-----------------------------------------------------#LCT-----------------------------------------------
/*
功能：动态加边，动态删边，动态求某个路径上点的信息（只能维护树，不能有环，有环要破环）
函数声明
一般数据结构函数（字面意思）
	PushUp(x)
	PushDown(x)
Splay 树的函数
下面是 Splay 树中用到的函数，具体可以查阅 Splay 树。

	Getch(x) 获取 x 是父亲的哪个儿子。
	Splay(x) 通过和 Rotate 操作联动实现把 x 旋转到 当前 Splay 的根。
	Rotate(x) 将 x 向上旋转一层的操作。

新操作
	Access(x) 把从根到 x 的所有点放在一条实链里，使根到 x 成为一条实路径，并且在同一棵 Splay 里。只有此操作是必须实现的，其他操作视题目而实现。
	IsRoot(x) 判断 x 是否是所在树的根。
	Update(x) 在 Access 操作之后，递归地从上到下 PushDown 更新信息。
	MakeRoot(x) 使 x 点成为其所在树的根。
	Link(x, y) 在 x, y 两点间连一条边。
	Cut(x, y) 把 x, y 两点间边删掉。
	Find(x) 找到 x 所在树的根节点编号。
	Fix(x, v) 修改 x 的点权为 v。
	Split(x, y) 提取出 x, y 间的路径，方便做区间操作。
*/

struct LCT {
	int ch[N][2], p[N], tg[N];  // ch[x][0] 表示节点x的左孩子，ch[x][1] 表示节点x的右孩子
	int v[N], sum[N];  // v[x] 为节点x的值，sum[x] 为以节点x为根的子树的所有节点值的异或和

	// 清除节点x的信息，将其子节点、父节点、标记值都设为0
	void clear(int x) {
		ch[x][0] = ch[x][1] = p[x] = tg[x] = 0;
	}

	// 返回x是父节点的左孩子还是右孩子，1表示右孩子，0表示左孩子
	int getch(int x) {
		return ch[p[x]][1] == x;
	}

	// 判断节点x是否是其Splay树的根节点
	int isroot(int x) {
		return ch[p[x]][0] != x && ch[p[x]][1] != x;
	}

	// 对节点x进行翻转，交换其左右孩子，并更新反转标记
	void rev(int x) {
		swap(ch[x][0], ch[x][1]);
		tg[x] ^= 1;
	}

	// 更新节点x的sum值，sum[x]等于左右孩子的sum值和自身的值的异或
	void up(int x) {
		v[x] = v[ch[x][0]] + 1 + v[ch[x][1]];
	}

	// 下推反转标记，若节点x有反转标记，则将其传递给子节点，并清除x的标记
	void pushdown(int x) {
		if (tg[x]) {
			rev(ch[x][0]);  // 翻转左孩子
			rev(ch[x][1]);  // 翻转右孩子
			tg[x] = 0;  // 清除x的反转标记
		}
	}

	// 递归更新父节点，保证所有祖先节点的懒标记都被下推
	void update(int x) {
		if (!isroot(x)) update(p[x]);  // 如果x不是根节点，则递归更新父节点
		pushdown(x);  // 下推x的反转标记
		//迭代写法
		/*int top = 0, r = x;
		stk[++top] = r;
		while (!isroot(r)) stk[++top] = r = p[r];
		while (top) pushdown(stk[top--]);*/
	}

	// 旋转操作，将节点x旋转到其父节点y的位置
	void rotate(int x) {
		int y = p[x], z = p[y];  // y是x的父节点，z是y的父节点
		int chx = getch(x), chy = getch(y);  // chx表示x是左还是右孩子，chy表示y是左还是右孩子
		p[x] = z;  // x的父节点更新为z
		if (!isroot(y)) ch[z][chy] = x;  // 如果y不是根节点，则z的对应孩子设为x
		ch[y][chx] = ch[x][chx ^ 1];  // y的对应孩子更新为x的另一个孩子
		p[ch[x][chx ^ 1]] = y;  // 更新x的另一个孩子的父节点为y
		ch[x][chx ^ 1] = y;  // x的对应子节点设为y
		p[y] = x;  // y的父节点设为x
		up(y);  // 更新y的sum值
		up(x);  // 更新x的sum值
	}

	// 将节点x伸展到Splay树的根节点
	void splay(int x) {
		update(x);  // 先递归下推x的懒标记
		for (int f = p[x]; f = p[x], !isroot(x); rotate(x))  // 循环，直到x成为根节点
			if (!isroot(f))  // 如果父节点不是根节点，决定是Zig-Zig还是Zig-Zag操作
				rotate(getch(x) == getch(f) ? f : x);
	}

	// 建立一条从根到x的路径，同时将x变成Splay树的根节点
	void access(int x) {
		int z = x;
		for (int f = 0; x; f = x, x = p[x]) {
			splay(x);  // 先将x伸展到根节点
			ch[x][1] = f;  // 将当前的子树f挂到x的右孩子上
			up(x);  // 更新x的sum值
		}
		splay(z);  // 最终将z旋转到Splay树的根
	}

	// 将节点x变成树的根节点
	void makeroot(int x) {
		access(x);  // 先通过access建立路径
		splay(x);  // 然后将x旋转到Splay树的根节点
		swap(ch[x][0], ch[x][1]);  // 交换x的左右孩子，进行路径反转
		tg[x] ^= 1;  // 标记x为反转状态
	}

	// 找到节点x所在树的根节点，并将根节点旋转到Splay树的根
	int findroot(int x) {
		access(x);  // 先通过access将x变为Splay树的根
		splay(x);  // 将x旋转到根
		pushdown(x);
		while (ch[x][0]) pushdown(x = ch[x][0]);  // 不断沿左孩子寻找树的根节点
		splay(x);  // 将根节点旋转到Splay树的根节点
		return x;  // 返回根节点
	}

	// 分离x和y之间的路径，y成为Splay树的根
	void split(int x, int y) {
		makeroot(x);  // 将x变为树的根节点
		access(y);  // 建立从根到y的路径
	}

	// 将x和y连接，建立一条新的边
	void link(int x, int y) {
		makeroot(x);  // 将x变为原树的根节点
		if (findroot(y) != x) p[x] = y;  // 如果x和y没有连通，则将x的父节点设为y
	}

	// 切断x和y之间的连接
	void cut(int x, int y) {
		makeroot(x);  // 将x变为原树的根节点
		if (findroot(y) == x && p[y] == x && !ch[y][0]) {  // 如果y的父节点是x且y没有左孩子
			ch[x][1] = p[y] = 0;  // 切断x与y的连接
			up(x);  // 更新x的sum值
		}
	}
	//--------------------------------------------------------LCT处理边双问题模板--------------------------------------
	/*
	边双，考虑连边的时候，如果发现左右两端点已经连通。

	就把路径上所有点拿出来，缩点。

	因为缩点可能进行多次，所以并查集维护一下。
	*/
	/*
	int fa[N], s[N];
	int find(int a) {
		if (fa[a] == a)return a;
		return fa[a] = find(fa[a]);
	}
	void init(int n) {
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			v[i] = s[i] = 1;
		}
	}

#define lc ch[x][0]    // 定义宏 lc 为当前节点 x 的左孩子
#define rc ch[x][1]
	void access(int x) {
		for (int y = 0; x; y = x, x = p[y] = find(p[x])) {  // y 是前一个子树的根，x 是当前节点
			splay(x);  // 伸展节点 x 到根节点
			rc = y;    // 将前一个子树挂到 x 的右孩子
			up(x); // 更新 x 的信息
		}
	}
	 //删除节点 x 的右子树，将子树中的所有点合并到 y 代表的根节点上
	void Del(int x, int y) {
		if (!x) return;  // 如果 x 为空，直接返回
		fa[x] = y;  // 将 x 的父节点设为 y
		s[y] += s[x];  // 合并节点 x 的子树大小到 y
		Del(lc, y);  // 递归删除左子树
		Del(rc, y);  // 递归删除右子树
	}

	// 连通节点 x 和 y
	void Link(int x, int y) {
		if (x == y) return;  // 如果 x 和 y 是同一个节点，不需要连通
		makeroot(x);  // 先将 x 变成根节点
		if (findroot(y) != x) {  // 如果 x 和 y 不在同一个连通分量中
			p[x] = y;  // 将 x 的父节点设为 y，连通 x 和 y
			return;
		}
		Del(rc, x);  // 否则删除 x 的右子树
		rc = 0;  // 将 x 的右孩子设为空
		up(x);  // 更新 x 的信息
	}
	*/
} st;

//------------------------------------------------------#ST表----------------------------------------------------
struct SparseTable {
	int st[N][32];  // 存储稀疏表，st[i][j] 表示从 i 开始的长度为 2^j 的区间的值

	// 初始化稀疏表的函数
	void init(int n) {
		// 初始化所有 st[i] 行的值为 0
		for (int i = 1; i <= n; i++) {
			memset(st[i], 0, sizeof st[i]);
		}
	}

	// 计算稀疏表的函数
	void work(vector<int>& v) {
		int n = v.size() - 1;  // 获取向量 v 的大小

		// 初始化稀疏表第一列，st[i][0] 记录每个元素本身的值
		for (int i = 1; i <= n; i++) {
			st[i][0] = v[i];
		}

		// 填充稀疏表
		// j 表示区间长度的指数部分，2^j 表示区间长度
		for (int j = 1; (1 << j) <= n; j++) {
			// i 表示区间的起始位置
			for (int i = 1; i + (1 << j) - 1 <= n; i++) {
				// 计算 st[i][j] 的值，通过合并两个长度为 2^(j-1) 的区间
				st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
			}
		}
	}

	// 计算数字 u 的二进制表示中最高位的 1 所在的位置
	int lg(int u) {
		for (int i = 30; i != -1; i--)
			if (u >> i & 1) return i;  // 找到最高位的 1，返回它的位置
		return 0;  // 如果没有找到，返回 0
	}

	// 查询区间 [l, r] 的值
	int query(int l, int r) {
		int k = lg(r - l + 1);  // 计算区间长度的最高位的 1
		// 合并两个部分的结果，返回 [l, r] 区间的值
		return st[l][k] | st[r - (1 << k) + 1][k];
	}
} ST;
//-------------------------------------------#并查集----------------------------------


// 并查集 (Disjoint Set Union) 数据结构，用于维护点之间的连通性
struct DSU {
    std::vector<int> fa, siz; // fa 存储每个节点的父节点，siz 存储每个连通块的大小
    DSU(int n) : fa(n + 1), siz(n + 1, 1) {
        // 初始化，将每个节点的父节点设为自身，连通块大小为 1
        std::iota(fa.begin(), fa.end(), 0);
    }
    // 查找操作，带路径压缩优化
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    // 判断两个点是否在同一个连通块中
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
    // 合并操作，按大小优化，将较小的连通块合并到较大的连通块
    inline bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false; // 如果已经在同一个连通块，则无需合并
        if (siz[fx] < siz[fy]) swap(fx, fy); // 保证 fx 是较大的连通块
        fa[fy] = fx, siz[fx] += siz[fy], siz[fy] = 0; // 合并并更新大小
        return true;
    }
};

//------------------------------------------#三分搜索---------------------------------

struct  Ternary_Search{
    int check(int x,int k){

    }

    int get(int L,int R,int k){
        int l=L,r=R,ret=l;
        while(l<=r){
            int mid=l+(r-l)/2;
            int midmid=r-(r-mid)/2;
            if(check(mid,k)>=check(midmid,k)){
                ret=mid;
                r=midmid-1;
            }
            else{
                l=mid+1;
            }
        }
        return check(ret,k);
    }
};

//--------------------------------------------#字符串Hash-----------------------------

// 哈希结构体，用于计算字符串的哈希值
struct HASH{
    static const ULL P = 1331;  // P为哈希基数，通常选用一个较大的质数，如131
    ULL h[M], p[M];  // h[]用于存储哈希值，p[]用于存储P的幂次
    int len;
    
    // 初始化函数，计算字符串的哈希值和P的幂次表
    void init(char *s) {
        p[0] = 1;  // P^0 = 1
        len=strlen(s+1);
        for (int i = 1; i <= len; i++) {
            p[i] = p[i - 1] * P;  // 计算P的幂次：P^1, P^2, ..., P^n
            h[i] = h[i - 1] * P + s[i];  // 计算哈希值：h[i] = h[i-1] * P + s[i]
        }
    }

    // 获取子串[l, r]的哈希值，使用前缀哈希技巧
    ULL get(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];  // 通过哈希值差计算子串哈希值
    }
};



//---------------------------------------------#双Hash-----------------------------------

struct HH{//使用时记得拆出来用
	// 哈希参数
	static const int MAXN=1e6+10;
	static const int P1 = 993244853, BASE1 = 131;  
	static const int P2 = 1000000009, BASE2 = 13331;  
	int B1[MAXN], B2[MAXN];  // 存储基数的幂

	// 哈希结构体
	struct Hash {
	    long long a1, a2;  // 两个哈希值
	    // 哈希值相等比较
	    bool operator==(const Hash &b) const {
	        return a1 == b.a1 && a2 == b.a2;
	    }
	    // 哈希值小于比较
	    bool operator<(const Hash &b) const {
	        return a1 == b.a1 ? a2 < b.a2 : a1 < b.a1;
	    }
	    // 追加字符的哈希
	    Hash operator+(const int b) const {
	        return { (a1 * BASE1 + b) % P1, (a2 * BASE2 + b) % P2 };
	    }
	    // 左移操作，计算哈希的扩展
	    Hash operator<<(const int b) const {
	        return { a1 * B1[b] % P1, a2 * B2[b] % P2 };
	    }
	    // 哈希值相减
	    Hash operator-(const Hash &b) const {
	        return { (a1 - b.a1 + P1) % P1, (a2 - b.a2 + P2) % P2 };
	    }
	} h[MAXN];  // 存储哈希值数组

	// 获取字符串的子串哈希值
	Hash split(int l, int r) {
	    return h[r] - (h[l - 1] << (r - l + 1));
	}

	void init(){
	    B1[0] = B2[0] = 1;  // 初始化基数的幂
	    for (int i = 1; i < MAXN; i++) {
	        B1[i] = 1ll * B1[i - 1] * BASE1 % P1;  // 计算 BASE1 的幂
	        B2[i] = 1ll * B2[i - 1] * BASE2 % P2;  // 计算 BASE2 的幂
	    }
	}
}H;

//-----------------------------------------------#基环树找环---#树上hash-------------------------

// 用于寻找环的结构体
struct FIND_CIRCLE {
    bool cir[N];  // 标记是否在环中的节点
    PII edge[N];  // 存储每一条边
    int p[N], que[N], stk[N];  // p用于并查集，que用于存储环，stk是递归栈
    int cnt, top;  // cnt表示环的节点数量，top是栈的高度

    // 初始化
    void initC() {
        top = cnt = 0;
    }

    // 并查集找根
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    // 深度优先搜索，查找环的节点
    void dfs(int u, int fa, int g) {
        if (cir[g]) return;  // 如果已经找到环，则返回
        stk[++top] = u;  // 将当前节点加入递归栈
        if (u == g) {  // 如果找到环
            cnt = 0;
            for (int i = 1; i <= top; i++) {
                cir[stk[i]] = 1;  // 标记环上的节点
                que[++cnt] = stk[i];  // 将环的节点存入que数组
            }
            return;
        }
        // 遍历邻接表，继续深度优先搜索
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (v == fa) continue;  // 忽略父节点
            if (fa == 0 && v == g) continue;  // 如果是根节点且v是目标节点，忽略
            dfs(v, u, g);  // 递归搜索
        }
        --top;  // 递归结束后退栈
    }

    // 查找环
    void find_circle(){
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            cir[i] = 0;  // 初始化并查集和环标记
        }
        for (int i = 1; i <= m; i++) {
            int pa = find(edge[i].first), pb = find(edge[i].second);
            if (pa != pb) {
                p[pa] = pb;  // 如果不在同一个集合，则合并
            }
            else {
                dfs(edge[i].first, 0, edge[i].second);  // 否则，查找环
            }
        }
    }

    ULL pri[N];  // 用于哈希的质数表
    int siz[N];  // 用于存储子树大小

    // 初始化质数表
    void init() {
        srand(time(0));
        for (int i = 1; i <= 1e5; i++) {
            pri[i] = i * i + rand();  // 生成随机数
            if (!(pri[i] & 1)) pri[i]++;  // 确保是奇数
        }
    }

    // 计算子树的哈希值
    ULL get(int u, int fa) {
        ULL ans = 1;
        siz[u] = 1;
        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            if (v == fa) continue;  // 忽略父节点
            if (cir[v]) continue;  // 忽略环上的节点
            ans += get(v, u) * pri[siz[v]];  // 计算子树的哈希值
            siz[u] += siz[v];  // 更新子树大小
        }
        return ans;
    }

    // 检查是否是合法的环图
    void check_hash(){
        ULL hash = 0;
        bool fg = 0;
        if (cnt % 2 == 1) {  // 如果环的节点数是奇数
            hash = get(que[1], 0);  // 计算第一个节点的哈希值
            for (int i = 2; i <= cnt; i++) {
                if (get(que[i], 0) != hash) {  // 如果其他节点的哈希值不同，则标记失败
                    fg = 1;
                }
            }
        } else {  // 如果环的节点数是偶数
            hash = get(que[1], 0);
            for (int i = 3; i <= cnt; i += 2) {
                if (get(que[i], 0) != hash) {
                    fg = 1;
                }
            }
            hash = get(que[2], 0);
            for (int i = 4; i <= cnt; i += 2) {
                if (get(que[i], 0) != hash) {
                    fg = 1;
                }
            }
        }
        if (fg) {
            cout << "NO" << endl;  // 如果不满足条件，输出NO
        } else {
            cout << "YES" << endl;  // 否则，输出YES
        }
    }

    // 判断图是否满足条件
    void solve() {
        find_circle();  // 先查找环
        check_hash();  // 再判断环是否满足题意
    }
} ; 

//-------------------------------------------------#EX_KMP(Z函数)--------------------------------
/*
扩展 KMP 主要用来解决以下两个问题：
	Pattern Matching Problem（模式匹配问题）：可以在 O(n + m) 时间内求出文本串 s 中每个位置与模式串 p 的最长匹配前缀长度。
	这可以用于改进的字符串匹配算法，尤其是在需要知道部分匹配信息的情况下。

	LCP Between Prefixes of Pattern（模式串的后缀与自身的最长公共前缀问题）：求模式串 p 的每个后缀与整个模式串的最长公共前缀长度。

Z 函数 z[i] 表示字符串 s 从位置 i 开始的后缀和 s 的前缀的最长公共前缀长度
p[i] 表示 t 从位置 i 开始的后缀与 s 的前缀的最长公共前缀长度

*/

struct EXKMP {
	int z[N], p[N];  // z数组存储模式串的Z函数，p数组存储文本与模式串的匹配信息
	char s[N], t[N];  // s存储模式串，t存储文本串

	/**
	 * @brief 计算字符串 s 的 Z 函数
	 * Z 函数 z[i] 表示字符串 s 从位置 i 开始的后缀和 s 的前缀的最长公共前缀长度
	 * @param s 字符串 s
	 * @param n 字符串 s 的长度
	 */
	void get_z(char* s, int n) {
		z[1] = n;  // 初始化，z[1] 表示整个字符串的长度
		for (int i = 2, l = 0, r = 0; i <= n; ++i) {
			// 如果当前位置 i 在当前的区间 [l, r] 内，则利用之前的计算结果
			if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
			// 继续扩展当前的 Z 值，比较 s 的后缀与前缀
			while (s[1 + z[i]] == s[i + z[i]]) z[i]++;
			// 更新区间 [l, r]，使其覆盖当前的 Z 匹配区域
			if (i + z[i] - 1 > r) {
				l = i;
				r = i + z[i] - 1;
			}
		}
	}

	/**
	 * @brief 计算文本串 t 与模式串 s 的最长公共前缀长度
	 * p[i] 表示以 t[i] 为起点，和 s 的最长公共前缀长度。
	 * @param s 模式串
	 * @param n 模式串的长度
	 * @param t 文本串
	 * @param m 文本串的长度
	 */
	void get_p(char* s, int n, char* t, int m) {
		get_z(s, n);
		for (int i = 1, l = 0, r = 0; i <= m; ++i) {
			// 如果 i 在 [l, r] 内，使用之前的 Z 值进行推断
			if (i <= r) p[i] = min(r - i + 1, z[i - l + 1]);
			// 继续比较 t 和 s，扩展当前匹配的长度
			while (1 + p[i] <= n && i + p[i] <= m && s[1 + p[i]] == t[i + p[i]]) p[i]++;
			// 更新区间 [l, r]，使其覆盖当前的匹配区域
			if (i + p[i] - 1 > r) {
				l = i;
				r = i + p[i] - 1;
			}
		}
	}

	/**
	 * @brief 处理模式串和文本串，计算答案
	 */
	void solve() {
		// 输入文本串 t 和模式串 s，输入从下标 1 开始存储
		cin >> t + 1;
		cin >> s + 1;

		int ls = strlen(s + 1), lt = strlen(t + 1);  // 获取模式串和文本串的长度
		get_z(s, ls);  // 计算模式串的 Z 函数
		get_p(s, ls, t, lt);  // 计算文本串与模式串的匹配情况

		LL ans = 0;

		// 计算模式串 Z 函数的异或和结果
		for (int i = 1; i <= ls; i++) {
			ans ^= 1LL * i * (z[i] + 1);  // 这里的 z[i] + 1 表示 i 位置的 Z 值加上 1
		}
		cout << ans << endl;  // 输出模式串的结果

		ans = 0;

		// 计算文本串 p 数组的异或和结果
		for (int i = 1; i <= lt; i++) {
			ans ^= 1LL * i * (p[i] + 1);  // 这里的 p[i] + 1 表示 i 位置的匹配值加上 1
		}
		cout << ans << endl;  // 输出文本串的结果
	}
}exkmp;

//-------------------------------------------------#KMP------------------------------------------
/*
next 数组：next[i] 表示模式串 p[1] 到 p[i] 的最长相同前后缀的长度，用于在匹配失败时跳过一些字符，从而提高匹配效率。
*/

struct KMP {
	int ne[N]; // 存储模式串的 next 数组，用于加速匹配过程
	char s[N], p[N]; // s 为文本串，p 为模式串

	// KMP 算法的求解函数
	int solve() {
		// 读取模式串的长度和内容
		scanf("%d%s", &n, p + 1); // 模式串从 p[1] 开始存储
		// 读取文本串的长度和内容
		scanf("%d%s", &m, s + 1); // 文本串从 s[1] 开始存储

		// 计算模式串的 next 数组
		for (int i = 2, j = 0; i <= n; i++) {
			// 当模式串前后缀不匹配时，回退 j 到之前的位置
			while (j && p[i] != p[j + 1]) j = ne[j];
			// 如果当前字符匹配，则更新 j
			if (p[i] == p[j + 1]) j++;
			// 更新 next 数组
			ne[i] = j;
		}

		// KMP 匹配过程
		for (int i = 1, j = 0; i <= m; i++) {
			// 当字符不匹配时，使用 next 数组进行回退
			while (j && s[i] != p[j + 1]) j = ne[j];
			// 如果字符匹配，更新 j
			if (s[i] == p[j + 1]) j++;
			// 如果 j 达到 n，说明模式串匹配成功
			if (j == n) {
				// 输出匹配的起始位置（匹配的结束位置 i 减去模式串的长度 n）
				printf("%d ", i - n);
				// 匹配成功后，将 j 置为 next 数组中的值，继续寻找下一个匹配
				j = ne[j];
			}
		}
		return 0; // 返回 0 表示程序正常结束
	}
}kmp;
//------------------------------------------------#TRIE------------------------------------------

// 字典树结构体 TRIE
struct TRIE {
    static const int MAXN = 1e6 + 10;  // 定义字典树的最大节点数
    int tr[MAXN][26];  // 字典树数组，存储 26 个小写字母的子节点
    LL cnt[30][30], siz[MAXN];  // cnt 存储字母对关系的计数，siz 存储每个节点的大小（即经过该节点的字符串数目）
    int idx = 1;  // 当前可用的最大节点索引，初始化为 1（根节点）
    LL sum;  // 用于记录总的字符对数

    // 将字符串 s 插入字典树中
    void insert(char* s) {
        int len = strlen(s + 1);  // 获取字符串长度，s+1 是因为输入字符串从下标 1 开始存储
        int u = 1;  // 从字典树的根节点开始插入

        // 遍历字符串中的每一个字符
        for (int i = 1; i <= len; i++) {
            int ch = s[i] - 'a';  // 将字符转换为索引（a -> 0, b -> 1, ..., z -> 25）
            
            // 如果该字符对应的子节点不存在，创建新节点
            if (!tr[u][ch]) tr[u][ch] = ++idx;

            // 更新当前节点上所有其他字符的计数
            for (int j = 0; j < 26; j++) {
                if (j == ch) continue;  // 跳过当前字符，更新其他字符的计数
                cnt[ch][j] += siz[tr[u][j]];  // 统计当前节点中其他字符 j 出现的次数
            }

            // 移动到下一个字符对应的子节点
            u = tr[u][ch];
            ++siz[u];  // 当前节点的大小（经过该节点的字符串数目）加 1
        }

        // 更新最后一个节点中的所有其他字符的计数
        for (int i = 0; i < 26; i++) {
            sum += siz[tr[u][i]];  // 将所有字符对的计数累加到 sum 中
        }
    }
};



//---------------------------------------------#AC自动机（trie图）-------------------------------------
/*
代码结构：
	init()：初始化 AC 自动机，包括 Trie 树、结束模式串计数数组 e 和失败指针数组 fail。
	insert()：将模式串插入到 Trie 树中，构建 Trie 树的节点。
	build()：构建 AC 自动机的失败指针，通过广度优先搜索（BFS）建立失败指针，从根节点开始，遍历每个节点的所有子节点。
	query()：在给定的文本串中查找匹配的模式串。通过 Trie 树的转移和失败指针链，找到所有可能的模式串匹配，并统计结果。
	solve()：处理每个测试用例，插入模式串，构建 AC 自动机，并查找模式串在文本中的匹配情况。
	main()：主函数处理多个测试用例。

AC 自动机的作用：(文本串：文本，模式串：模板，在文本串中找模式串)
	AC 自动机可以高效地在文本串中查找多个模式串。通过构建 Trie 树和失败指针，它可以在一次遍历文本串的过程中完成对所有模式串的匹配。

Trie 中的结点表示的是某个模式串的前缀。我们在后文也将其称作状态。一个结点表示一个状态，Trie 的边就是状态的转移。
AC 自动机利用一个 fail 指针来辅助多模式串的匹配。
状态 u 的 fail 指针指向另一个状态 v，且 v 是 u 的最长后缀（即在若干个后缀状态中取最长的一个作为 fail 指针）。

fail 指针与 KMP 中的 next 指针相比：
	共同点：两者同样是在失配的时候用于跳转的指针。
	不同点：next 指针求的是最长 Border（即最长的相同前后缀），而 fail 指针指向所有模式串的前缀中匹配当前状态的最长后缀。
	因为 KMP 只对一个模式串做匹配，而 AC 自动机要对多个模式串做匹配。有可能 fail 指针指向的结点对应着另一个模式串，两者前缀不同。
	总结下来，AC 自动机的失配指针指向当前状态的最长后缀状态。
	注意：AC 自动机在做匹配时，同一位上可匹配多个模式串。
*/
struct AC_TRIE {
	int tr[N * K][26], e[N * K], idx; // Trie 树数组，tr 用于存储节点，e 记录以该节点结束的模式串数量，idx 记录当前的节点编号
	int fail[N * K]; // 失败指针数组
	char s[M]; // 输入的模式串和文本串
	// 初始化 AC 自动机
	void init(int n) {
		memset(tr, 0, sizeof tr); // 初始化 Trie 树
		memset(e, 0, sizeof e); // 初始化结束模式串的数量
		memset(fail, 0, sizeof fail); // 初始化失败指针
		idx = 0; // 初始化节点编号为 0
	}

	// 将模式串插入到 Trie 树中
	void insert() {
		int p = 0; // 从根节点开始
		for (int i = 0; s[i]; i++) { // 遍历模式串中的每个字符
			int t = s[i] - 'a'; // 计算字符对应的子节点索引
			if (!tr[p][t]) tr[p][t] = ++idx; // 如果当前节点没有相应字符的子节点，则创建新的节点
			p = tr[p][t]; // 移动到下一个节点
		}
		e[p]++; // 该节点代表一个模式串，计数加1
	}

	// 构建 AC 自动机中的失败指针
	void build() {
		queue<int> q; // 用于广度优先搜索的队列
		for (int i = 0; i < 26; i++) { // 初始化根节点的所有子节点的失败指针
			if (tr[0][i]) q.push(tr[0][i]); // 如果根节点有这个字符的子节点，加入队列
		}
		while (q.size()) { // 开始广度优先搜索
			int u = q.front(); // 取出队头元素
			q.pop();
			for (int i = 0; i < 26; i++) { // 遍历当前节点的所有子节点
				if (tr[u][i]) { // 如果存在子节点
					fail[tr[u][i]] = tr[fail[u]][i]; // 设置子节点的失败指针
					q.push(tr[u][i]); // 将子节点加入队列
				}
				else { // 如果不存在子节点，则通过失败指针链接到相应的字符位置
					tr[u][i] = tr[fail[u]][i];
				}
			}
		}
	}

	// 在文本串中查询模式串的匹配（如果每条路径只需走一遍，就将e[j]=0改为e[j]=-1）
	int query(char* t) {
		int u = 0, res = 0; // u 记录当前在 Trie 树中的位置，res 记录匹配的模式串数量
		for (int i = 1; t[i]; i++) { // 遍历文本串
			u = tr[u][t[i] - 'a']; // 根据当前字符在 Trie 树中转移
			for (int j = u; j; j = fail[j]) { // 沿着失败指针链查找
				res += e[j]; // 累加当前节点匹配的模式串数量
				e[j] = 0; // 清空匹配数量，避免重复计数
			}
		}
		return res; // 返回匹配的模式串数量
	}

	// 处理每个测试用例
	void solve() {
		cin >> n; // 读取模式串数量
		init(n); // 初始化 AC 自动机
		for (int i = 1; i <= n; i++) {
			scanf("%s", s); // 读取每个模式串
			insert(); // 将模式串插入 Trie 树
		}
		build(); // 构建 AC 自动机的失败指针
		scanf("%s", s + 1); // 读取文本串
		int ret = query(s); // 查询模式串在文本串中的匹配情况
		cout << ret << endl; // 输出匹配的模式串数量
	}
};

//-------------------------------------------#AC自动机拓扑优化------------------------------

/*

因为我们的 AC 自动机中，每次匹配，会一直向 fail 边跳来找到所有的匹配，但是这样的效率较低，在某些题目中会超时。
那么需要如何优化呢？首先需要了解到 fail 指针的一个性质：一个 AC 自动机中，如果只保留 fail 边，那么剩余的图一定是一棵树。
这是显然的，因为 fail 不会成环，且深度一定比现在低，所以得证。
这样 AC 自动机的匹配就可以转化为在 fail 树上的链求和问题，只需要优化一下该部分就可以了。
这里提供两种思路。

拓扑排序优化：
    观察到时间主要浪费在在每次都要跳 fail。如果我们可以预先记录，最后一并求和，那么效率就会优化。
    于是我们按照 fail 树，做一次内向树上的拓扑排序，就能一次性求出所有模式串的出现次数。
    build 函数在原先的基础上，增加了入度统计一部分，为拓扑排序做准备。

*/

struct AC_TRIE2 {
    char str[N], s[N]; // 用于存储输入的模式串和文本串
    static const int K = 2e6 + 10; // Trie 树的节点数量

    int tr[K][26], e[K], idx; // Trie 树数组，tr 存储节点，e 记录以该节点结束的模式串数量，idx 记录当前节点编号
    int fail[K]; // 失败指针数组
    int cnt[K], du[K]; // 计数数组和入度数组

    int ans[N]; // 存储匹配结果
    int id[K], id_cnt; // 存储每个模式串的唯一编号和编号计数

    // 初始化 AC 自动机
    void init() {
        memset(tr, 0, sizeof tr); // 初始化 Trie 树
        memset(e, 0, sizeof e); // 初始化结束模式串的数量
        memset(fail, 0, sizeof fail); // 初始化失败指针
        idx = 0; // 初始化节点编号
    }

    // 将模式串插入到 Trie 树中
    void insert(char* s, int c) {
        int p = 0; // 从根节点开始
        for (int i = 0; s[i]; i++) { // 遍历模式串中的每个字符
            int t = s[i] - 'a'; // 计算字符对应的子节点索引
            if (!tr[p][t]) tr[p][t] = ++idx; // 如果当前节点没有相应字符的子节点，则创建新的节点
            p = tr[p][t]; // 移动到下一个节点
        }
        if (!e[p]) e[p] = ++id_cnt; // 如果此节点是首次结束模式串，则分配新的模式串编号
        id[c] = e[p]; // 记录模式串编号
    }

    // 构建 AC 自动机中的失败指针
    void build() {
        queue<int> q; // 用于广度优先搜索的队列
        for (int i = 0; i < 26; i++) { // 初始化根节点的所有子节点的失败指针
            if (tr[0][i]) q.push(tr[0][i]); // 如果根节点有这个字符的子节点，加入队列
        }
        while (!q.empty()) { // 开始广度优先搜索
            int u = q.front(); // 取出队头元素
            q.pop();
            for (int i = 0; i < 26; i++) { // 遍历当前节点的所有子节点
                if (tr[u][i]) { // 如果存在子节点
                    fail[tr[u][i]] = tr[fail[u]][i]; // 设置子节点的失败指针
                    du[tr[fail[u]][i]]++; // 更新入度
                    q.push(tr[u][i]); // 将子节点加入队列
                } else { // 如果不存在子节点，则通过失败指针链接到相应的字符位置
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    // 在文本串中查询模式串的匹配
    void query(char* t) {
        int u = 0; // u 记录当前在 Trie 树中的位置
        for (int i = 1; t[i]; i++) { // 遍历文本串
            u = tr[u][t[i] - 'a']; // 根据当前字符在 Trie 树中转移
            cnt[u]++; // 增加当前节点的计数
        }
    }

    // 执行拓扑排序
    void topu() {
        queue<int> q; // 用于拓扑排序的队列
        for (int i = 0; i <= idx; i++) {
            if (du[i] == 0) {
                q.push(i); // 入度为 0 的节点入队
            }
        }
        while (!q.empty()) {
            int u = q.front(); // 当前节点
            q.pop();
            ans[e[u]] = cnt[u]; // 记录匹配结果
            int v = fail[u]; // 获取失配指针
            cnt[v] += cnt[u]; // 更新失配节点的匹配计数
            if (!--du[v]) q.push(v); // 如果入度为 0，入队
        }
    }

    // 主解决函数
    void solve() {
        cin >> n; // 输入模式串数量
        init(); // 初始化 Aho-Corasick 结构
        for (int i = 1; i <= n; i++) {
            scanf("%s", s); // 输入模式串
            insert(s, i); // 插入模式串
        }
        scanf("%s", str + 1); // 输入待匹配的文本
        build(); // 建造字典树和失配指针
        query(str); // 进行匹配
        topu(); // 执行拓扑排序并汇总结果
        for (int i = 1; i <= n; i++) {
            printf("%d\n", ans[id[i]]); // 输出每个模式串的匹配计数
        }
    }
}; // 实例化 Aho-Corasick 结构体

//---------------------------------------------#后缀自动机------------------------------------------

/*
应用：
	检查字符串是否出现
	不同子串个数(在子串s后添加一个字符形成新的子串ss,此时ss相对于s新增加的不同字串的数量为 len(ss)-len(s) )
	所有不同子串的总长度
	字典序第 k 大子串
	最小循环移位
	求每种子串出现的次数
	第一次出现的位置
	所有出现的位置
	最短的没有出现的字符串
	两个字符串的最长公共子串
	多个字符串间的最长公共子串

	
一、SAM的性质:

SAM是个状态机。一个起点，若干终点。原串的所有子串和从SAM起点开始的所有路径一一对应，不重不漏。所以终点就是包含后缀的点。
每个点包含若干子串，每个子串都一一对应一条从起点到该点的路径。且这些子串一定是里面最长子串的连续后缀。
SAM问题中经常考虑两种边：
(1) 普通边，类似于Trie。表示在某个状态所表示的所有子串的后面添加一个字符。
(2) Link、Father。表示将某个状态所表示的最短子串的首字母删除。这类边构成一棵树。
二、SAM的构造思路

endpos(s)：子串s所有出现的位置（尾字母下标）集合。SAM中的每个状态都一一对应一个endpos的等价类。
endpos的性质：
(1) 令 s1,s2 为 S 的两个子串 ，不妨设 |s1|≤|s2| （我们用 |s| 表示 s 的长度 ，此处等价于 s1 不长于 s2 ）。则 s1 是 s2 的后缀当且仅当 endpos(s1)⊇endpos(s2) ，s1 不是 s2 的后缀当且仅当 endpos(s1)∩endpos(s2)=∅　。
(2) 两个不同子串的endpos，要么有包含关系，要么没有交集。
(3) 两个子串的endpos相同，那么短串为长串的后缀。
(4) 对于一个状态 st ，以及任意的 longest(st) 的后缀 s ，如果 s 的长度满足：|shortest(st)|≤|s|≤|longsest(st)| ，那么 s∈substrings(st) 。
三、SAM的构造过程
分类讨论，具体看板书。
证明较为复杂，略。

四、SAM时间复杂度
线性。
证明较为复杂，略。


Fail 指针是指向当前节点在遇到失配时应该跳转到的节点。
具体来说，当在某个节点上处理输入字符时，如果该字符在当前节点的边上不存在，fail 指针就会引导算法回退到一个可以继续匹配的节点
*/

// 后缀自动机结构体
struct SAM {
    static const int maxn = 300003; // 定义最大节点数
    int a[maxn]; // 输入的数组
    map<int, int> ch[maxn << 2]; // 存储节点的映射关系
    int tot = 1, lst = 1; // tot为节点总数，lst为当前节点
    int len[maxn << 2], fail[maxn << 2]; // len为节点长度，fail为失败指针

    // 向后缀自动机中追加字符
    void append(int c) {
        int u = ++tot; // 创建新节点u
        int p = lst; // 当前节点为lst
        len[u] = len[p] + 1; // 新节点的长度

        // 遍历失败指针，寻找字符c可以连接的父节点
        for (; p && !ch[p][c]; p = fail[p]) ch[p][c] = u; // 找到匹配的父节点
        if (!p) fail[u] = 1; // 如果没有父节点，指向根节点
        else {
            int q = ch[p][c]; // q为匹配的节点
            if (len[q] == len[p] + 1) fail[u] = q; // 如果q是p的直接后继
            else {
                int cc = ++tot; // 创建新节点cc
                fail[cc] = fail[q]; // cc的失败指针
                len[cc] = len[p] + 1; // cc的长度
                ch[cc] = ch[q]; // 复制q的边

                // 更新p的指向
                for (; p && ch[p][c] == q; p = fail[p]) ch[p][c] = cc; // 更新p的边
                fail[q] = fail[u] = cc; // 更新q和u的失败指针
            }
        }
        lst = u; // 更新当前节点为u
    }

    // 处理输入并构建后缀自动机,并输出 a 的字典序最小循环同构的串
    void solve() {
        cin >> n; // 输入数量
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]); // 输入元素
        }
        // 重复两次输入序列以构建后缀自动机
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= n; j++) {
                append(a[j]); // 向后缀自动机中追加字符
            }
        }

        int p = 1; // 从根节点开始
        for (int i = 1; i <= n; i++) {
            map<int, int>::iterator q = ch[p].begin(); // 获取当前节点的第一个子节点
            // 输出边的值和连接的下一个节点
            p = (*q).second; // 转移到下一个节点
            cout << (*q).first << ' '; // 输出当前边的值
        }
    }
}; // 创建后缀自动机实例

//-----------------------------------------------#后缀数组-------------------------------------------
/*
时间复杂度 nlogn

sa[i] 代表所有后缀中，第 i 小的后缀的编号。
rk[i] 代表后缀 i 从小到大的排名。
height[i] 即第 i 名的后缀与第 i-1 的后缀的最长公共前缀长度。

get_sa 函数：

	该函数通过倍增法计算后缀数组 sa。
	使用了双关键字基数排序来确保每一轮计算中后缀的相对顺序是正确的。
	x 和 y 数组用于存储当前和上一轮的排名。

get_height 函数(lcp函数)：

	rk[i] 用于记录后缀 i 的排名，方便从排名推导位置。
	该函数计算 height 数组，表示 sa[i] 和 sa[i-1] 的最长公共前缀的长度。
主函数：

	首先从输入中读取字符串，接着调用 get_sa 和 get_height 计算后缀数组和最长公共前缀数组。
	最后打印后缀数组和 height 数组。
例如：
	输入
		abababab
	输出
		7 5 3 1 8 6 4 2 
		0 2 4 6 0 1 3 5 

    解释
       lsp  后缀
        0   ab
        2   abab
        4   ababab
        6   abababab
        0   b
        1   bab
        3   babab
        5   bababab   
*/
struct Suffix_Array{
    int n, m; // n 是字符串长度，m 是字符集大小
    char s[N]; // 原字符串
    int sa[N], x[N], y[N], c[N], rk[N], height[N]; // 后缀数组、临时数组、字符计数数组、排名数组、height 数组

    // 计算后缀数组的函数
    void get_sa()
    {
        // 初始化基于单个字符的排名
        for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ; // 将字符映射到 c 数组
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1]; // 计算排名前缀和
        for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i; // 基于排名填充后缀数组 sa

        // 双关键字排序
        for (int k = 1; k <= n; k <<= 1) // 每次处理长度翻倍的前缀
        {
            int num = 0;
            // 先按第二关键字排序
            // 先将没有第二关键字存入 y[]
            for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
            // 从小到大枚举第二关键字存入 y[]
            for (int i = 1; i <= n; i ++ )
                if (sa[i] > k)
                    y[ ++ num] = sa[i] - k; // 根据当前后缀的位置减去 k 的位置重新安排
            
            // 第一关键字排序，清空 c 数组
            for (int i = 1; i <= m; i ++ ) c[i] = 0;
            // 按第一关键字排序
            for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ; // 统计当前排名 
            for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1]; // 计算排名前缀和
            // 按照第二关键字从后往前枚举，用完之后就没有用了，顺便清空一下
            for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0; // 重新安排后缀数组顺序

            // 更新 x 数组，用来记录新的排名
            swap(x, y);
        	// 离散化存入x[]中
            x[sa[1]] = 1, num = 1; // 第一个后缀排名为 1
            for (int i = 2; i <= n; i ++ )
                // 判断当前两个后缀是否相同，决定是否增加排名
                x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;

            if (num == n) break; // 此时能完全区别开每个后缀，排名完全确定，退出循环
            m = num; // 更新字符集大小，即不同的个数
        }
    }

    // 计算 height 数组的函数，height 数组存储每个后缀与其前一个后缀的最长公共前缀长度
    void get_height()
    {
        // 计算每个位置的排名 rk
        for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;

        for (int i = 1, k = 0; i <= n; i ++ )
        {
            if (rk[i] == 1) continue; // 如果是排名第 1 的后缀，跳过
            if (k) k -- ; // 用前一个位置的 LCP（最长公共前缀）值来初始化 k
            int j = sa[rk[i] - 1]; // 找到前一个排名的后缀位置
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ; // 比较两个后缀的字符，计算 LCP
            height[rk[i]] = k; // 存储 LCP 值
        }
    }

    void solve(){
        // 输入字符串，读取到 s 数组中，s + 1 是为了使下标从 1 开始
        scanf("%s", s + 1);
        n = strlen(s + 1), m = 122; // 字符集范围为 0 到 122（包括字符）
        
        // 计算后缀数组
        get_sa();
        
        // 计算 height 数组
        get_height();

        // 输出后缀数组
        for (int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);
        puts("");

        // 输出 height 数组
        for (int i = 1; i <= n; i ++ ) printf("%d ", height[i]);
        puts("");
    }
}sa;

//----------------------------------------------#回文树（回文自动机）-----------------------------------
/*
回文树中每个节点包含以下信息：
	fail 指针：指向的是这个节点所代表的回文串的最长回文后缀所对应的节点
	长度：该节点所代表的回文子串的长度。
	子节点：表示可以通过在当前回文两侧添加字符得到的新的回文节点。

应用：(可以像AC自动机一样同时对多个字符串处理)
	本质不同回文子串个数
	回文子串出现次数
	最小回文划分
*/


// PAM 结构体，表示回文自动机
/*
---------------回文自动机PAM---------------
- 该结构体用于处理回文字符串的各种操作
- 记录本质不同的回文子串个数
- 所有回文子串个数
- 每种回文串出现的次数 cnt
- 每种回文串的长度 len
*/
struct PAM {
    char ss[N];   // 输入字符串的存储

    int sz, tot, last;  // sz 为当前节点数，tot 为插入字符的数量，last 表示上一个插入字符的节点
    char s[N];          // 存储构建回文自动机的字符串
    int cnt[N], ch[N][26], len[N], fail[N]; // cnt 记录每个回文串的出现次数，ch 为转移字符表，len 为回文长度，fail 为失败指针

    // 创建一个新节点，l 表示节点对应的回文长度
    int node(int l) {
        sz++;  // 新增一个节点
        memset(ch[sz], 0, sizeof ch[sz]); // 清空该节点的转移字符表
        len[sz] = l;      // 设置节点的回文长度
        fail[sz] = cnt[sz] = 0; // 初始化该节点的失败指针和计数
        return sz;         // 返回新建节点编号
    }

    // 初始化回文自动机
    PAM() {
        sz = -1;      // 初始化节点计数
        last = 0;     // 初始化 last 节点
        s[tot = 0] = '$'; // 用 '$' 作为哨兵字符，防止越界
        node(0);      // 添加一个长度为 0 的节点
        node(-1);     // 添加一个长度为 -1 的节点
        fail[0] = 1;  // 设置长度为 0 的节点的失败指针指向长度为 -1 的节点
    }

    // 获取当前字符无法扩展时的最长回文后缀对应的节点
    int getfail(int x) {
        // 循环找到满足回文条件的失败指针
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;  // 返回符合条件的回文节点
    }

    // 插入一个字符，更新回文自动机
    void insert(char c) {
        s[++tot] = c;  // 插入字符
        int now = getfail(last);  // 获取 last 节点的后缀回文
        // 如果当前字符无法从 now 节点扩展，则创建一个新节点
        if (!ch[now][c - 'a']) {
            int x = node(len[now] + 2);  // 新节点长度为当前节点长度加 2
            fail[x] = ch[getfail(fail[now])][c - 'a'];  // 设置失败指针
            ch[now][c - 'a'] = x;  // 更新字符转移表
        }
        last = ch[now][c - 'a'];  // 更新 last 节点为当前插入的回文串节点
        cnt[last]++;  // 统计回文串出现次数
    }

    // 计算并返回最大回文串长度乘以其出现次数
    LL work() {
        LL ans = 0;
        // 将回文串的出现次数向前累积
        for (int i = sz; i >= 0; i--) {
            cnt[fail[i]] += cnt[i];
        }
        // 计算每个回文串长度乘以其出现次数，取最大值
        for (int i = 1; i <= sz; i++) {
            ans = max(ans, 1ll * len[i] * cnt[i]);
        }
        return ans;  // 返回最大值
    }

    // 处理字符串并输出结果
    void solve() {
        // init();  // 初始化回文自动机
        scanf("%s", ss + 1);  // 读取输入字符串
        for (int i = 1; ss[i]; i++) {
            insert(ss[i]);  // 逐个字符插入回文自动机
        }
        cout << work() << endl;  // 输出最大回文串贡献值
    }   
    /*
    // 计算循环节
    void work() {
        LL ans = 0;  // 存储最终的答案
        for (int i = 2; i <= sz; i++) {
            LL k = len[i] - len[fail[i]];  // 计算当前回文的循环节
            if (len[i] % k == 0) {
                ans += len[i] / k * 2 - 1;  // 如果是循环节，计算贡献
            } else {
                ans++;  // 否则贡献 1
            }
        }
        cout << ans << endl;  // 输出结果
    }
    */
} pam;  // 实例化 PAM 结构体


//最小回文划分例题：https://codeforces.com/problemset/problem/932/G
/*
	border：若 0 <= r < |s|，pre(s,r)=suf(s,r)，就称 pre(s,r) 是 s 的 border。
	周期和 border 的关系：t 是 s 的 border，当且仅当 |s|-|t| 是 s 的周期。
	t 是回文串 s 的后缀，t 是 s 的 border 当且仅当 t 是回文串。
	t 是串 s 的 border (|s| <= 2|t|)，s 是回文串当且仅当 t 是回文串。
	t 是回文串 s 的 border，则 |s|-|t| 是 s 的周期，|s|-|t| 为 s 的最小周期，当且仅当 t 是 s 的最长回文真后缀。
	x 是一个回文串，y 是 x 的最长回文真后缀，z 是 y 的最长回文真后缀。令 u,v 分别为满足 x=uy,y=vz 的字符串，则有下面三条性质
		1.|u| >= |v|；
		2.如果 |u| > |v|，那么 |u| > |z|；
		3.如果 |u| = |v|，那么 u=v。
	推论：s 的所有回文后缀按照长度排序后，可以划分成 log |s| 段等差数列。
*/

/*
	核心：dp[i]表示：长度位i的前缀最小划分：dp[i]=1+min(dp[j]),要保证s[j+1]……s[i]为回文串
	优化：由上述推论可知：一个等差数列表示的所有回文串的 dp 值之和（在原问题中指 min），记录到最长的那一个回文串对应节点上。
*/
/*

题面：给定一个字符串 s，要求将 s 划分为 t_1, t_2, ..., t_k，其中 k 是偶数，且 t_i=t_{k-i+1}，求这样的划分方案数。

数组定义：
 	dp[i] 表示： s 长度为 i 的前缀的最小划分数，转移只需要枚举以第 i 个字符结尾的所有回文串
	diff[u] 表示：节点 u 和 fail[u] 所代表的回文串的长度差，即 len[u]-len[fail[u]]。
	slink[u] 表示： u 一直沿着 fail 向上跳到第一个节点 v，使得 diff[v] != diff[u]，也就是 u 所在等差数列中长度最小的那个节点
	g[v] 表示： v 所在等差数列的 dp 值之和，且 v 是这个等差数列中长度最长的节点，则 g[v]=\sum_{slink[x]=slink[v]} dp[i-len[x]]，这里 i 是当前枚举到的下标。
*/


struct PAM2 {  // 定义一个结构体 PAM，表示回文自动机
	int n;
	int sz, tot, last;  // 节点数、字符串的当前长度、最后一个回文串的节点
	int ch[N][26], len[N], fail[N];  // ch: 节点的子节点，len: 节点表示的回文串长度，fail: 失败指针
	int cnt[N], dep[N], dif[N], slink[N];  // cnt: 回文串出现次数，dep: 节点的深度，dif: 长度差，slink: 特殊指针
	char s[N], t[N], str[N];  // s: PAM中的字符串，t: 构建的回文字符串，str: 输入字符串

	int dp[N], g[N];  // dp[] 和 g[] 为动态规划数组，用于存储当前的状态

	// 辅助函数：两个数相加并对模数取模
	int add(int x, int y) {
		x += y;
		return x >= mod ? x -= mod : x;  // 如果结果超过模数，则对其进行取模
	}

	// 建立一个长度为 l 的新节点
	int node(int l) {
		sz++;  // 增加节点数量
		memset(ch[sz], 0, sizeof(ch[sz]));  // 初始化当前节点的子节点转移数组
		len[sz] = l;  // 设置当前节点的长度
		fail[sz] = 0;  // 初始化失败指针
		cnt[sz] = 0;  // 初始化回文串的出现次数
		dep[sz] = 0;  // 初始化节点的深度
		return sz;
	}

	// 初始化回文自动机
	void clear() {
		sz = -1;  // 初始化节点数量
		last = 0;  // 初始化 last 为 0 表示空串
		s[tot = 0] = '$';  // 使用 '$' 作为占位字符，避免边界问题
		node(0);  // 建立长度为0的空回文节点
		node(-1);  // 建立长度为-1的哨兵节点
		fail[0] = 1;  // 0号节点的失败指针指向1号节点
	}

	// 找到当前字符的后缀回文
	int getfail(int x) {
		// 当当前位置字符和之前回文串的下一个字符不匹配时，通过fail指针向前跳转
		while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
		return x;
	}

	// 插入字符 c 到回文自动机中，构建回文树
	void insert(char c) {
		  s[++tot] = c;  // 插入字符到当前字符串
		  int now = getfail(last);  // 找到上一个回文子串的失败指针
		  if (!ch[now][c - 'a']) {  // 如果当前字符没有对应的转移节点
			    int x = node(len[now] + 2);  // 创建一个新节点，长度为当前节点长度加2
			    fail[x] = ch[getfail(fail[now])][c - 'a'];  // 设置新节点的失败指针
			    dep[x] = dep[fail[x]] + 1;  // 新节点的深度等于其失败节点深度加1
			    ch[now][c - 'a'] = x;  // 在当前节点建立对新节点的转移
			    dif[x] = len[x] - len[fail[x]];  // 计算当前节点和其失败节点的长度差
			    if (dif[x] == dif[fail[x]])  // 如果长度差相等，设置 slink 为其失败节点的 slink
			    	slink[x] = slink[fail[x]];
			    else
			    	slink[x] = fail[x];  // 否则，slink 指向失败指针
		  }
		  last = ch[now][c - 'a'];  // 更新 last 为当前节点
		  cnt[last]++;  // 更新当前回文串的出现次数
	}

	// 执行主要的工作函数，包括构建回文自动机和动态规划
	void work(){
		clear();  // 初始化回文自动机
		scanf("%s", str + 1);  // 读取输入的字符串
		n = strlen(str + 1);  // 计算字符串的长度
		// 构建新字符串 t，将字符串 str 和它的反转拼接在一起
		for (int j = 0, i = 1; i <= n; i++) {
			t[++j] = str[i], t[++j] = str[n - i + 1];
		}
		dp[0] = 1;  // 初始化动态规划的起始状态
		for (int i = 1; i <= n; i++) {  // 遍历字符串 t，依次插入 PAM 中
		    insert(t[i]);  // 插入第 i 个字符
		    for (int x = last; x > 1; x = slink[x]) {  // 遍历当前节点的 slink 链
			  g[x] = dp[i - len[slink[x]] - dif[x]];  // 计算 g[x]，通过回文的长度差更新动态规划状态
			  if (dif[x] == dif[fail[x]]) g[x] = add(g[x], g[fail[x]]);  // 如果长度差相等，累加 g 值
			  if (i % 2 == 0) dp[i] = add(dp[i], g[x]);  // 只在偶数位置更新 dp 数组
		    }
  		}
  		cout << dp[n] << endl;  // 输出结果，即 dp[n] 表示的最终状态
	}
} pam2;  // 定义一个 pam 实例


//-------------------------------------------------#Manacher-------------------------------------------
/*
	求 len[i]:以i为中心的回文串的最大半径
*/
struct MANACHAR {
	char tmp[N];   // 临时数组，用于存储处理过的字符串，加入特殊字符进行扩展
	int Len[N];    // 存储以每个字符为中心的回文半径

	// 将原始字符串进行预处理，插入特殊字符以简化回文判断（处理奇偶长度回文串）
	int init(char* s) {
		int len = strlen(s + 1);  // 获取原始字符串的长度（从1开始）
		int k = 0;  // 临时数组的索引
		tmp[k++] = '$';  // 在临时数组的最前面加上特殊字符 '$'，避免边界判断
		tmp[k++] = '#';  // 在每个字符之间插入 '#'，处理奇偶长度的回文

		// 将原始字符串的字符加入到临时数组中，并在每个字符前后插入 '#'
		for (int i = 1; i <= len; i++) {
			tmp[k++] = s[i];  // 插入原始字符串的字符
			tmp[k++] = '#';   // 插入分隔符 '#'
		}

		tmp[k++] = '^';  // 在末尾加入特殊字符 '^'，避免边界越界

		// 返回处理后字符串的总长度
		return k;
	}

	// Manacher算法核心：用于求解最长回文子串的半径数组 Len
	void manacher(char* s, int len) {
		int mr = 0;  // 当前能扩展到的最右边界（右边界的下一个位置）
		int mid = 0;  // 与 mr 对应的回文中心

		// 遍历处理后的字符串，寻找每个位置的回文半径
		for (int i = 1; i < len; i++) {
			int j = 2 * mid - i;  // i 关于 mid 对称的位置 j

			// 若当前字符在最右边界内，可以利用对称性减少计算
			if (Len[i] < mr) {
				Len[i] = min(Len[j], mr - i);  // 从对称点的回文半径和边界的最小值开始
			}
			else {
				Len[i] = 1;  // 如果不在边界内，回文半径从1开始
			}

			// 尝试从 Len[i] 的初始值开始扩展回文串
			while (s[i + Len[i]] == s[i - Len[i]]) {
				Len[i]++;  // 如果两边字符相等，继续扩展回文半径
			}

			// 更新最右边界和中心点
			if (mr < i + Len[i]) {
				mr = i + Len[i];  // 更新最右边界
				mid = i;  // 更新中心位置
			}
		}
	}
} mlc;  // 定义一个全局的 MANACHAR 结构体实例 mlc


//-------------------------------------------#最小表示法----------------------------------
/*
算法分析：最小表示法
    本题的最小表示法就是找出字符串S的的循环同构串中字典序最小的一个。
    设S’是S的循环同构的串。那么S’可以是 “bcad” 或者 “cadb” , “adbc” , “dbca”

最小表示法的实现方法：
    假设有一个字符串S，请你求出S循环同构串的最小表示
    设S的长度为len
    1.利用两个指针i，j。初始化时i指向s[0]，j指向s[1]。
    我们规定i和j在任意时刻都不能相等。
    2.匹配长度k=0开始，检验s[i+k]和s[j+k]是否相等，相等k++，
    一直下去，直到找到第一个不相同的字符
    （若k试了一个字符串的长度也没找到不同，即整个串都是
    相同的字符。则那个位置就是最小表示位置，算法终止并返回）
    该过程中，我们发现s[i+k]和s[j+k]的关系有三种：
    　　 1).s[i+k]>s[j+k], 由于s[i~ i+k-1 ]都不会是循环字符串的"最小表示"的前缀，i滑动到i+k+1处。

    　　 2).s[i+k]<s[j+k]，同理关系 1)，j滑动到 j+k+1 处。

    　　 3).s[i+k]==s[j+k]，则k++。

    　　 若滑动后i==j，将正在变化的那个指针在+1.直到i， j把整个字串都检验完毕，返回两者中小于len的值。
    3.如果 k==len，则返回 min(i，j)

*/
struct Minimal_Representation{
    static const int SIZE=3e5+10;
    int ans,A[SIZE];
    int Min_show()
    //最小表示法求出串的最小表示
    {
        int i=0,j=1,k=0;
        //两个指针i,j,任意时刻i!=j,当前匹配长度为k
        //循环同构串要复制一遍字串(成环)接在A序列后面
        //由于数组过大,(i+k)%n和(j+k)%n代表了字串
        //复制一遍接在原序列后各字符的对应位置
        while(i<n&&j<n&&k<n)
              {
                if(A[(i+k)%n]==A[(j+k)%n])
                //两个位置数值相等，匹配长度k++
                   k++;
                else
                   {
                    if(A[(i+k)%n]>A[(j+k)%n])
                    //[i,i+k-1]与[j,j+k-1]相同
                         //那么在[i,i+k-1]中不可能有最小表示
                         //则i+=k+1,令k=0
                        i+=k+1;
                    else j+=k+1;
                    //同上
                    if(i==j)i++;
                         //任何时候都要满足i!=j
                    k=0;//匹配长度k归零
                   }
              }
        return min(i,j);//返回最小表示
    }
    void solve()
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)//初始字串
            scanf("%d",&A[i]);
        ans=Min_show();//求最小表示
        for(int i=0;i<n;i++)//输出最小表示
            printf("%d ",A[(i+ans)%n]);
    }

};

//--------------------------------------------#点分治--------------------------------------

/*

我们先随意选择一个节点作为根节点 rt，所有完全位于其子树中的路径可以分为两种，一种是经过当前根节点的路径，
一种是不经过当前根节点的路径。对于经过当前根节点的路径，又可以分为两种，一种是以根节点为一个端点的路径，
另一种是两个端点都不为根节点的路径。而后者又可以由两条属于前者链合并得到。所以，对于枚举的根节点 rt，
我们先计算在其子树中且经过该节点的路径对答案的贡献，再递归其子树对不经过该节点的路径进行求解。

点分治过程中，每一层的所有递归过程合计对每个点处理一次，假设共递归 h 层，则总时间复杂度为 O(hn)。


邻接表结构：代码通过add()函数建立邻接表，将树中的边和对应的权重存储起来。每条边在邻接表中存储两次，因为是无向图。
重心分解：通过get_wc()找到子树的重心，并通过递归分解成更小的子树。重心分解可以有效减少重复计算和路径搜索的复杂度。
计算路径：calc()函数计算以当前重心为根的所有路径，避免重复计算。每次处理一个子树时，先去除当前重心，然后递归处理剩余的子树。
双指针统计路径：get()函数通过双指针方法统计所有满足两节点间距离和不超过m的路径对数。

*/
struct Centroid_Decomposition{
    int h[N], e[M], w[M], ne[M], idx;  // h是邻接表头数组，e存储每条边的终点，w存储每条边的权重，ne是链表指针，idx是边的编号
    bool st[N];  // st数组用于标记节点是否已被删除（是否属于已处理的子树）
    int p[N], q[N];  // p和q是临时数组，用于存储从某个节点出发到其他节点的距离

    // 邻接表中添加一条边a到b，权重为c
    void add(int a, int b, int c)
    {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    }

    // 计算以u为根的子树大小，fa是u的父节点
    int get_size(int u, int fa)  
    {
        if (st[u]) return 0;  // 如果节点u已经被删除，返回0
        int res = 1;  // 子树大小初始为1
        for (int i = h[u]; ~i; i = ne[i])  // 遍历u的邻接表
            if (e[i] != fa)  // 跳过父节点
                res += get_size(e[i], u);  // 递归计算子树大小
        return res;
    }

    // 计算节点u的重心，tot是子树的总大小，wc存储重心节点
    int get_wc(int u, int fa, int tot, int& wc)  
    {
        if (st[u]) return 0;  // 如果节点u已被删除，返回0
        int sum = 1, ms = 0;  // sum是以u为根的子树大小，ms是最大子树的大小
        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            if (j == fa) continue;
            int t = get_wc(j, u, tot, wc);  // 递归获取子树大小
            ms = max(ms, t);  // 更新最大子树大小
            sum += t;  // 更新当前子树大小
        }
        ms = max(ms, tot - sum);  // 计算非子树部分的大小
        if (ms <= tot / 2) wc = u;  // 如果最大子树不超过总节点数的一半，当前节点就是重心
        return sum;
    }

    // 计算从节点u到各个子节点的距离，存入q数组
    void get_dist(int u, int fa, int dist, int& qt)
    {
        if (st[u]) return;
        q[qt ++ ] = dist;  // 将当前距离存入q数组
        for (int i = h[u]; ~i; i = ne[i])
            if (e[i] != fa)
                get_dist(e[i], u, dist + w[i], qt);  // 递归计算子节点的距离
    }

    // 统计数组a中两数之和小于等于m的对数
    int get(int a[], int k)
    {
        sort(a, a + k);  // 先对数组进行排序
        int res = 0;
        for (int i = k - 1, j = -1; i >= 0; i -- )  // 使用双指针方法统计对数
        {
            while (j + 1 < i && a[j + 1] + a[i] <= m) j ++ ;  // 找到满足条件的最大j
            j = min(j, i - 1);  // 保证i > j
            res += j + 1;  // 统计对数
        }
        return res;
    }

    // 计算以u为根的子树中满足条件的路径数
    int calc(int u)
    {
        if (st[u]) return 0;  // 如果节点u已被删除，返回0
        int res = 0;
        get_wc(u, -1, get_size(u, -1), u);  // 找到子树的重心
        st[u] = true;  // 标记重心为已删除

        int pt = 0;  // p数组的指针
        for (int i = h[u]; ~i; i = ne[i])  // 遍历重心的所有邻接点
        {
            int j = e[i], qt = 0;  // qt是q数组的指针
            get_dist(j, -1, w[i], qt);  // 计算子树中所有节点的距离
            res -= get(q, qt);  // 去重
            for (int k = 0; k < qt; k ++ )
            {
                if (q[k] <= m) res ++ ;  // 如果距离小于等于m，路径数加1
                p[pt ++ ] = q[k];  // 将距离存入p数组
            }
        }
        res += get(p, pt);  // 统计以重心为根的路径数

        for (int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);  // 递归处理子树
        return res;
    }
    int solve()
    {
        // 处理多组输入，直到输入0 0为止
        while (scanf("%d%d", &n, &m), n || m)
        {
            memset(st, 0, sizeof st);  // 重置标记数组
            memset(h, -1, sizeof h);  // 初始化邻接表
            idx = 0;  // 重置边的编号
            // 读取n-1条边
            for (int i = 0; i < n - 1; i ++ )
            {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);  // 读取边的两个端点和权重
                add(a, b, c), add(b, a, c);  // 添加双向边
            }

            printf("%d\n", calc(0));  // 输出满足条件的路径数
        }

        return 0;
    }
};

//-------------------------------------------#LCA(倍增)--------------------------------------
/*

倍增算法的预处理时间复杂度为 O(n log n)，单次查询时间复杂度为 O(log n)。

*/


struct LCA{
    vector<PII> g[N];
    int f[N][31], cost[N][31], dep[N];

    // dfs，用来为 lca 算法做准备。接受两个参数：dfs 起始节点和它的父亲节点。
    void dfs(int u, int fa) {
      // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
      f[u][0] = fa;
      dep[u] = dep[f[u][0]] + 1;
      // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
      // 2^(i-1) 的祖先节点。
      for (int i = 1; i < 31; ++i) {
        f[u][i] = f[f[u][i - 1]][i - 1];
        cost[u][i] = cost[f[u][i - 1]][i - 1] + cost[u][i - 1];
      }
      // 遍历子节点来进行 dfs。
      for(int i=0;i<g[u].size();i++){
        int v=g[u][i].first,w=g[u][i].second;
        if(v==fa)continue;
        cost[v][0]=w;
        dfs(v,u);
      }
      // int sz = g[u].size();
      // for (int i = 0; i < sz; ++i) {
      //   if (g[u][i] == fa) continue;
      //   cost[g[u][i]][0] = g[u][i];
      //   dfs(g[u][i], u);
      // }
    }

    // lca。用倍增算法算取 x 和 y 的 lca 节点。
    int lca(int x, int y) {
      // 令 y 比 x 深。
      if (dep[x] > dep[y]) swap(x, y);
      // 令 y 和 x 在一个深度。
      int tmp = dep[y] - dep[x], ans = 0;
      for (int j = 0; tmp; ++j, tmp >>= 1)
        if (tmp & 1) ans += cost[y][j], y = f[y][j];
      // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先。
      if (y == x) return ans;
      // 不然的话，找到第一个不是它们祖先的两个点。
      for (int j = 30; j >= 0 && y != x; --j) {
        if (f[x][j] != f[y][j]) {
          ans += cost[x][j] + cost[y][j];
          x = f[x][j];
          y = f[y][j];
        }
      }
      // 返回结果。
      ans += cost[x][0] + cost[y][0];
      return ans;
    }
};
//---------------------------------------------#LCA(RMQ)------------------------------------

/*

对一棵树进行 DFS，无论是第一次访问还是回溯，每次到达一个结点时都将编号记录下来，可以得到一个长度为 2n-1 的序列，这个序列被称作这棵树的欧拉序列。

在下文中，把结点 u 在欧拉序列中第一次出现的位置编号记为 pos(u)（也称作节点 u 的欧拉序），把欧拉序列本身记作 E[1..2n-1]。

有了欧拉序列，LCA 问题可以在线性时间内转化为 RMQ 问题，即 pos(LCA(u, v))=min{pos(k)|k in E[pos(u)..pos(v)]};

预处理的时间复杂度为 O(n\log n)，每次查询 LCA 的时间复杂度为 O(1)。

*/
struct RMQ_LCA {
    vector<PII> g[N]; // 图的邻接表
    int dist[N]; // 记录每个节点到根节点的距离
    int depth[N << 1], lg[N << 1]; // 深度数组和对数数组
    int dfn[N << 1], pos[N], tot; // DFS序列、节点位置、节点总数
    int st[30][(N << 1) + 2], rev[30][(N << 1) + 2]; // 稀疏表和对应节点编号

    // 深度优先搜索函数
    void dfs(int cur, int dep) {
        dfn[++tot] = cur; // 记录当前节点的DFS序列
        depth[tot] = dep; // 记录当前深度
        pos[cur] = tot; // 记录当前节点在DFS序列中的位置
        for (int i = 0; i < g[cur].size(); i++) { // 遍历当前节点的所有子节点
            int v = g[cur][i].first; // 获取子节点
            if (!pos[v]) { // 如果子节点还未被访问
                dist[v] = dist[cur] + g[cur][i].second; // 更新子节点距离
                dfs(v, dep + 1); // 递归DFS，深度加1
                dfn[++tot] = cur; // 记录当前节点（回溯）
                depth[tot] = dep; // 记录回溯时的深度
            }
        }
    }

    // 初始化函数，构建稀疏表
    void init(int u) {
        dfs(u, 0); // 从根节点开始DFS
        // 预处理lg数组，用于快速计算区间长度的对数值
        for (int i = 2; i <= tot + 1; ++i)
            lg[i] = lg[i >> 1] + 1; // 计算i的二进制位数（对数）

        // 初始化稀疏表的第一行，存储深度
        for (int i = 1; i <= tot; i++) {
            st[0][i] = depth[i]; // 深度数组
            rev[0][i] = dfn[i]; // DFS序列中的节点
        }

        // 构建稀疏表
        for (int i = 1; i <= lg[tot]; i++) // 从第1行开始
            for (int j = 1; j + (1 << i) - 1 <= tot; j++) // 确保范围合法
                if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)]) // 比较两个区间的最小深度
                    st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j]; // 选择左区间的值
                else
                    st[i][j] = st[i - 1][j + (1 << i - 1)], // 选择右区间的值
                    rev[i][j] = rev[i - 1][j + (1 << i - 1)]; // 更新对应节点
    }

    // 查询区间[l, r]的最小深度对应的节点,求 LCA
    int query(int l, int r) {
        l = pos[l], r = pos[r]; // 获取DFS序列中的位置
        if (l > r) swap(r, l); // 确保l小于等于r
        int k = lg[r - l + 1]; // 计算区间长度的对数
        // 比较两个可能的区间并返回对应的节点
        return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l] : rev[k][r + 1 - (1 << k)];
    }

    // 计算两个节点之间的距离
    int getdist(int x, int y) {
        int l = query(x, y); // 获取x和y的LCA
        return dist[x] + dist[y] - 2ll * dist[l]; // 计算距离
    }
} ;

//-----------------------------------------#kruskal重构树(倍增)-----------------------------------
/*
kruskal重构树有几条重要的性质：
 1.树上除叶子结点以外的点都对应着原来生成树中的边，叶子结点就是原来生成树上的节点。
 2.由于新点的创建顺序与原来生成树上边权的大小有关，从每个点到根节点上除叶子结点外按顺序访问到的点的点权是单调的。 
 3.出于kruskal算法贪心的性质，两个点u和v的lca的点权就对应着它们最小生成树上的瓶颈。 
 4.实际上这棵树就是一个二叉堆
*/

/*
Kruskal 结构体：

	kruskal 函数构建最小生成树并处理查询。
	dfs 函数用于深度优先搜索构建倍增表。
	find 函数使用并查集来查找根节点。
	ask 函数用于倍增查询。
*/

// Kruskal 重构树算法的结构体
// Kruskal 重构树算法的结构体
struct KRUSKAL {
	int Q;

    struct Edge {
        int u, v, w;  // u 和 v 是边的端点，w 是边权（长度）
    } E[M];  // 存储所有边

    vector<int> g[N];  // 存储生成树的邻接表
    LL v[N], cost[N][30], c[N];  // v存储节点的属性值，cost存储倍增跳跃的最大代价，c记录以i为根的子树权值和
    int p[N], dep[N];  // p 是并查集的父节点数组，dep 是节点深度
    int f[N][30];  // 倍增数组，用于快速查询祖先节点


    // 初始化倍增表，通过DFS生成倍增跳跃表
    void dfs(int now) {
        int LOGN = 25;
        for (int j = 1; j <= LOGN; j++) {
            for (int u = 1; u <= now; u++) {
                f[u][j] = f[f[u][j-1]][j-1];  // f[u][j]记录从u通过2^j步到达的节点
                cost[u][j] = max(cost[u][j-1], cost[f[u][j-1]][j-1]);  // 记录跳跃时的最大代价
            }
        }
    }

    // 查询符合条件的节点，即在给定限制下能到达的最高祖先
    int ask(int x, int y) {
        int LOGN = 25;
        for (int i = LOGN; i >= 0; i--) {  // 倍增查找祖先节点
            if (cost[x][i] <= y && f[x][i]) x = f[x][i];  // 如果可以跳到父节点且满足限制，进行跳跃
        }
        return c[x];  // 返回符合条件的节点的权值和
    }

    // 并查集查找根节点
    int find(int x) {
        if (p[x] == x) return x;  // 如果x是自身的父节点，返回x
        return p[x] = find(p[x]);  // 否则递归寻找根节点，并进行路径压缩
    }

    // Kruskal 算法构建最小生成树
    void kruskal() {
        for (int i = 1; i <= (n << 1); i++) {
            p[i] = i;  // 初始化并查集，每个节点自成一个集合
        }

        // 按照边权从小到大排序，构建最小生成树
        sort(E + 1, E + 1 + m, [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });
        int e_cnt = 0;  // 记录加入生成树的边数
        int n_cnt = n;  // 新节点编号从n+1开始
        for (int i = 1; i <= m; i++) {
            int a = E[i].u, b = E[i].v;
            int pa = find(a), pb = find(b);  // 找到a和b的根节点
            if (pa != pb) {  // 如果根节点不同，则合并
                ++n_cnt;  // 新节点编号增加
                p[pa] = n_cnt;  // 更新并查集
                p[pb] = n_cnt;
                v[n_cnt] = E[i].w;  // 新节点的属性值为当前边的权值
                c[n_cnt] = c[pa] + c[pb];  // 新节点的权值和为两个子节点的权值和
                cost[pa][0] = v[n_cnt] - c[pa];  // 记录跳到父节点的代价
                cost[pb][0] = v[n_cnt] - c[pb];
                f[pa][0] = f[pb][0] = n_cnt;  // 更新父节点
                ++e_cnt;
            }
            if (e_cnt == n - 1) break;  // 如果生成树构建完成，退出
        }
        dfs(n_cnt);  // 构建倍增跳跃表
        while (Q--) {
            int x, y;
            cin >> x >> y;
            LL ret = ask(x, y);  // 查询符合条件的节点
            printf("%lld\n", ret + y);  // 输出结果
        }
    }

    // 求无向连通图中子图点权和值不小于边权的情况下能求得的最大和值
    void solve() {
        cin >> n >> m >> Q;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);  // 输入每个城市的社会能力点数
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);  // 输入每条边的信息
        }
        kruskal();  // 调用 Kruskal 算法构建最小生成树并处理查询
    }

} ; // Kruskal 实例

//-------------------------------------------#tarjan强连通分量算法---------------------------
// 它的时间复杂度是 O(V + E)，其中：
// V 表示图中的顶点数量（vertices）。
// E 表示图中的边数量（edges）。

// Tarjan 算法结构体，用于求解强连通分量 (SCC)
struct TARJAN1 {
	void ADD(int a,int b){}
    // 图的邻接表和边相关信息
    int h[N], e[M], ne[M], idx; 
    int dfn[N], low[N], timestamp;  // Tarjan 算法的时间戳、dfn 和 low 数组
    int stk[N], top;  // 栈用于存储当前访问的节点
    bool in_stk[N];  // 节点是否在栈中的标志
    int id[N], scc_cnt, scc_size[N];  // id 表示节点所属的强连通分量

    // 构造函数，初始化一些数据结构
    TARJAN1() {
        memset(h, -1, sizeof h);
        idx = timestamp = top = scc_cnt = 0;
    }

    // 添加一条边到邻接表
    void add(int a, int b) {
        e[idx] = b;  // 目标节点
        ne[idx] = h[a];  // 邻接链
        h[a] = idx++;  // 更新头指针
    }

    // Tarjan 算法的实现，寻找强连通分量
    void tarjan(int u) {
        dfn[u] = low[u] = ++timestamp;  // 初始化 dfn 和 low 值
        stk[++top] = u;  // 将节点压栈
        in_stk[u] = true;  // 标记节点在栈中

        // 遍历所有邻接边
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if (!dfn[j]) {  // 如果节点 j 没有被访问
                tarjan(j);  // 递归访问
                low[u] = min(low[u], low[j]);  // 更新节点 u 的 low 值
            } else if (in_stk[j]) {
                low[u] = min(low[u], dfn[j]);  // 更新 low 值
            }
        }

        // 如果发现了强连通分量的根节点
        if (dfn[u] == low[u]) {
            ++scc_cnt;  // 新增一个强连通分量
            int y;
            do {
                y = stk[top--];  // 弹出栈顶元素
                in_stk[y] = false;  // 标记不在栈中
                id[y] = scc_cnt;  // 记录节点的分量
                scc_size[scc_cnt]++;  // 统计强连通分量大小
            } while (y != u);  // 直到回到根节点
        }
    }

    // 处理并求解强连通分量
    void solve() {
        for (int i = 1; i <= m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);  // 读取边
            add(a, b);  // 添加边
        }

        // 对每个节点执行 Tarjan 算法
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                tarjan(i);
        }

        // 建立强连通分量之间的拓扑图
        unordered_set<LL> s;  // 使用哈希集合去重
        for (int i = 1; i <= n; i++) {
            for (int j = h[i]; j != -1; j = ne[j]) {
                int k = e[j];
                int a = id[i], b = id[k];
                LL hash = a * 1000000LL + b;  // 生成哈希值
                if (a != b && !s.count(hash)) {
                    ADD(a, b);  // 建立新的边
                    s.insert(hash);
                }
            }
        }
    }
} ;

//---------------------------------------------#tarjan桥-------------------------------------------
/*
low_v=dfn_u 表示还可以回到父节点，如果顶点 v 不能回到祖先也没有另外一条回到父亲的路，那么 u-v 这条边就是割边。
*/

struct BRIDGE{
    // std::vector<int> G[N];
    int low[N], dfn[N], dfs_clock;  // low[]: 记录每个节点能够回溯到的最早访问的节点
                                          // dfn[]: 记录节点的访问时间（时间戳）
                                          // dfs_clock: 全局时间戳计数器
    bool isbridge[N];                  // isbridge[]: 用于标记是否是桥（桥边）
    vector<int> G[N];                  // G[]: 图的邻接表
    int cnt_bridge;                       // cnt_bridge: 记录桥的数量
    int father[N];                     // father[]: 记录每个节点的父节点

    // Tarjan 算法的递归函数，用于找到图中的桥
    void tarjan(int u, int fa) {
      father[u] = fa;  // 记录当前节点 u 的父节点
      low[u] = dfn[u] = ++dfs_clock;  // 初始化当前节点 u 的 dfn 和 low 为时间戳

      // 遍历当前节点 u 的所有邻接节点
      for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];  // 取出相邻节点 v

        // 如果 v 还没有被访问过
        if (!dfn[v]) {
          tarjan(v, u);  // 递归调用 Tarjan 函数对 v 进行深度优先搜索
          low[u] = min(low[u], low[v]);  // 更新 u 的 low 值

          // 如果 v 的 low 值大于 u 的 dfn 值，说明 u-v 是一条桥
          if (low[v] > dfn[u]) {
            isbridge[v] = true;  // 标记 v 为桥
            ++cnt_bridge;  // 计数桥的数量
          }
        } 
        // 如果 v 已经访问过，且 v 不是 u 的父节点
        else if (dfn[v] < dfn[u] && v != fa) {
          low[u] = min(low[u], dfn[v]);  // 更新 u 的 low 值为 v 的 dfn
        }
      }
    }
};


//-----------------------------------------------#边的双连通分量--------------------------------------

//求边双连通分量的过程实际上就是求强连通分量的过程，时间复杂度 O(n+m)。
//（们先总结出一个重要的性质，在无向图中，DFS 生成树上的边不是树边就只有非树边。
//我们联系一下求强连通分量的方法，在无向图中只要一个分量没有桥，那么在 DFS 生成树上，它的所有点都在同一个强连通分量中。
//反过来，在 DFS 生成树上的一个强连通分量，在原无向图中是边双连通分量。）


struct TARJAN2 {
	vector<int>g[N]; // 邻接表，g[i] 存储与节点 i 相连的所有节点
	int dfn[N], low[N], timestamp; // dfn[i] 记录节点 i 被访问的时间戳，low[i] 记录 i 或 i 的子节点能够回溯到的最早祖先的时间戳
	stack<int>stk; // 栈，用于存储当前未完成的连通分量的节点
	int col[N], dcc[N], dcc_cnt; // col[i] 记录节点 i 所在的双连通分量编号，dcc[i] 记录第 i 个双连通分量的大小，dcc_cnt 是双连通分量的计数器
	vector<int>sz[N]; // 每个双连通分量中节点的集合

	// Tarjan 算法核心递归函数，x 是当前节点，fa 是父节点
	void tarjan(int x, int fa) {
		stk.push(x); // 将当前节点压入栈中
		dfn[x] = low[x] = ++timestamp; // 为当前节点 x 分配时间戳
		bool flg = 0; // 标记是否已经处理过父节点，防止重复处理 fa
		for (auto j : g[x]) { // 遍历与节点 x 相邻的每个节点 j
			if (j == fa && !flg) { // 跳过父节点 fa，但只跳过一次，防止重复
				flg = 1;
				continue;
			}
			if (!dfn[j]) { // 如果 j 没有被访问过
				tarjan(j, x); // 递归访问 j
				low[x] = min(low[x], low[j]); // 更新 x 的 low 值
			}
			else {
				low[x] = min(low[x], dfn[j]); // 如果 j 已经访问过，更新 x 的 low 值
			}
		}
		// 如果 x 是一个连通分量的根节点
		if (dfn[x] == low[x]) {
			int u = 0;
			dcc_cnt++; // 新的双连通分量
			dcc[dcc_cnt] = 0; // 初始化当前双连通分量的大小
			do {
				u = stk.top(); // 从栈顶取出节点
				stk.pop(); // 弹出栈顶节点
				col[u] = dcc_cnt; // 将节点 u 标记为属于当前双连通分量
				dcc[dcc_cnt]++; // 增加当前双连通分量的节点数量
			} while (u != x); // 直到处理完当前连通分量的所有节点
		}
	}

	// 初始化函数，清空图，时间戳，栈等信息
	void init(int n) {
		for (int i = 1; i <= n; i++) {
			g[i].clear(); // 清空邻接表
			dfn[i] = low[i] = 0; // 重置 dfn 和 low 数组
		}
		while (!stk.empty()) stk.pop(); // 清空栈
		timestamp = dcc_cnt = 0; // 重置时间戳和双连通分量计数器
	}
} tar;
//----------------------------------------------#Dijkstra-----------------------------------
struct DIJKSTRA {
	vector<PII>g[M];
	LL dist[M];
	bool vis[M];
	int idx = n;
    void init(int x){
        idx=x;
        for (int i = 1; i <= idx; i++)dist[i] = INF, vis[i] = 0;
    }
	LL dij(int u) {
		dist[u] = 0;
		priority_queue<PII, vector<PII>, greater<PII>>q;
		q.push({ dist[u],u });
		while (!q.empty()) {
			int t = q.top().second;
			q.pop();
			if (vis[t])continue;
			vis[t] = 1;
			for (int i = 0; i < g[t].size(); i++) {
				int j = g[t][i].first, w = g[t][i].second;
				if (dist[j] > dist[t] + w) {
					dist[j] = dist[t] + w;
					q.push({ dist[j],j });
				}
			}
		}
		return dist[1];
	}
};
//------------------------------------------------#spfa------------------------------------------

struct SPFA{
    vector<PII>g[N];
    int len=0;
    LL dist[N];
    bool vis[N];
    void init(int u){
        len=u;
        for(int i=1;i<=len;i++){
            dist[i]=INF;
            vis[i]=0;
        }
    }
    LL spfa() {
        dist[1] = 0;
        queue<int>q;
        q.push(1);
        vis[1] = 1;
        int t;
        while (!q.empty()) {
            t = q.front();
            q.pop();
            vis[t] = 0;
            for (int i = 0; i <g[t].size(); i++) {
                int j = g[t][i].first;
                int d = g[t][i].second;
                if (dist[j] > dist[t] + d) {
                    dist[j] = dist[t] + d;
                    if (vis[j] == 0) {
                        vis[j] = 1;
                        q.push(j);
                    }
                }
            }
        }
        return dist[n];
    }
    
};
//-------------------------------------------------#网络流----------------------------------------

struct STL_DINIC {
    vector<tuple<int, int, int>> g[M];  // 图的邻接表，tuple<int, int, int> 表示 (目标节点, 反向边索引, 剩余流量)
    int dep[M], st[M];  // dep 是层次图中的深度，st 是当前弧优化指针，用于 DFS 时遍历未访问的边

    // 清空图
    void clear(int n) {
        for (int i = 0; i <= n; i++) {
            g[i].clear();  // 清空每个节点的邻接表
        }
    }

    // 添加一条从 a 到 b 的容量为 c 的边，同时添加一条反向边，容量为 0
    void add(int a, int b, int c) {
        g[a].emplace_back(b, int(g[b].size()), c);  // 正向边 a -> b, 容量为 c
        g[b].emplace_back(a, int(g[a].size()) - 1, 0);  // 反向边 b -> a, 容量为 0
    }

    // 通过广度优先搜索 (BFS) 构建分层图
    bool bfs(int s, int t, int n) {
        queue<int> q;  // 队列用于 BFS
        memset(dep, inf, sizeof(int) * (n + 2));  // 初始化所有节点的深度为无穷大
        memset(st, 0, sizeof(int) * (n + 2));  // 初始化当前弧优化指针
        q.push(s);  // 将源点入队
        dep[s] = 0;  // 源点深度为 0
        while (!q.empty()) {
            int u = q.front(); q.pop();  // 取出队首元素 u
            for (auto [v, r, f] : g[u]) {  // 遍历 u 的所有邻接边
                if (!f) continue;  // 如果边上没有剩余流量，跳过
                if (dep[v] > dep[u] + 1) {  // 如果找到更短的路径，更新深度
                    dep[v] = dep[u] + 1;
                    q.push(v);  // 将目标节点 v 入队
                }
            }
        }
        return dep[t] < inf;  // 返回是否能到达汇点 t
    }

    // 深度优先搜索 (DFS) 寻找增广路径
    int find(int u, int t, int limit) {
        if (u == t) return limit;  // 如果到达汇点，返回当前限制流量
        int flow = 0;  // 当前已经找到的流量
        for (int& i = st[u]; i < int(g[u].size()); i++) {  // 遍历从节点 u 出发的所有边
            auto& [v, r, f] = g[u][i];  // 取出邻接边 (v, r, f)
            if (!f || dep[v] != dep[u] + 1) continue;  // 如果没有剩余流量或者深度不符合条件，跳过
            int ret = find(v, t, min(f, limit - flow));  // 递归寻找增广路径，更新流量
            if (ret) {
                auto& [vv, rv, vf] = g[v][r];  // 取出反向边信息
                f -= ret, vf += ret;  // 更新正向边和反向边的流量
                flow += ret;  // 更新当前找到的流量
                if (flow == limit) break;  // 如果找到足够的流量，停止
            }
        }
        if (!flow) dep[u] = -1;  // 如果没有找到流量，设置深度为 -1，标记不可用
        return flow;  // 返回找到的流量
    }

    // Dinic 算法主函数，返回最大流量
    int Dinic(int s, int t, int n) {
        int ret = 0, flow;
        while (bfs(s, t, n)) {  // 通过 BFS 构建分层图
            while (flow = find(s, t, inf)) ret += flow;  // 通过 DFS 寻找增广路径，累加流量
        }
        return ret;  // 返回最大流量
    }

    // 递归查找路径，找到从源点到汇点的增广路径并记录在 ret 中
    void findpath(int u, int lim, vector<int>& ret) {
        ret.emplace_back(u);  // 将当前节点 u 添加到路径
        if (u > lim) return;  // 如果节点编号超过限制 lim，停止递归
        for (auto [v, r, f] : g[u]) {  // 遍历节点 u 的所有边
            auto [vv, rr, ff] = g[v][r];  // 获取反向边的流量信息
            if (ff) return findpath(v, lim, ret);  // 如果反向边的流量不为 0，递归查找路径
        }
    }
} ;

//链式前向星写法
struct DINIC {
	int S, T;
	int h[N], e[M], f[M], ne[M], idx; // 邻接表相关数组：h为头节点, e为边的终点, f为边的流量, ne为下一条边, idx为边的索引
	int q[N], d[N], cur[N]; // q为队列, d为层次数组, cur为当前弧优化数组

	// 添加一条从 a 到 b 的容量为 c 的边，同时添加一条反向边，容量为 0
	void add(int a, int b, int c) {
		e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx++; // 正向边
		e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx++; // 反向边，容量为 0
	}

	// 通过广度优先搜索 (BFS) 构建分层图
	bool bfs() {
		int hh = 0, tt = 0;
		memset(d, -1, sizeof d); // 初始化层次数组 d 为 -1
		q[0] = S, d[S] = 0, cur[S] = h[S]; // 从源点 S 开始，d[S]=0 表示源点的层次为 0
		while (hh <= tt) { // 广度优先搜索队列不为空时
			int t = q[hh++]; // 取出队首元素 t
			for (int i = h[t]; i != -1; i = ne[i]) { // 遍历从节点 t 出发的所有边
				int ver = e[i]; // ver 是当前边的终点
				if (d[ver] == -1 && f[i]) { // 如果 ver 未被访问且该边的剩余容量大于 0
					d[ver] = d[t] + 1; // 更新 ver 的层次
					cur[ver] = h[ver]; // 初始化 ver 的当前弧
					if (ver == T) return 1; // 如果 ver 是汇点，返回 true，表示找到增广路径
					q[++tt] = ver; // 将 ver 加入队列
				}
			}
		}
		return 0; // 如果无法到达汇点，返回 false
	}

	// 深度优先搜索 (DFS) 寻找阻塞流
	int find(int u, int limit) {
		if (u == T) return limit; // 如果到达汇点，返回当前限制流量
		int flow = 0; // 当前已经找到的流量
		for (int i = cur[u]; i != -1 && flow < limit; i = ne[i]) { // 遍历从节点 u 出发的所有边，直到找到足够的流量
			cur[u] = i; // 当前弧优化
			int ver = e[i]; // ver 是当前边的终点
			if (d[ver] == d[u] + 1 && f[i]) { // 如果 ver 的层次比 u 大 1 且该边还有剩余流量
				int t = find(ver, min(f[i], limit - flow)); // 递归寻找从 ver 出发的增广路径，限制流量为剩余的最小值
				if (!t) d[ver] = -1; // 如果 t 为 0，表示无法继续增广，标记 ver 不再访问
				f[i] -= t, f[i ^ 1] += t, flow += t; // 更新当前边和反向边的流量
			}
		}
		return flow; // 返回找到的流量
	}

	// Dinic 算法主函数，返回最大流量
	int Dinic() {
		int ret = 0, flow;
		while (bfs()) { // 构建分层图
			while (flow = find(S, INF)) ret += flow; // 通过阻塞流寻找增广路径，并累加流量
		}
		return ret; // 返回最大流量
	}
}dinic;
//---------------------------------------------------#费用流---------------------------------------
/*
	时间复杂度：
	𝑂(F⋅m)，其中 F 是流量的总增广次数，m 是边的数量。
*/

struct EK_SuanFa {
	int h[N], w[M], e[M], ne[M], idx; // h存储头节点, e存储边, ne存储下一条边的索引, idx为边的编号
	// 添加一条边到图中，双向边 (a, b) 和 (b, a)
	void add(int a, int b, int c) {
		e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
		e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx++;
	}
	int S, T;
	int dist[N];
	int incf[N], f[N];
	int q[N];//队列
	bool st[N];
	int pre[N];

	// spfa算法：寻找最短路径，并返回是否存在增广路径
	bool spfa() {
		int hh = 0, tt = 1; // hh为队列头指针，tt为队列尾指针
		memset(dist, 0x3f, sizeof dist); // 初始化距离为无穷大
		memset(incf, 0, sizeof incf); // 初始化增广流量
		q[0] = S, dist[S] = 0, incf[S] = INF; // 源点进入队列，增广流量初始化为无穷大
		while (hh != tt) { // 队列不空
			int t = q[hh++]; // 取出队头元素
			if (hh == N) hh = 0; // 环形队列处理
			st[t] = 0; // 标记t不在队列中
			for (int i = h[t]; i != -1; i = ne[i]) { // 遍历t的邻边
				int j = e[i]; // j为当前边的终点
				if (f[i] && dist[j] > dist[t] + w[i]) { // 如果可以增广并且找到更短的路径
					dist[j] = dist[t] + w[i]; // 更新距离
					incf[j] = min(incf[t], f[i]); // 更新增广路径的流量
					pre[j] = i; // 记录前驱边
					if (!st[j]) { // 如果j不在队列中
						st[j] = 1; // 标记j在队列中
						q[tt++] = j; // 将j加入队列
						if (tt == N) tt = 0; // 环形队列处理
					}
				}
			}
		}
		return incf[T] > 0; // 返回是否存在增广路径
	}
	// EK算法：求解最大流和最小费用
	void EK(int& flow, int& cost) {
		flow = cost = 0; // 初始化最大流和费用
		while (spfa()) { // 通过spfa寻找增广路径
			int t = incf[T]; // t为当前增广路径上的流量
			flow += t, cost += t * dist[T]; // 更新总流量和总费用
			for (int i = T; i != S; i = e[pre[i] ^ 1]) { // 反向更新残余网络
				f[pre[i]] -= t; // 正向边流量减少
				f[pre[i] ^ 1] += t; // 反向边流量增加
			}
		}
	}
}ek;
//-----------------------------------------------#数位dp----------------------------------------------
/*
数位dp得dfs写法，优点：思路简单，边写边想，套路化（尽量将所有出现过的状态都存入 f 数组内）
在此模板中，由于f[20][7][2]即使dfs的搜索空间，所以时间复杂度就是f[20][7][2]的大小
*/
struct DIGIT_DP {
	int s[8] = { 0, 8, 1, 0, 9, 7, 5 };

	// 动态规划缓存数组，避免重复计算
	LL f[20][7][2];

	// 动态规划函数，用于计算从当前状态开始有多少个包含子序列 "810975" 的数字
	LL dp(int pos, int seq, int lead, int limit, vector<int>& num) {
		LL ret = 0;
		if (pos == -1) return seq == 7; // 如果已经检查完所有位数，并且完全匹配到 "810975" 则返回 1
		if (f[pos][seq][limit]) return f[pos][seq][limit]; // 如果已经计算过当前状态，直接返回缓存的结果

		int up = limit ? num[pos] : 9; // 确定当前位置的数字范围，如果限制则为当前位的数字，否则为 0~9

		for (int i = 0; i <= up; i++) {
			// 如果当前数字匹配到子序列中的当前位，继续向后匹配
			if (seq <= 6 && s[seq] == i) {
				ret += dp(pos - 1, seq + 1, lead && i == 0, limit && up == i, num);
			}
			else {
				// 否则继续在当前状态匹配下一个数字
				ret += dp(pos - 1, seq, lead && i == 0, limit && up == i, num);
			}
		}
		f[pos][seq][limit] = ret; // 缓存当前状态的计算结果
		return ret;
	}

	// 检查 1 到某个数字 u 内包含子序列 "810975" 的数字
	bool work(LL u) {
		memset(f, 0, sizeof f); // 清空缓存数组
		vector<int> num; // 将数字 u 转换成一个数组，方便逐位处理
		while (u) {
			num.push_back(u % 10);
			u /= 10;
		}

		LL ret = dp(num.size() - 1, 1, 1, 1, num); // 调用动态规划函数计算
		return ret;
	}
}DP;


//-------------------------------#质数筛/#质因子分解(// 初始化函数，使用埃拉托斯特尼筛法生成素数表)----------------
struct PRIME {
	vector<int>prime;
	int s[N];
	// 初始化函数，使用线性筛法计算最小质因数
	void get_prime(int n = 1e6 + 10) {
		for (int i = 2; i < n; i++) {
			// 如果 s[i] 为 0，说明 i 是质数
			if (!s[i]) {
				// 记录质数 p 和最小质因数 s
				prime.push_back(i);
				s[i] = i;
			}
			// 遍历所有已知的质数，更新合数的最小质因数
			for (int j = 0; j < prime.size() && prime[j] * i < n; j++) {
				s[i * prime[j]] = prime[j];// 标记合数 i * p[j] 的最小质因数
				if (i % prime[j] == 0) break;// 如果 p[j] 是 i 的因数，停止进一步的标记
			}
		}
	}
	// 处理函数，针对每个数组元素 a，分解其素因数并更新结果
	void work(int a, int i) {
		for (int j = 0; j < prime.size() && prime[j] * prime[j] <= a; j++) {
			int k = prime[j];
			if (a % k) continue; // 如果 a 不能被 k 整除，跳过该素数
			//ans += 1ll * (i - pos[k]) * (n - i + 1); // 更新结果
			//pos[k] = i; // 更新素数 k 的上次出现位置
			while (a % k == 0) {
				a /= k; // 除去所有 k 的因数
			}
		}
		if (a > 1) { // 如果 a 还剩下一个大于 1 的素数因子
			int k = a;
			//ans += 1ll * (i - pos[k]) * (n - i + 1); // 处理该素数因子
			//pos[k] = i; // 更新该素数的上次出现位置
		}
	}
}Prime;

//------------------------------------------#莫比乌斯反演------------------------------------
/*
μ(n)（莫比乌斯函数）的定义如下：

μ(n) =
  1,  当 n = 1;
  (-1)^k, 当 n 是由 k 个互不相同的质数的乘积（即 n 无平方因子）；
  0,  当 n 含有平方因子（即存在某个质数 p，使得 p^2 整除 n）。

它的一个重要性质是：
[gcd(i, j) = 1] = ∑_{d | gcd(i, j)} μ(d)

也就是说，判断 i 和 j 是否互素，可以通过 μ 函数的加权求和来实现。

---

此外，若有两个数论函数 f(n), g(n) 满足：
f(n) = ∑_{d | n} g(d)

则通过莫比乌斯反演可得：
g(n) = ∑_{d | n} μ(n/d) * f(d)

μ 就是“反演核”，能把约数和式反过来求回原函数。

下面这段代码实现了：
→ 利用线性筛法（O(n)）同时计算出
   1. 每个整数的最小质因数 s[i]
   2. 每个整数的莫比乌斯函数 μ(i)
*/

struct Mobius {
    vector<int> prime;  // 存储筛法中找到的所有质数
    int s[N];           // s[i] 表示 i 的最小质因数（smallest prime factor）
    int mu[N];          // mu[i] 表示 μ(i) 的值

    // 初始化函数，默认计算 1 ~ n 的 μ 值
    void init(int n = N) {
        mu[1] = 1; // 根据定义 μ(1) = 1

        // 从 2 开始筛
        for (int i = 2; i < n; i++) {

            // 如果 s[i] == 0，说明 i 尚未被标记，是质数
            if (!s[i]) {
                prime.push_back(i); // 记录质数
                s[i] = i;           // 最小质因数就是自己
                mu[i] = -1;         // 质数的 μ 值为 -1
            }

            // 遍历所有已找到的质数，用这些质数来标记合数
            for (int j = 0; j < prime.size() && prime[j] * i < n; j++) {
                int p = prime[j];

                s[i * p] = p; // 标记 i*p 的最小质因数为 p

                if (i % p == 0) {
                    /*
                     如果 i 本身含有因子 p，
                     那么 i*p 就至少含有 p^2，
                     根据定义 μ(i*p) = 0 （因为有平方因子）。
                    */
                    mu[i * p] = 0;
                    break; // 一旦出现平方因子就停止继续筛这个 i
                } else {
                    /*
                     如果 p 不整除 i，则说明 p 是一个新的质因子，
                     根据定义 μ(i*p) = -μ(i)
                     （多了一个新的不同质因子，符号取反）
                    */
                    mu[i * p] = -mu[i];
                }
            }
        }

        // 如果你需要 μ 的前缀和，可以启用下面这一行
        // for (int i = 1; i < n; ++i) mu[i] += mu[i - 1];
    }
};


//------------------------------------------#快速幂------------------------------------------

LL qpow(LL a,LL b,LL p){
    LL ret=1;
    while(b){
        if(b&1)ret=ret*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ret;
}

//-----------------------------------------#模运算类：MInt ----------------------------


// template<int MOD>
class MInt {
private:
    static int MOD;
    int value; // 当前值（模 MOD）

    // 快速幂 (a^b % MOD)
    static int mod_exp(int a, int b) {
        int result = 1;
        while (b > 0) {
            if (b & 1) result = 1LL * result * a % MOD; // 如果 b 的当前位为 1
            a = 1LL * a * a % MOD;
            b >>= 1;
        }
        return result;
    }
    

public:
    static void set_mod(int m) {
        MOD = m;
    }
    // 构造函数
    MInt(int v = 0) : value((v % MOD + MOD) % MOD) {}

    // 获取当前值
    int get() const { return value; }

    // 模逆元 (x^(MOD-2) % MOD) -> 仅在 MOD 是质数时成立（费马小定理）
    MInt inv() const {
        return MInt(mod_exp(value, MOD - 2));
    }

    // 运算符重载：+=
    MInt& operator+=(const MInt& other) {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    // 运算符重载：-=
    MInt& operator-=(const MInt& other) {
        value -= other.value;
        if (value < 0) value += MOD;
        return *this;
    }

    // 运算符重载：*=
    MInt& operator*=(const MInt& other) {
        value = 1LL * value * other.value % MOD;
        return *this;
    }

    // 运算符重载：/=
    MInt& operator/=(const MInt& other) {
        return *this *= other.inv(); // 除法相当于乘以模逆元
    }

    // 友好的运算符重载：+
    friend MInt operator+(MInt a, const MInt& b) {
        return a += b;
    }

    // 友好的运算符重载：-
    friend MInt operator-(MInt a, const MInt& b) {
        return a -= b;
    }

    // 友好的运算符重载：*
    friend MInt operator*(MInt a, const MInt& b) {
        return a *= b;
    }

    // 友好的运算符重载：/
    friend MInt operator/(MInt a, const MInt& b) {
        return a /= b;
    }

    // 重载流插入运算符（方便输出）
    friend std::ostream& operator<<(std::ostream& os, const MInt& x) {
        return os << x.value;
    }

    // 重载流提取运算符（方便输入）
    friend std::istream& operator>>(std::istream& is, MInt& x) {
        int v;
        is >> v;
        x = MInt(v);
        return is;
    }
};
int MInt::MOD = 1e9 + 7;
/*
void solve(){
    cin>>n>>m;
    MInt::set_mod(mod);
    
    MInt ans=n;
    cout<<ans<<endl;
}
*/


//---------------------------------------#排列函数------------------------------------------

struct Next_Permutation{
	void solve(){
	    vector<int> arr = {1, 2, 3};

	    // 打印所有的排列
	    do {
	        for (int num : arr) {
	            cout << num << " ";
	        }
	        cout << endl;
	    } while (next_permutation(arr.begin(), arr.end()));

	}
};

//------------------------------------------#组合数模板---------------------------------------

struct Combination_Number{
    static const int MOD = 1e9 + 7;
    static const int MAX_N = 100000;

    long long fact[MAX_N + 1], inv[MAX_N + 1];

    void init(){
        precompute();
    }

    // 快速幂计算 x^y % MOD
    long long fast_pow(long long x, long long y, long long mod) {
        long long res = 1;
        while (y) {
            if (y & 1) res = res * x % mod;
            x = x * x % mod;
            y >>= 1;
        }
        return res;
    }

    // 预计算阶乘和阶乘的逆元
    void precompute() {
        fact[0] = inv[0] = 1;
        for (int i = 1; i <= MAX_N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        inv[MAX_N] = fast_pow(fact[MAX_N], MOD - 2, MOD);
        for (int i = MAX_N - 1; i >= 1; i--) {
            inv[i] = inv[i + 1] * (i + 1) % MOD;
        }
    }

    // 计算 C(n, i)
    long long C(int n, int i) {
        if (i > n) return 0;
        return fact[n] * inv[i] % MOD * inv[n - i] % MOD;
    }
};

//-------------------------------------------#O(n)时间求逆元-----------------------------------
/*
新学的一个求逆元的方法：

inv[i] = ( MOD - MOD / i ) * inv[MOD%i] % MOD

证明：

设t = MOD / i , k = MOD % i

则有 t * i + k == 0 % MOD

有 -t * i == k % MOD

两边同时除以ik得到

-t * inv[k] == inv[i] % MOD

即

inv[i] == -MOD / i * inv[MOD%i]

即

inv[i] == ( MOD - MOD / i) * inv[MOD%i]

证毕

适用于MOD是质数的情况，能够O(n)时间求出1~n对模MOD的逆

*/
struct inverse{
	static const int mod=998244353;
	int inv[N];
	void work(){
		inv[1]=1;
		for (int i = 2; i <= 10000000; i++)
	        inv[i] = mod - 1ll * mod / i * inv[mod % i] % mod;
	}
};


//----------------------------------------------#随机化------------------------------------------
struct Randomized {
    mt19937 rng;  // 成员变量
    Randomized() {
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
    }
    int getR(int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng);
    }
};


//----------------------------------------------#gcd------------------------------------------
/*
	gcd(a1,a2,a3,……,ak)=gcd(a1,a2-a1,a3-a2,……,ak-ak-1);
    // 递归实现 gcd
    int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
*/

//----------------------------------------#拓展欧几里得(exgcd)---------------------------------

struct EXGCD1{
    int exgcd(int a,int b,int &x,int &y){
        if(b==0){
            x=1,y=0;
            return a;
        }
        int d=exgcd(b,a%b,x,y);
        int z=x;
        x=y;
        y=z-y*(a/b);
        return d;
    }
};

struct EXGCD2 {

    // 扩展欧几里得算法
    tuple<long long, long long, long long> exgcd(long long a, long long b) {
        // 如果 b 为 0，返回 gcd(a, 0) = a，并且 x = 1, y = 0
        if (b == 0) {
            return {a, 1, 0};  
        } else {
            long long g, x1, y1;
            // 递归调用以获得 gcd 和其系数
            tie(g, x1, y1) = exgcd(b, a % b);
            long long x = y1; // x 的新值
            long long y = x1 - (a / b) * y1; // y 的新值
            return {g, x, y}; // 返回 gcd 及其系数
        }
    }

    // 求解方程 x * s + b * y = ret * t
    bool solve(long long x, long long b, long long ret, long long t) {
        long long g, s, y;
        // 使用扩展欧几里得算法求解 x 和 b 的 gcd 及系数
        tie(g, s, y) = exgcd(x, b);
        
        // 检查方程是否有解
        if ((ret * t) % g != 0) {
            cout << "No solution!" << endl;
            return false; // 如果没有解，返回 false
        }

        // 计算特解
        long long k = (ret * t) / g; // 求解 k
        s *= k; // 调整 s
        y *= k; // 调整 y

        // 计算 x 和 b 的最小公倍数（不在后续计算中使用，保留可读性）
        long long lcm = (b / g) * x; 

        // 调整解使其为正整数
        if (s <= 0) {
            // 计算需要调整的倍数
            long long adjust = (-s + (b / g) - 1) / (b / g); 
            s += adjust * (b / g); // 调整 s
            y -= adjust * (x / g); // 相应调整 y
        }

        // 确保 y 为正
        if (y <= 0) {
            long long adjust = (-y + (x / g) - 1) / (x / g); // 计算需要调整的倍数
            s -= adjust * (b / g); // 相应调整 s
            y += adjust * (x / g); // 调整 y
        }

        // 检查 s 和 y 是否都为正
        if (s > 0 && y > 0) {
            cout << "s: " << s << ", y: " << y << endl; // 输出解
            return true; // 返回 true，表示找到正解
        } else {
            cout << "No positive solution!" << endl; // 如果解不是正的，输出消息
            return false; // 返回 false
        }
    }

    // 用户输入并求解的接口
    void Solve() {
        long long x, b, ret, t;
        cout << "Enter values for x, b, ret, t: ";
        cin >> x >> b >> ret >> t; // 获取用户输入

        solve(x, b, ret, t); // 调用求解函数
    }
};


//----------------------------------------------#蕴含表达式-------------------------------------
/*

p        q        p⇒q

真 (T)   真 (T)   真 (T)
真 (T)   假 (F)   假 (F)
假 (F)   真 (T)   真 (T)
假 (F)   假 (F)   真 (T)

*/

//-----------------------------------------------#卢卡斯定理------------------------------------
/*
对于质数 p，有:C(n,m)%p=C(n/p,m/p)*C(n%p,m%p)%p;
时间复杂度为 O(f(p) + g(n)\log n)，其中 f(n) 为预处理组合数的复杂度，g(n) 为单次求组合数的复杂度。
*/
struct LUCAS {
	int c[N][N];
	//求组合数c
	int C(int a, int b, int p) {

	}
	//卢卡斯定理转换
	long long Lucas(long long n, long long m, long long p) {
		if (m == 0) return 1;
		return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
	}
}Lucas;

//------------------------------------------#威尔逊定理------------------------------------
/*
根据威尔逊定理当j为质数时，(j-1)!%j=j-1
*/


//-----------------------------------------#曼哈顿距离和切比雪夫距离------------------------------
/*

曼哈顿距离: dist=abs(x2-x1)+abs(y2-y1)
切比雪夫距离: dist=max(abs(x2-x1),abs(y2-y1))
将一个点（x,y）的坐标变为（x+y,x-y）后,原坐标系中的曼哈顿距离 = 新坐标系中的切比雪夫距离
将一个点（x,y）的坐标变为（(x+y)/2,(x-y)/2）后,原坐标系中的切比雪夫距离 = 新坐标系中的曼哈顿距离

*/

//-----------------------------------------#二项式反演-------------------------------------
/*
当：b[n]=sum(c(k,n)*a[k])(k=0,n)
时：a[n]=sum((-1)^(n-k)*c(k,n)*b[k])(k=0,n)
这个公式被称为二项式反演
*/


//-----------------------------------------#数学trick--------------------------------------
/*
一个数能被9或3整除，当且仅当这个数的各位之和能被9或3整除
一个数能被11整除，当且仅当奇数位和减去偶数位和能被 11 整除

*/

//-------------------------------------------------------#bitset-----------------------------------------------
/*
`bitset` 是 C++ 标准库中的一个模板类，用于存储和操作二进制位（bit）。`bitset` 提供了高效的位操作功能，类似于数组但专门处理位。

### 基本用法
`bitset<N > ` 表示一个长度为 `N` 的二进制位集，每个元素是 0 或 1。

#### 1. 引入头文件
```cpp
#include <bitset>
```

#### 2. 定义一个 `bitset`
```cpp
bitset<8> bs; // 创建一个长度为 8 的 bitset，初始值为 00000000
```

#### 3. 初始化
- 可以通过整型或字符串来初始化。

```cpp
bitset<8> bs1(5);           // 00000101，用整数初始化
bitset<8> bs2("10101010");   // 10101010，用二进制字符串初始化
```

#### 4. 访问和修改
- 使用下标运算符 `[]` 访问和修改指定位置的位。

```cpp
bitset<8> bs(5);  // 00000101
cout << bs[0];    // 输出 1，访问第 0 位
cout << bs[2];    // 输出 0，访问第 2 位

bs[1] = 1;        // 修改第 1 位，bs 变为 00000111
```

#### 5. 常用函数
`bitset` 提供了许多有用的成员函数：

- **`set()`** : 设置所有位为 1，或设置指定位置的位为 1。
- **`reset()`** : 将所有位重置为 0，或重置指定位置的位为 0。
- **`flip()`** : 翻转所有位，或翻转指定位置的位。
- **`count()`** : 返回 bitset 中值为 1 的位数。
- **`any()`** : 如果存在至少一个 1 返回 true，否则返回 false。
- **`none()`** : 如果所有位都是 0，返回 true。
- **`size()`** : 返回 bitset 的位数。
- **`to_string()`** : 将 bitset 转换为字符串。
- **`to_ulong()`** : 将 bitset 转换为无符号长整型。

##### 示例
```cpp
bitset<8> bs("1010");

// 设置所有位为 1
bs.set();            // bs = 11111111

// 重置第 2 位
bs.reset(2);         // bs = 11111011

// 翻转第 4 位
bs.flip(4);          // bs = 11110011

// 统计 1 的个数
cout << bs.count();  // 输出 6

// 检查是否有任意位为 1
cout << bs.any();    // 输出 true

// 检查是否所有位都为 0
cout << bs.none();   // 输出 false

// 输出 bs 的大小
cout << bs.size();   // 输出 8

// 将 bs 转换为字符串
cout << bs.to_string();  // 输出 "11110011"

// 将 bs 转换为无符号整型
cout << bs.to_ulong();   // 输出 243
```

### 运算符支持
`bitset` 支持按位运算符，如 `&`（与）、`|`（或）、`^`（异或）、`~`（取反），以及移位运算符 `<<` 和 `>>`。


bitset<8> bs1("1100");
bitset<8> bs2("1010");

bitset<8> bs3 = bs1 & bs2;   // 位与，结果为 1000
bitset<8> bs4 = bs1 | bs2;   // 位或，结果为 1110
bitset<8> bs5 = bs1 ^ bs2;   // 位异或，结果为 0110
bitset<8> bs6 = ~bs1;        // 位取反，结果为 0011
bitset<8> bs7 = bs1 << 2;    // 左移两位，结果为 00001100
bitset<8> bs8 = bs2 >> 1;    // 右移一位，结果为 0101


### 示例代码

#include <iostream>
#include <bitset>
using namespace std;

int main() {
	bitset<8> bs("1010");  // 初始化一个长度为 8 的 bitset，值为 00001010

	bs.set(1);             // 设置第 1 位为 1，变为 00001011
	bs.reset(3);           // 重置第 3 位为 0，变为 00000011
	bs.flip(2);            // 翻转第 2 位，变为 00000111

	cout << "bs: " << bs << endl;      // 输出：00000111
	cout << "count of 1s: " << bs.count() << endl;  // 输出：3
	cout << "to_ulong: " << bs.to_ulong() << endl;  // 输出：7

	return 0;
}


总结:
`bitset` 是一个强大的工具，适用于处理大规模位操作的问题，比如位图、位掩码等场景。

*/

