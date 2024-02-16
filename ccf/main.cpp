#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<unordered_map<int, int>> preprocessArray(const vector<int>& arr) {
    vector<unordered_map<int, int>> prefixCounts(arr.size());
    unordered_map<int, int> counts;
    for (int i = 0; i < arr.size(); ++i) {
        counts[arr[i]]++;
        prefixCounts[i] = counts;
    }
    return prefixCounts;
}

pair<int, int> findDistinctElements(const vector<unordered_map<int, int>>& prefixCounts, const vector<int>& arr, int l, int r) {
    const auto& leftCounts = prefixCounts[l - 1];
    const auto& rightCounts = prefixCounts[r - 1];
    for (const auto& entry : rightCounts) {
        if (leftCounts.find(entry.first) != leftCounts.end() && leftCounts.at(entry.first) < entry.second) {
            int i = l;
            for (; i < r; ++i) {
                if (leftCounts.find(entry.first) != leftCounts.end() && leftCounts.at(entry.first) != arr[i - 1]) {
                    return make_pair(i, distance(begin(leftCounts), leftCounts.find(entry.first)) + 1);
                }
            }
        }
    }
    return make_pair(-1, -1);
}

int main() {
    int t;
    cin >> t;

    for (int testCase = 0; testCase < t; ++testCase) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        auto prefixCounts = preprocessArray(arr);

        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            auto result = findDistinctElements(prefixCounts, arr, l, r);
            cout << result.first << " " << result.second << endl;
        }

        if (testCase < t - 1) {
            cout << endl;
        }
    }

    return 0;
}
