/*
g++ --std=c++23 -o 2148E 2148E.cpp && cat 2148E.data|./2148E
*/
#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
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
  for (;batch>0;batch--) {
    unordered_map<int, int> map_1;
    unordered_map<int, int> map_all;
    

  }
  return 0;
}