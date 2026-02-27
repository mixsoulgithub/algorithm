/*
g++ --std=c++23 -o 2148E 2148E.cpp && cat 2148E.data|./2148E
*/
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
template <typename T> void dbg_out(T x) { std::cerr << x << ")" << std::endl; }
void dbg_out() { std::cerr << ")" << std::endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  std::cerr << H << ", ";
  dbg_out(T...);
}
#ifdef DEBUG
#define debug(...)                                                             \
  std::cerr << "(" << #__VA_ARGS__ << ") = (", dbg_out(__VA_ARGS__)
#else
#define debug(...)
#endif
typedef unsigned long long ll_t;
typedef std::vector<long long> vll_t;

int main() {
  using namespace std;
  cin.tie(0)->sync_with_stdio(0);
  ll_t batch;
  cin >> batch;
  debug("1");
  for (; batch > 0; batch--) {
    int l = 0, r = 0;
    int len, k;
    cin >> len;
    cin >> k;
    debug(len, k);
    uint64_t ans = 0;
    vector<int> map_all(len + 1, 0);
    int nums[len];
    for (int i = 0; i < len; i++) {
      int e;
      cin >> e;
      nums[i] = e;
      map_all[e]++;
    }
    bool has_not_k_times_element = false;
    debug("1");
    for (const auto &pair : map_all) {
      if ((pair % k) != 0) {
        has_not_k_times_element = true;
        break;
      }
    }
    if (has_not_k_times_element) {
      cout << 0 << endl;
      continue;
    }
    vector<int> map_lr(len + 1, 0);
    // for(const auto& pair: map_all){
    //   debug(pair.first,pair.second);
    // }
    // debug(0, map_lr[nums[0]]);
    // debug(1, map_lr[nums[1]]);
    while (r<len) {
      //  debug(r, map_lr[nums[r]],map_lr[nums[r+1]],map_all[nums[r+1]], ans);
      map_lr[nums[r]]++;
      while ((map_lr[nums[r]]) * k > map_all[nums[r]]) {
        map_lr[nums[l]]--;
        l++;
      }
      ans += (r - l + 1);
      r++;
    }
    cout << ans << endl;
  }
  return 0;
}