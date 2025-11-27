/*
g++ --std=c++23 -o 1051B 1051B.cpp && cat 1051B.data|./1051B
*/
#include <algorithm>
#include <bit>
#include <iostream>
#include <tuple>
#include <vector>
template <typename T> void dbg_out(T x) { std::cerr << x << ")" << std::endl; }
void dbg_out() { std::cerr << ")" << std::endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  std::cerr << H << ", ";
  dbg_out(T...);
}
#define debug(...)                                                             \
  std::cerr << "(" << #__VA_ARGS__ << ") = (", dbg_out(__VA_ARGS__)

typedef unsigned long long ll_t;
typedef std::vector<long long> vll_t;

int main() {
  using namespace std;
  ll_t batch;
  cin >> batch;
  for (ll_t batch_iter = 0; batch_iter < batch; batch_iter++) {
    ll_t prices_num, vouchers_num;
    cin >> prices_num >> vouchers_num;
    vector<ll_t> prices(prices_num);
    vector<ll_t> vouchers(vouchers_num);
    for (ll_t i = 0; i < prices_num; i++) {
      cin >> prices[i];
    }
    for (ll_t i = 0; i < vouchers_num; i++) {
      cin >> vouchers[i];
    }
    std::sort(vouchers.begin(), vouchers.end());
    std::sort(prices.begin(), prices.end(),
              [](const ll_t a, const ll_t b) { return a > b; });
    ll_t prices_i = 0;
    ll_t vouchers_i = 0;
    ll_t ans = 0;
    while (prices_i < prices_num && vouchers_i < vouchers_num) {
      // check price_i<price_num again.
      for (ll_t j = 0; j < vouchers[vouchers_i] - 1 && prices_i < prices_num; j++) {
        ans += prices[prices_i++];
      }
      prices_i++; // buy it for free!
      vouchers_i++;
    }
    while (prices_i < prices_num) {
      ans += prices[prices_i++];
    }
    cout << ans << endl;
  }

  return 0;
}