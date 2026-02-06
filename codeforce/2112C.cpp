/*
g++ --std=c++23 -o 2112C 2112C.cpp && cat 2112C.data|./2112C
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


int main() {
  using namespace std;
  int batch;
  cin >> batch;
  for (int batch_iter = 0; batch_iter < batch; batch_iter++) {
    int element_num;
    cin>>element_num;
    vector<int> elements(element_num);
    for(int i=0;i<element_num;i++){
      cin>>elements[i];
    }
    //1. sum of 3 bigger than any other one. 2. sum of 2 in 3 bigger than left 1. here comparasion is strict.
    int l=0, r=element_num-1;
    int max_e=elements[element_num-1];
    int ans=0;
    for(int big=element_num-1;big>=2;big--){
      for(int mid=big-1;mid>=1;mid--){
        int l0=0,r0=mid-1;//(elements[mid]+elements[small])>elements[big]
        int target0=elements[big]-elements[mid];
        while(l0<=r0){
          int m=(l0+r0)/2;
          if(elements[m]>target0){
            r0=m-1;
          }else{
            l0=m+1;
          }
        }//l0 is first element index s.t. element[l0]>element[big]-element[mid]
        int l1=0,r1=mid-1;//(elements[mid]+elements[small])+elements[big]>max_e
        int target1=max_e-elements[big]-elements[mid];
        while(l1<=r1){
          int m=(l1+r1)/2;
          if(elements[m]>target1){
            r1=m-1;
          }else{
            l1=m+1;
          }
        }//l1 is first element index s.t. element[l1]>maxe-element[big]-element[mid]
        ans+=mid-max(l0,l1);
      }
    } 
    cout<<ans<<endl;
  }
  return 0;
}