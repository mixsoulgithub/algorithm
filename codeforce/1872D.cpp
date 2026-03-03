/*
g++ -DDEBUG --std=c++23 -o 1872D.out 1872D.cpp && cat 1872D.data|./1872D.out
*/
#include <bits/stdc++.h>
#include <cstdint>
#include <numeric>
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
  cin >> batch;
  for (;batch>0;batch--) {
    uint64_t n,x,y;
    cin>>n>>x>>y;
    uint64_t lcm_xy=std::lcm(x, y);    
    uint64_t rpt=n/lcm_xy;
    uint64_t xnum=n/x;
    uint64_t ynum=n/y;
    debug(n,x,y,lcm_xy,rpt, xnum,ynum);
    int64_t ans= (n+n-(xnum-rpt)+1)*(xnum-rpt)/2-(1+ynum-rpt)*(ynum-rpt)/2;
    cout<<ans<<endl;
  }
  return 0;
}