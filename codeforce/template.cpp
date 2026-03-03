/*
g++ -DDEBUG --std=c++23 -o problem_id.out problem_id.cpp && cat problem_id.data|./problem_id.out
*/
#include <bits/stdc++.h>
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
using namespace std;

int main() {
  ll_t batch;
cin.tie(0)->sync_with_stdio(0);
  cin >> batch;
  for (;batch>0;batch--) {
    uint64_t ans;

    cout<<ans<<endl;
  }
  return 0;
}