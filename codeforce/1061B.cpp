/*
g++ --std=c++23 -o 1061B 1061B.cpp && cat 1061B.data|./1061B
*/
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <bit>
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
  for (int batch_iter = 0; batch_iter < batch; batch_iter++) {
    ll_t AB_len, query_num;
    cin >> AB_len >> query_num;
    string AB_seq;
    cin >> AB_seq;
    vector<tuple<char, int>> AB_pair;
    int num = 1;
    for (int i = 1; i < AB_len; i++) {
      if (AB_seq[i] == AB_seq[i - 1]) {
        num++;
      } else {
        AB_pair.push_back(make_tuple(AB_seq[i - 1], num));
        num = 1;
      }
    }
    AB_pair.push_back(make_tuple(AB_seq[AB_len - 1], num));
    ll_t AB_pair_len = AB_pair.size();
    for (int i = 0; i < query_num; i++) {
      ll_t q, ans = 0;
      cin >> q;
      if(q==0) return 0;
      if (AB_pair_len == 1) {
        auto [c, _] = AB_pair[0];
        if (c == 'A') {
          cout<< q<<endl;
          continue;
        }else{
          cout<< ll_t(bit_width(q))<<endl;
          continue;
        }
      }
      for (ll_t AB_pair_iter = 0; q != 0; AB_pair_iter++) {
        ll_t loc = AB_pair_iter % AB_pair_len;
        auto [c, c_len] = AB_pair[loc];
        if (c == 'A') {
          // use ll_t by hand to solve conflict of deduce.
          ll_t mov = min<ll_t>(q, c_len);
          q -= mov;
        //   cout<<q<<endl;
          ans += mov;
        } else {
          for (int j = 0; q != 0 && j < c_len; j++) { //note: i is not good, use i0,i1...
            q = q >> 1;
            ans++;
          }
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}