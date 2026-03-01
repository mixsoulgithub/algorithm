/*
g++ --std=c++23 -o 1909B.out 1909B.cpp && cat 1909B.data|./1909B.out
*/
#include <bits/stdc++.h>
#include <cstdio>
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
using namespace std;

int main() {
  ll_t batch;
  cin >> batch;
  for (; batch > 0; batch--) {
    int len;
    cin >> len;
    // debug(len);
    ll_t first;
    cin >> first;
    // printf("0x%llx\n",first);
    int zeros = 65;
    for (; len > 1; len--) {
      ll_t now;
      cin >> now;
    // printf("0x%llx\n",now);
      zeros = min(zeros, std::countr_zero(now ^ first));
    }
    cout << (1 << (zeros + 1)) << endl;
  }
  return 0;
}