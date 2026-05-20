#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// 处理单个测试用例
void solve() {
    int n;
    cin >> n;

    // 存储每个博客去重后、按最后出现顺序反转的序列
    vector<vector<int>> blog_sequences(n);
    // 存储每个博客包含的所有用户集合，方便快速判断
    vector<set<int>> blog_sets(n);

    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        vector<int> a(l);
        for (int j = 0; j < l; ++j) cin >> a[j];

        set<int> seen_in_blog;
        // 从后往前扫，记录用户最后一次出现的顺序
        for (int j = l - 1; j >= 0; --j) {
            if (seen_in_blog.find(a[j]) == seen_in_blog.end()) {
                blog_sequences[i].push_back(a[j]);
                seen_in_blog.insert(a[j]);
                blog_sets[i].insert(a[j]);
            }
        }
    }

    vector<bool> used(n, false);
    set<int> global_seen;
    vector<int> final_Q;

    // 贪心选择 n 次，每次选出能让当前 Q 增加部分字典序最小的博客
    for (int step = 0; step < n; ++step) {
        int best_idx = -1;
        vector<int> best_contribution;

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;

            // 计算该博客当前能贡献的（尚未在 global_seen 中的）用户序列
            vector<int> current_contribution;
            for (int user : blog_sequences[i]) {
                if (global_seen.find(user) == global_seen.end()) {
                    current_contribution.push_back(user);
                }
            }

            // 字典序比较：找到最小的贡献序列
            if (best_idx == -1 || current_contribution < best_contribution) {
                best_contribution = current_contribution;
                best_idx = i;
            }
        }

        // 将选中的博客贡献加入 final_Q
        for (int user : best_contribution) {
            final_Q.push_back(user);
        }
        // 更新全局已选用户集
        for (int user : blog_sets[best_idx]) {
            global_seen.insert(user);
        }
        used[best_idx] = true;
    }

    // 输出结果
    for (int i = 0; i < final_Q.size(); ++i) {
        cout << final_Q[i] << (i == final_Q.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}