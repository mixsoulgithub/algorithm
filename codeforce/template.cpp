/*
g++ --std=c++23 -o problem_id.out problem_id.cpp && cat problem_id.data|./problem_id.out
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
using namespace std;

int main() {
  ll_t batch;
  cin >> batch;
  for (;batch>0;batch--) {
  }
  return 0;
}