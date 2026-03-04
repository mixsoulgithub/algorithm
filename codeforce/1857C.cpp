/*
g++ -DDEBUG --std=c++23 -o 1857C.out 1857C.cpp && cat 1857C.data|./1857C.out
*/
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdint>
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
using namespace std;

int main() {
  ll_t batch;
cin.tie(0)->sync_with_stdio(0);
  cin >> batch;
  for (;batch>0;batch--) {
    uint64_t n;
    cin>> n;
    uint64_t combin_n= n*(n-1)/2;
    debug(n);
    debug(combin_n);
    vector<int64_t> a(combin_n);
    for(int i=0;i<combin_n;i++){
     cin>>a[i];
    }
    std::sort(a.begin(),a.end());
    uint64_t index=-1;
    for(int i=n-1;i>=0;i--){
      index+=i;
      // debug(index);
      cout<<a[index]<<" ";
    }
    cout<<endl;
  }
  return 0;
}