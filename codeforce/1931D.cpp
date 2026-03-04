/*
g++ -DDEBUG --std=c++23 -o 1931D.out 1931D.cpp && cat 1931D.data|./1931D.out
*/
#include <bits/stdc++.h>
#include <cstdint>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        ll n, x, y;
        cin >> n >> x >> y;
        
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        map<pair<ll, ll>, ll> freq;
        ll ans = 0;
        
        for (int i = 0; i < n; i++) {
            ll rmd_x = a[i] % x;
            ll rmd_y = a[i] % y;
            
            // 要找的配对元素的模 x 值
            ll need_x = (x - rmd_x) % x;
            
            // 查找之前出现过的满足条件的元素
            ans += freq[{rmd_y, need_x}];
            
            // 将当前元素加入哈希表
            freq[{rmd_y, rmd_x}]++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}