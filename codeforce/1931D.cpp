/*
g++ -DDEBUG --std=c++23 -o 1931D.out 1931D.cpp && cat 1931D.data|./1931D.out
*/
#include <bits/stdc++.h>
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
    int64_t x,y;
    cin>>n>>x>>y;
    vector<int64_t> modx(n);
    vector<int64_t> mody(n);
    for(int i=0;i<n;i++){
      int64_t a;
      cin>>a;
      modx[i]=a%x;
      mody[i]=a%y;
    }
    uint64_t ans=0;
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        int64_t sum=modx[i]+modx[j];
        int64_t sub=mody[i]-mody[j];
          ans+=((sum==0||sum==x) && (sub==0));
        // if(!((nums[i]+nums[j])%x)&&!((nums[i]-nums[j])%y)){
        //   ans++;
        //   debug(i,j,ans);
        //   debug(nums[i],nums[j]);
        //   debug(nums[i]+nums[j],nums[i]-nums[j]);
        // }
      }
    }
    cout<<ans<<endl;
  }
  return 0;
}