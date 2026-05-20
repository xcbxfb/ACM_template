#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    // R[i] 存储 i 后面第一个比 p[i] 小的元素的下标 (Next Smaller Element)
    vector<int> R(n + 1, n + 1);
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && p[st.back()] > p[i]) {
            R[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }

    int LOG = 21;
    vector<vector<int>> up(LOG, vector<int>(n + 2, 0));
    vector<vector<long long>> min_val(LOG, vector<long long>(n + 2, 2e18));
    vector<vector<long long>> sum_S(LOG, vector<long long>(n + 2, 0));
    vector<vector<long long>> sum_Sx(LOG, vector<long long>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        up[0][i] = R[i];
        min_val[0][i] = 2LL * i - R[i];
        sum_S[0][i] = R[i] - i;
        sum_Sx[0][i] = 1LL * (R[i] - i) * i;
    }

    // 构建倍增表
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            int nxt = up[j - 1][i];
            if (nxt != 0 && nxt <= n + 1) {
                up[j][i] = up[j - 1][nxt];
                min_val[j][i] = min(min_val[j - 1][i], min_val[j - 1][nxt]);
                sum_S[j][i] = sum_S[j - 1][i] + sum_S[j - 1][nxt];
                sum_Sx[j][i] = sum_Sx[j - 1][i] + sum_Sx[j - 1][nxt];
            }
        }
    }

    // 处理查询
    for (int q_idx = 0; q_idx < q; q_idx++) {
        int l, r;
        cin >> l >> r;
        long long ans = 0;
        
        // 第一块单独处理
        int v = R[l];
        if (v > r) v = r + 1;

        long long S1 = v - l;
        long long c1 = (S1 - 1) / 2;
        if (S1 > 0) {
            ans += c1 * (S1 - 1 - c1);
        }

        int curr = v;

        // 持续处理完整的中间块
        while (curr <= r && R[curr] <= r) {
            if (2LL * curr - R[curr] < l) {
                // 如果当前块触发 A < S，手动计算并推进一步
                long long A = curr - l;
                long long S = R[curr] - curr;
                long long c = (A + S) / 2;
                if (c > S) c = S;
                ans += c * (A + S - c);
                curr = R[curr];
            } else {
                // 若 A >= S 成立，使用倍增加速跳跃连续满足条件的块段
                for (int j = LOG - 1; j >= 0; j--) {
                    int nxt = up[j][curr];
                    // 保证跳跃过程都在范围内且全段均满足 2y - R[y] >= l (即 A >= S)
                    if (nxt != 0 && nxt <= r && min_val[j][curr] >= l) {
                        ans += sum_Sx[j][curr] - 1LL * l * sum_S[j][curr];
                        curr = nxt;
                    }
                }
            }
        }

        // 处理最后一块因为右边界截断的余下部分
        if (curr <= r) {
            long long A = curr - l;
            long long S = r + 1 - curr;
            long long c = (A + S) / 2;
            if (c > S) c = S;
            ans += c * (A + S - c);
        }

        cout << ans << "\n";
    }
}

int main() {
    // 关闭同步流提升速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}