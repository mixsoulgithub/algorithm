#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long M = a[n - 1];
        long long ans = 0;
        //find triple. for one element, find threashould Tk.
        for (int k = 2; k < n; k++) {
            long long Tk;
            if (2 * a[k] >= M) {//the rest two num's sum can't bigger than Tk. search  biggest num from minimal
                Tk = a[k];
            } else {
                Tk = M - a[k];
            }
            int left = 0;
            int right = k - 1;
            int cnt = 0;
            while (left < right) {
                if (a[left] + a[right] > Tk) {
                    cnt += (right - left);
                    right--;
                } else {
                    left++;
                }
            }
            ans += cnt;
        }
        cout << ans << endl;
    }
    return 0;
}